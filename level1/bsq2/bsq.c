#include "bsq.h"

/*
1 input
2 read header
3 read grid
4 check all ?
---
5 find square
6 fill square
7 multi file input
*/

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
		header->h = header->h * 10 + (line[i++] - '0');
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
	cap = 0;
	extra = NULL;
	if (getline(&extra, &cap, input) != -1)
	{
		free(extra);
		free_grid(grid, header->h);
	}
	free(extra);
	return (grid);
}

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
				if (x > 0 && y > 0)
					dp[i] += min_three(dp[i - 1],
						dp[i - header->w],
						dp[i - header->w - 1]);
			}
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
		if (ac > 2)
			fputs("\n", stdout);
		i++;
	}
	return (status);
}
