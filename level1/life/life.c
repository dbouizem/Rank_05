#include "life.h"

/*
** Steps to build the exercise:
** 1. Read and validate the arguments: width, height, iterations.
** 2. Allocate grid.c and next with calloc (dead cells).
** 3. Write print_grid and test the board display.
** 4. Write draw_grid to draw with the pen using commands from stdin.
** 5. Write simulation to run the generations and swap the boards.
** 6. Write next_generation to compute one generation in next.
** 7. Write count_neighbors, then test and print the final result.
**    Free both boards after use.
*/

/* Print 'O' for a live cell, otherwise a space. */
void	print_grid(t_grid *grid)
{
	int	x;
	int	y;

	y = 0;
	while (y < grid->h)
	{
		x = 0;
		while (x < grid->w)
		{
			if (grid->c[y * grid->w + x])
				putchar('O');
			else
				putchar(' ');
			x++;
		}
		putchar('\n');
		y++;
	}
}

/* Draw until EOF: the pen starts at (0, 0), lifted. */
void	draw_grid(t_grid *grid)
{
	char	cmd;
	int		x;
	int		y;
	int		draw;

	x = 0;
	y = 0;
	draw = 0;
	while (read(STDIN_FILENO, &cmd, 1) == 1)
	{
		/* x toggles drawing; movement stays within the board. */
		if (cmd == 'x')
			draw = !draw;
		else if (cmd == 'w' && y > 0)
			y--;
		else if (cmd == 'a' && x > 0)
			x--;
		else if (cmd == 's' && y < grid->h - 1)
			y++;
		else if (cmd == 'd' && x < grid->w - 1)
			x++;
		if (draw)
			grid->c[y * grid->w + x] = 1;
	}
}

/* Count the eight neighbors; cells outside the board are dead. */
int		count_neighbors(t_grid *grid, int x, int y)
{
	int	count;
	int	dx;
	int	dy;

	count = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			/* Exclude the cell itself and check the bounds. */
			if ((dx != 0 || dy != 0)
				&& (x + dx >= 0 && x + dx < grid->w)
				&& (y + dy >= 0 && y + dy < grid->h))
				count += grid->c[(y + dy) * grid->w + (x + dx)];
			dx++;
		}
		dy++;
	}
	return (count);
}

/* Read the current board and write only to the next board. */
void	next_generation(t_grid *grid, char *next)
{
	int	x;
	int	y;
	int	i;
	int	n;

	y = 0;
	while (y < grid->h)
	{
		x = 0;
		while (x < grid->w)
		{
			/* Convert coordinates (x, y) to an array index. */
			i = y * grid->w + x;
			n = count_neighbors(grid, x, y);
			/* Birth with 3 neighbors; survival with 2 or 3. */
			next[i] = (n == 3 || (n == 2 && grid->c[i]));
			x++;
		}
		y++;
	}
}

void	simulation(t_grid *grid, char *next, int iter)
{
	char	*tmp;

	while (iter > 0)
	{
		next_generation(grid, next);
		/* Swap the boards once the entire generation has been computed. */
		tmp = grid->c;
		grid->c = next;
		next = tmp;
		iter--;
	}
	/* After swapping, next points to the unused work board. */
	free(next);
}

int	main(int ac, char **av)
{
	t_grid	grid;
	char	*next;
	int		iter;

	if (ac != 4)
		return (1);
	grid.w = atoi(av[1]);
	grid.h = atoi(av[2]);
	iter = atoi(av[3]);
	if (!(grid.w > 0 && grid.h > 0 && iter >= 0))
		return (1);
	/* calloc initializes every cell to 0: all cells are dead. */
	grid.c = calloc((size_t)grid.h * grid.w, sizeof(char));
	if (!grid.c)
		return (1);
	next = calloc((size_t)grid.h * grid.w, sizeof(char));
	if (!next)
		return (free(grid.c), 1);
	draw_grid(&grid);
	simulation(&grid, next, iter);
	print_grid(&grid);

	/* grid.c holds the final generation, which has already been printed. */
	free(grid.c);
	return (0);
}
