#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
/*
1 choisire source de lecture
2 lire et verifier le header
3 lire et stocker la grid
4 verifier la grille
----
5 trouver la plus grand carre
6 remplir et afficher le carre
7 gerer plusieurs fichier et verifier l'ensemble
*/

typedef struct s_header
{
	int		h;
	int		w;
	char	e;
	char	o;
	char	f;
}	t_header;

/* Position du coin en haut à gauche et taille du carré trouvé. */
typedef struct s_square
{
	int	x;
	int	y;
	int	size;
}	t_square;

/* Libérer les lignes, puis le tableau de pointeurs. */
void	free_grid(char **grid, int count)
{
	int	y;

	y = 0;
	while (y < count)
		free(grid[y++]);
	free(grid);
}

/* Lire un espace suivi d'un caractère imprimable. */
int	read_symbol(char *line, int *i, char *s)
{
	if (line[*i] != ' '
		|| line[*i + 1] < 32 || line[*i + 1] > 126)
		return (-1);
	*s = line[*i + 1];
	*i += 2;
	return (0);
}

/* Lire et vérifier l'en-tête. */
int	read_header(FILE *input, t_header *header)
{
	char	*line;
	size_t	cap;
	int		i;

	// Lire la première ligne.
	line = NULL;
	cap = 0;
	if (getline(&line, &cap, input) == -1)
		return (free(line), -1);

	// Lire la hauteur.
	header->h = 0;
	i = 0;
	while (line[i] >= '0' && line[i] <= '9')
		header->h = header->h * 10 + (line[i++] - '0');
	if (header->h <= 0)
		return (free(line), -1);

	// Lire les trois symboles.
	if (read_symbol(line, &i, &header->e) == -1
		|| read_symbol(line, &i, &header->o) == -1
		|| read_symbol(line, &i, &header->f) == -1)
		return (free(line), -1);

	// Vérifier que les symboles sont différents.
	if (header->e == header->o
		|| header->e == header->f
		|| header->o == header->f)
		return (free(line), -1);

	// Vérifier la fin de l'en-tête.
	if (line[i] != '\n' || line[i + 1] != '\0')
		return (free(line), -1);

	free(line);
	return (0);
}

/* Vérifier les caractères, la largeur et la fin d'une ligne. */
int	check_row(char *row, t_header *header, int y)
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
	if (x == 0 || x != header->w || row[x] != '\n')
		return (-1);
	return (0);
}

/* Lire, stocker et vérifier la grille. */
char	**read_grid(FILE *input, t_header *header)
{
	char	**grid;
	char	*extra;
	size_t	cap;
	int		y;

	// Allouer le tableau de pointeurs.
	grid = calloc((size_t)header->h, sizeof(char *));
	if (grid == NULL)
		return (NULL);

	// Lire et vérifier les lignes attendues.
	y = 0;
	while (y < header->h)
	{
		cap = 0;
		if (getline(&grid[y], &cap, input) == -1
			|| check_row(grid[y], header, y) == -1)
			return (free_grid(grid, y + 1), NULL);
		y++;
	}

	// Vérifier qu'il n'y a pas de ligne supplémentaire.
	extra = NULL;
	cap = 0;
	if (getline(&extra, &cap, input) != -1)
	{
		free(extra);
		return (free_grid(grid, header->h), NULL);
	}
	free(extra);
	return (grid);
}

/* Renvoyer le plus petit des trois nombres. */
int	min_three(int a, int b, int c)
{
	if (b < a)
		a = b;
	if (c < a)
		a = c;
	return (a);
}

/* Chercher le carré sans modifier la grille. */
int	find_square(char **grid, t_header *header, t_square *best)
{
	int	*dp;
	int	x;
	int	y;
	int	i;

	best->x = 0;
	best->y = 0;
	best->size = 0;
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
			/* dp[i] : taille du carré qui se termine en (x, y). */
			if (grid[y][x] == header->e)
			{
				dp[i] = 1;
				if (x > 0 && y > 0)
					dp[i] += min_three(dp[i - 1], dp[i - header->w],
							dp[i - header->w - 1]);
			}
			/* En cas d'égalité, garder le premier carré rencontré. */
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

/* Remplir le carré à partir de son coin en haut à gauche. */
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

/* Chaque ligne contient déjà son retour à la ligne. */
void	print_grid(char **grid, t_header *header)
{
	int	y;

	y = 0;
	while (y < header->h)
	{
		fputs(grid[y], stdout);
		y++;
	}
}

/* Lire, résoudre, afficher et libérer une carte. */
int	solve_map(FILE *input)
{
	t_header	header;
	int			status;
	char		**grid;
	t_square	best;

	// Lire l'en-tête, puis la grille.
	status = read_header(input, &header);
	grid = NULL;
	if (status == 0)
		grid = read_grid(input, &header);

	// Vérifier le résultat des lectures.
	if (status == -1 || grid == NULL)
		return (fprintf(stderr, "map error\n"), 1);

	// Chercher le plus grand carré.
	if (find_square(grid, &header, &best) == -1)
		return (free_grid(grid, header.h),
			fprintf(stderr, "map error\n"), 1);

	// Remplir le carré, puis afficher la carte finale.
	fill_square(grid, &header, &best);
	print_grid(grid, &header);

	// Libérer la grille.
	free_grid(grid, header.h);
	return (0);
}

int	main(int ac, char **av)
{
	FILE	*input;
	int		i;
	int		status;

	if (ac == 1)
		return (solve_map(stdin));
	i = 1;
	status = 0;
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
		// Ajouter une ligne vide après chaque résultat en mode multi-fichiers.
		if (ac > 2)
			fputs("\n", stdout);
		i++;
	}
	return (status);
}
