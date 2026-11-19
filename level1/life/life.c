#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_board
{
	int		width;
	int		height;
	char	*cells;
}	t_board;

static int	parse_number(const char *text, int *number)
{
	int	digit;

	*number = 0;
	if (*text == '+')
		text++;
	if (*text == '\0')
		return (0);
	while (*text)
	{
		if (*text < '0' || *text > '9')
			return (0);
		digit = *text - '0';
		if (*number > (INT_MAX - digit) / 10)
			return (0);
		*number = *number * 10 + digit;
		text++;
	}
	return (1);
}

static int	draw_board(t_board *board)
{
	int		x;
	int		y;
	int		drawing;
	char	command;
	ssize_t	bytes_read;

	x = 0;
	y = 0;
	drawing = 0;
	bytes_read = read(STDIN_FILENO, &command, 1);
	while (bytes_read > 0)
	{
		if (command == 'x')
			drawing = !drawing;
		else if (command == 'w' && y > 0)
			y--;
		else if (command == 'a' && x > 0)
			x--;
		else if (command == 's' && y < board->height - 1)
			y++;
		else if (command == 'd' && x < board->width - 1)
			x++;
		if (drawing)
			board->cells[(size_t)y * board->width + x] = 1;
		bytes_read = read(STDIN_FILENO, &command, 1);
	}
	return (bytes_read == 0);
}

static int	count_neighbors(const t_board *board, int x, int y)
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
				&& x + dx >= 0 && x + dx < board->width
				&& y + dy >= 0 && y + dy < board->height)
				count += board->cells[(size_t)(y + dy) * board->width
					+ x + dx];
			dx++;
		}
		dy++;
	}
	return (count);
}

static void	next_generation(const t_board *board, char *next)
{
	int		x;
	int		y;
	int		neighbors;
	size_t	index;

	y = 0;
	while (y < board->height)
	{
		x = 0;
		while (x < board->width)
		{
			index = (size_t)y * board->width + x;
			neighbors = count_neighbors(board, x, y);
			next[index] = (neighbors == 3
					|| (board->cells[index] && neighbors == 2));
			x++;
		}
		y++;
	}
}

static void	print_board(const t_board *board)
{
	int	x;
	int	y;

	y = 0;
	while (y < board->height)
	{
		x = 0;
		while (x < board->width)
		{
			if (board->cells[(size_t)y * board->width + x])
				putchar('O');
			else
				putchar(' ');
			x++;
		}
		putchar('\n');
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_board	board;
	char	*next;
	char	*temporary;
	int		iterations;

	if (argc != 4 || !parse_number(argv[1], &board.width)
		|| !parse_number(argv[2], &board.height)
		|| !parse_number(argv[3], &iterations)
		|| board.width == 0 || board.height == 0)
		return (1);
	/* calloc initialise toutes les cellules a 0 (mortes). */
	board.cells = calloc((size_t)board.height, (size_t)board.width);
	next = calloc((size_t)board.height, (size_t)board.width);
	if (!board.cells || !next || !draw_board(&board))
	{
		free(board.cells);
		free(next);
		return (1);
	}
	while (iterations > 0)
	{
		next_generation(&board, next);
		/* On echange les grilles seulement quand tout le tour est calcule. */
		temporary = board.cells;
		board.cells = next;
		next = temporary;
		iterations--;
	}
	print_board(&board);
	free(board.cells);
	free(next);
	return (0);
}
