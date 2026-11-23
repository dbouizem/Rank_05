#include "life.h"

/*
1 recup arg
2 creat grid
3 print_grid
4 pen_down
5 count_nieghbers
6 next_generation 1 tour
7 all tours
*/

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

void	draw_grid(t_grid	*grid)
{
	int		x;
	int		y;
	int		draw;
	char	cmd;

	x = 0;
	y = 0;
	draw = 0;
	//'w', 'a', 's', 'd': move the pen up, left, down, and right.
	while (read(STDIN_FILENO, &cmd, 1) == 1)
	{
		if (cmd == 'x')
			draw = !draw;
		else if (cmd == 'w' && y > 0)
			y--;
		else if (cmd == 's' && y < grid->h - 1)
			y++;
		else if (cmd == 'a' && x > 0)
			x--;
		else if (cmd == 'd' && x < grid->w - 1)
			x++;
		if (draw)
			grid->c[y * grid->w + x] = 1;
	}
}

int		count_neighbors(const t_grid *grid, int x, int y)
{
	int	dx;
	int	dy;
	int	count;

	count = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
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

void	next_generation(const t_grid *grid, char *next)
{
	int	x;
	int	y;
	int	n;
	int i;

	y = 0;
	while (y < grid->h)
	{
		x = 0;
		while (x < grid->w)
		{
			i = y * grid->w + x;
			n = count_neighbors(grid, x, y);
			next[i] = (n == 3 || (n == 2 && grid->c[i]));
			x++;
		}
		y++;
	}
}

void	simulate(t_grid *grid, char *next, int iter)
{
	char	*tmp;

	while (iter > 0)
	{
		next_generation(grid, next);
		tmp = grid->c;
		grid->c = next;
		next = tmp;
		iter--;
	}
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
	grid.c = calloc((size_t)grid.w * grid.h, sizeof(char));
	if (grid.c == NULL)
		return (1);
	next = calloc((size_t)grid.w * grid.h, sizeof(char));
	if (next == NULL)
		return (free(grid.c), 1);
	draw_grid(&grid);
	simulate(&grid,next, iter);
	print_grid(&grid);

	free (grid.c);
	return (0);
}
