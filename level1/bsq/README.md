# BSQ — Biggest Square

Find the largest square containing only empty cells in a map, then replace its cells with the full symbol. If several squares have the same size, choose the topmost one, then the leftmost one.

## Files

- `bsq.c`: header and map reading, square search, filling and program entry point.
- `helper.c`: symbol and row validation, output, memory cleanup and minimum calculation.
- `bsq.h`: includes, structures and helper declarations.

## Compile and run

Run these commands from this directory:

```sh
cc -Wall -Wextra -Werror bsq.c helper.c -o bsq
./bsq map.txt
```

Without file arguments, read from standard input:

```sh
printf '3 . o x\n...\n...\n..o\n' | ./bsq
```

Expected output:

```text
xx.
xx.
..o
```

Process several files in order:

```sh
./bsq first.txt second.txt
```

When multiple files are supplied, an extra newline is written to standard output after every result, including the last one. Invalid maps produce `map error` followed by a newline on standard error; processing continues with the next file.

## Map format

The header contains the number of rows and three distinct printable symbols, separated by spaces:

```text
height empty obstacle full
```

For example:

```text
3 . o x
...
...
..o
```

Here, `.` is empty, `o` is an obstacle and `x` marks the solution. Each header separator in this implementation is exactly one space. A symbol may itself be a printable space or a digit.

A valid map must satisfy all of these rules:

- The height is positive and matches the exact number of map rows.
- Every row has the same positive width.
- Every row ends with a newline, including the last one.
- Map cells contain only the empty or obstacle symbol.
- The empty, obstacle and full symbols are printable and distinct.
- No extra rows follow the map.

An all-obstacle map is valid and is printed unchanged.

## Steps to build the exercise

1. Choose the input source: a file or standard input.
2. Read and validate the header: height and three distinct symbols.
3. Read and store the map.
4. Validate its characters, width, line endings and row count.
5. Find the largest empty square using the `dp` array.
6. Fill the square, print the map and free the memory.
7. Handle multiple files, errors and separator lines.

## How the square search works

`dp[y * width + x]` stores the size of the largest empty square whose bottom-right corner is `(x, y)`.

- An obstacle has value `0`.
- An empty cell on the first row or column has value `1`.
- Every other empty cell has value `1 + min(left, above, above-left)`.

When a larger square is found, save its size and top-left coordinates:

```c
best->x = x - best->size + 1;
best->y = y - best->size + 1;
```

Scan rows from top to bottom and columns from left to right. Update the best square only for a strictly larger size: this preserves the required priority on ties.

Fill the chosen square only after the search, so the original map remains available throughout the calculation.

Time complexity is `O(height * width)`. The stored map and `dp` array use `O(height * width)` memory.

## Memory and error handling

- Initialize the row-pointer array with `calloc` so unused pointers are null.
- Free already allocated rows if reading or validation fails.
- Reject extra rows immediately after freeing the map, without reusing freed pointers.
- Check for height overflow before multiplying by ten while parsing the header.
- Close each successfully opened file after processing it.
- Return a nonzero status if any map fails.

## Subject constraints and limits

Expected submission files: `*.c` and `*.h`.

Allowed functions and globals: `malloc`, `calloc`, `realloc`, `free`, `fopen`, `fclose`, `getline`, `fscanf`, `fputs`, `fprintf`, `stderr`, `stdout`, `stdin`, `errno`.

`_POSIX_C_SOURCE 200809L` enables the declaration of `getline` on POSIX systems.

Very large maps can overflow the `int` index calculations. The implementation also does not distinguish a stream read error from EOF when checking for extra rows. The height overflow check does not remove these separate limits.
