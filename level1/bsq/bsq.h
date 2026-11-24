#ifndef BSQ_H
# define BSQ_H

#define _POSIX_C_SOURCE 200809L

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>

/* h/w: height/width; e/o/f: empty/obstacle/full symbols. */
typedef struct s_header
{
	int		h;
	int		w;
	char	e;
	char	o;
	char	f;
}	t_header;

/* Top-left position and size of the best square. */
typedef struct s_square
{
	int		size;
	int		x;
	int		y;
}	t_square;

int		read_symbol(char *line, int *i, char *s);
void	free_grid(char **grid, int count);
int		check_row(char *row, t_header *header, int y);
int		min_three(int a, int b, int c);
void	print_grid(char **grid, t_header *header);

#endif
