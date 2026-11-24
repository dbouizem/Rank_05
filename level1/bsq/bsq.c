#include "bsq.h"

/*
** Steps to build the exercise:
** 1. Choose the input source: a file or stdin.
** 2. Read and validate the header: height and three distinct symbols.
** 3. Read and store the map.
** 4. Validate the map: characters, width, line endings and height.
** 5. Find the largest empty square using the dp array.
** 6. Fill the square, print the map and free the memory.
** 7. Handle multiple files, errors and separator lines.
*/

/* Read the height and three distinct printable symbols. */
int		read_header(FILE *input, t_header *header)
{
	char	*line;
	size_t	cap;
	int		i;

	line = NULL;
	cap = 0;
	if (getline(&line, &cap, input) == -1)
		return (free(line), -1);
	i = 0;
	header->h = 0;
	while (line[i] >= '0' && line[i] <= '9')
	{
		/* Check the limit before multiplying to prevent integer overflow. */
		if (header->h > (INT_MAX - (line[i] - '0')) / 10)
			return (free(line), -1);
		header->h = header->h * 10 + (line[i++] - '0');
	}
	if ( header->h <= 0)
		return (free(line), -1);
	if (read_symbol(line, &i, &header->e) == -1
		|| read_symbol(line, &i, &header->o) == -1
		|| read_symbol(line, &i, &header->f) == -1)
		return (free(line), -1);
	if (header->e == header->o
		|| header->e == header->f
		|| header->o == header->f)
		return (free(line), -1);
	if (line[i] != '\n' || line[i + 1] != '\0')
		return (free(line), -1);
	free(line);
	return (0);
}

/* Read exactly h rows of equal width, each ending with a newline. */
char	**read_grid(FILE *input, t_header *header)
{
	char	**grid;
	size_t	cap;
	int		y;
	char	*extra;

	grid = calloc((size_t)header->h, sizeof(char *));
	if (grid == NULL)
		return (NULL);
	y = 0;
	while (y < header->h)
	{
		cap = 0;
		if (getline(&grid[y], &cap, input) == -1
			|| check_row(grid[y], header, y) == -1)
			return (free_grid(grid, y + 1), NULL);
		y++;
	}
	/* An extra row makes the map invalid. */
	cap = 0;
	extra = NULL;
	if (getline(&extra, &cap, input) != -1)
	{
		free(extra);
		return (free_grid(grid, header->h), NULL);
	}
	free(extra);
	return (grid);
}

/* dp[i]: size of the largest square with bottom-right corner at (x, y). */
int		find_square(char **grid, t_header *header, t_square *best)
{
	int		*dp;
	int		i;
	int		x;
	int		y;

	*best = (t_square){0};
	dp = calloc((size_t)header->h * header->w, sizeof(int));
	if (dp == NULL)
		return (-1);
	y = 0;
	while (y < header->h)
	{
		x = 0;
		while (x < header->w)
		{
			i = y * header->w + x;
			if (grid[y][x] == header->e)
			{
				dp[i] = 1;
				/* 1 + the minimum square size to the left, above and diagonally above-left. */
				if (x > 0 && y > 0)
					dp[i] += min_three(dp[i - 1],
						dp[i - header->w],
						dp[i - header->w - 1]);
			}
			/* On a tie, keep the first square: topmost, then leftmost. */
			if (dp[i] > best->size)
			{
				best->size = dp[i];
				best->x = x - best->size + 1;
				best->y = y - best->size + 1;
			}
			x++;
		}
		y++;
	}
	free(dp);
	return (0);
}

/* Fill from the top-left corner of the best square. */
void	fill_square(char **grid, t_header *header, t_square *best)
{
	int	x;
	int	y;

	y = best->y;
	while (y < best->y + best->size)
	{
		x = best->x;
		while (x < best->x + best->size)
		{
			grid[y][x] = header->f;
			x++;
		}
		y++;
	}
}

/* Read, solve and free a map; report errors on stderr. */
int		solve_map(FILE *input)
{
	t_header	header;
	int			status;
	char		**grid;
	t_square	best;

	status = read_header(input, &header);
	grid = NULL;
	if (status == 0)
		grid = read_grid(input, &header);
	if (status == -1 || grid == NULL)
		return (fprintf(stderr, "map error\n"), 1);

	if (find_square(grid, &header, &best) == -1)
		return (free_grid(grid, header.h),
				fprintf(stderr, "map error\n"), 1);

	fill_square(grid, &header, &best);

	print_grid(grid, &header);

	free_grid(grid, header.h);
	return (0);
}

int		main(int ac, char **av)
{
	FILE	*input;
	int		status;
	int		i;

	/* Without a file argument, read from standard input. */
	if (ac == 1)
		return (solve_map(stdin));
	status = 0;
	i = 1;
	while (i < ac)
	{
		input = fopen(av[i], "r");
		if (input == NULL)
		{
			fprintf(stderr, "map error\n");
			status = 1;
		}
		else
		{
			if (solve_map(input) != 0)
				status = 1;
			fclose(input);
		}
		/* With multiple files, add a blank line after each result. */
		if (ac > 2)
			fputs("\n", stdout);
		i++;
	}
	return (status);
}
