#ifndef BSQ_H
# define BSQ_H

# define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
# include <stdio.h>

typedef struct s_header
{
	int		h;
	int		w;
	char	e;
	char	o;
	char	f;
}	t_header;

typedef struct	s_square
{
	int		x;
	int		y;
	int		size;
}	t_square;

int		read_symbol(char *line, int *i, char *s);

void	free_grid(char **grid, int count);
int		check_row(char *row, t_header *header, int y);

int		min_three(int a, int b, int c);

void	print_grid(char	**grid, t_header *header);

#endif
