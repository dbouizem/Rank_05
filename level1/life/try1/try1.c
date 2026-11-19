#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	print_grid(char *grid, int w, int h)
{
	// 'O' ' ' '\n'
	int	x;
	int	y;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (grid[y * w + x] == 1)
				putchar('O');
			else
				putchar(' ');
			x++;
		}
		putchar('\n');
		y++;
	}
}

void	pen_down(char *grid, int w, int h)
{
	// 'x' 'w' 's' 'a' 'd'
	int		x;
	int		y;
	int		pen_down;
	char	cmd;

	x = 0; //
	y = 0; //
	pen_down = 0;
	while (read(STDIN_FILENO, &cmd, 1) == 1)
	{
		if (cmd == 'x')
			pen_down = !pen_down;
		else if (cmd == 'w' && y > 0 )
			y--;
		else if (cmd == 's' && y < h - 1)
			y++;
		else if (cmd == 'a' && x > 0)
			x--;
		else if (cmd == 'd' && x < w - 1)
			x++;
		if (pen_down == 1)
			grid[y * w + x] = 1;
	}
}

int		count_nieghbers(char *grid, int w, int h, int x, int y)
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
			&& (x + dx >= 0 && x + dx < w)
			&& (y + dy >= 0 && y + dy < h))
			{
				count += grid[(y + dy) * w + (x + dx)];
			}
			dx++;
		}
		dy++;
	}
	return count;
}

void	next_generation(char *grid, char *next, int w, int h)
{
	int	x;
	int	y;
	int	n; //nieghbers

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			n = count_nieghbers(grid, w, h, x, y);
			if (n == 3)
				next[y * w + x] = 1;
			else if (n == 2 && grid[y * w + x] == 1)
				next[y * w + x] = 1;
			else
				next[y * w + x] = 0;
			x++;
		}
		y++;
	}
}

int		main(int ac, char **av)
{
	int		w;
	int		h;
	int		etir;
	char	*grid;
	char	*next;
	char	*tmp;

	if (ac !=4)
		return 1;
	w = atoi(av[1]);
	h = atoi(av[2]);
	etir = atoi(av[3]);
	if (!(w > 0 && h > 0 && etir >= 0))
		return 1;
	grid = calloc((size_t)w * h, sizeof(char));
	if (grid == NULL)
		return 1;
	next = calloc((size_t) w * h, sizeof(char));
	if (next == NULL)
	{
		free(grid);
		return 1;
	}
	pen_down(grid, w, h);
	while (etir > 0)
	{
		next_generation(grid, next, w, h);
		tmp = grid;
		grid = next;
		next = tmp;
		etir--;
	}
	print_grid(grid, w, h);
	free(next);
	free(grid);
	return 0;
}
