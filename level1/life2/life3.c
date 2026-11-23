#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
1 arg
2 alloc grid.c next
3 print test
4 draw_grid (put_pen)
5 simulation (all tours)
-> next_generation
-> count_neighbors
6
7 print
*/

typedef struct	s_grid
{
	char	*c;
	int		w;
	int		h;
}	t_grid;

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
		if (cmd == 'x')
			draw = !draw;
		// 'w', 'a', 's', 'd'
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

int		count_neighbors(t_grid *grid, int x, int y)
{
	int	count;
	int	dx;
	int	dy;

	count = 0;//
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if ((dx != 0 || dy != 0)
				&& (x + dx >= 0 && x + dx < grid->w)
				&& (y + dy >= 0 && y + dy < grid->h))// != >= <
				count += grid->c[(y + dy) * grid->w + (x + dx)];
			dx++;
		}
		dy++;
	}
	return (count);
}

void	next_generation(t_grid *grid, char *next)//
{
	int	x;
	int	y;
	int	i;
	int	n;

	i = 0;
	y = 0;
	while (y < grid->h)
	{
		x = 0;
		while (x < grid->w)
		{
			i = y * grid->w + x;
			n = count_neighbors(grid, x, y);//
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
	{	next_generation(grid, next);
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

	//args
	if (ac != 4)
		return (1);
	grid.w = atoi(av[1]);
	grid.h = atoi(av[2]);
	iter = atoi(av[3]);
	if (!(grid.w > 0 && grid.h > 0 && iter >= 0))
		return (1);
	//calloc grid.c && next
	grid.c = calloc((size_t)grid.w * grid.h, sizeof(char));//
	if (grid.c == NULL)
		return (1);
	next = calloc((size_t)grid.w * grid.h, sizeof(char));//
	if (next == NULL)
		return (free(grid.c), 1);
	//draw_grid
	draw_grid(&grid);
	//simulation
	simulation(&grid, next, iter);//
	// print
	print_grid(&grid);

	free(grid.c);
	return (0);
}
