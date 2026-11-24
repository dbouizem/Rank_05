# Life

Draw an initial board using commands from standard input, then simulate Conway's Game of Life for a given number of generations.

## Files

- `life.c`: drawing, simulation, output and program entry point.
- `life.h`: includes and the `t_grid` structure.

## Compile and run

Run these commands from this directory:

```sh
cc -Wall -Wextra -Werror life.c -o life
printf 'dxss' | ./life 3 3 1
```

Expected output, shown with `cat -e` (`$` marks each newline):

```sh
printf 'dxss' | ./life 3 3 1 | cat -e
```

```text
   $
OOO$
   $
```

Usage:

```sh
./life width height iterations
```

Width and height must be positive; iterations must be zero or greater. The program reads commands until EOF before running the simulation. For interactive input, finish with Ctrl+D on an empty line.

## Drawing commands

The pen starts at the top-left cell `(0, 0)`, with drawing disabled.

| Command | Action |
| --- | --- |
| `w` | Move up |
| `a` | Move left |
| `s` | Move down |
| `d` | Move right |
| `x` | Toggle drawing on or off |

The pen stays still when a move would leave the board. Unknown commands are ignored. While drawing is enabled, the current cell becomes alive; enabling drawing also marks the current cell. Drawing never erases a live cell.

Use zero iterations to inspect the drawing before simulation:

```sh
printf 'sdxddssaaww' | ./life 5 5 0 | cat -e
```

Expected output (`$` marks each newline):

```text
     $
 OOO $
 O O $
 OOO $
     $
```

## Game rules

Each cell has up to eight neighbors. Cells outside the board are dead; the board does not wrap around.

- A dead cell becomes alive with exactly three live neighbors.
- A live cell survives with two or three live neighbors.
- All other cells are dead in the next generation.

All cells change simultaneously. Read from `grid.c` and write into `next`, then swap the two pointers after completing a generation. Print live cells as `O`, dead cells as spaces, and a newline after each row.

## Steps to build the exercise

1. Read and validate the arguments: width, height, iterations.
2. Allocate `grid.c` and `next` with `calloc` to initialize dead cells.
3. Write `print_grid` and test the board display.
4. Write `draw_grid` to process pen commands from standard input.
5. Write `simulation` to run generations and swap the boards.
6. Write `next_generation` to compute one complete generation in `next`.
7. Write `count_neighbors`, then test drawing and simulation together. Free both boards after use.

This is a construction order: steps 5 and 6 can call functions implemented later. The execution order is drawing, simulation, then output.

## Key implementation details

- A flat array stores the board: the index of `(x, y)` is `y * grid->w + x`.
- `count_neighbors` excludes the cell itself and checks bounds before accessing neighbors.
- `next[i] = (n == 3 || (n == 2 && grid->c[i]))` implements birth and survival.
- `simulation` frees the unused work board. `main` prints and frees the final board.

Time complexity is `O(width * height * iterations)` for simulation, plus input and output. Memory usage is `O(width * height)`.

## Subject constraints and limits

Expected submission files: `*.c` and `*.h`.

Allowed functions: `atoi`, `read`, `putchar`, `malloc`, `calloc`, `realloc`, `free`.

The current implementation uses `atoi`, so it does not strictly validate numeric strings. Very large dimensions can overflow the `int` index calculations. A read error is treated like the end of input. Use valid numeric arguments and dimensions that fit the index range and available memory.
