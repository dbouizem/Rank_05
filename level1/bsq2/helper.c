#include "bsq.h"

int		read_symbol(char *line, int *i, char *s)
{
	if (line[*i] != ' ' || line[*i + 1] < 32 || line[*i + 1] > 126)
		return (-1);
	*s = line[*i + 1];
	*i += 2;
	return (0);
}

void	free_grid(char **grid, int count)
{
	int	y;

	y = 0;
	while (y < count)
	{
		free(grid[y]);
		y++;
	}
	free(grid);
}

int		check_row(char *row, t_header *header, int y)
{
	int	x;

	x = 0;
	while (row[x] != '\0' && row[x] != '\n')
	{
		if (row[x] != header->e && row[x] != header->o)
			return (-1);
		x++;
	}
	if (y == 0)
		header->w = x;
	if (x == 0 || header->w != x || row[x] != '\n')
		return (-1);
	return (0);
}

void	print_grid(char **grid, t_header *header)
{
	int y;

	y = 0;
	while (y < header->h)
	{
		fputs(grid[y], stdout);
		y++;
	}
}

int		min_three(int a, int b, int c)
{
	if (a > b)
		a = b;
	if (a > c)
		a = c;
	return (a);
}
