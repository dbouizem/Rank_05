#ifndef LIFE_H
# define LIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* c: cells (0 dead, 1 alive); w: width; h: height. */
typedef struct	s_grid
{
	char	*c;
	int		w;
	int		h;
}	t_grid;

#endif
