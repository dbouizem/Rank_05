# Bigint

Implement a C++ class that stores unsigned integers with arbitrary precision. It supports addition, increment, comparison, decimal digit shifts and output without leading zeros.

The value is stored as a `std::string`, so arithmetic results can grow beyond the range of built-in integer types, subject to available memory and implementation limits.

## Files

- `bigint.hpp`: class declaration, private storage and operator declarations.
- `bigint.cpp`: constructors and operator implementations.
- `main.cpp`: example program supplied with the exercise.
- `subject.txt`: assignment requirements and reference main.

Expected submission files: **`bigint.hpp` and `bigint.cpp`**. Keep `main.cpp` for local testing.

## Compile and run

Run these commands from this directory:

```sh
c++ -Wall -Wextra -Werror -std=c++98 bigint.cpp main.cpp -o bigint
./bigint
```

The current code compiles with C++98. Expected output from the included main:

```text
a = 42
b = 21
c = 0
d = 1337
e = 1337
a + b = 63
(c += a) = 42
b = 21
++b = 22
b++ = 22
(b << 10) + 42 = 230000000042
(d <<= 4) = 13370000
(d >>= 2) = 133700
a =42
d =133700
(d < a) = 0
(d <= a) = 0
(d > a) = 1
(d >= a) = 1
(d == a) = 0
(d != a) = 1
```

`b++` prints the old value, `22`, then leaves `b` equal to `23`. This is why the next expression uses `23`.

## Representation

The private string `digit` stores decimal digits in their usual order:

```text
Value:       1337
Stored as:   "1337"
Zero:        "0"
```

Maintain these invariants:

- The string is never empty.
- Each character is a decimal digit.
- There are no leading zeros, except for zero itself, stored as `"0"`.
- Values are unsigned: negative numbers are outside the subject's scope.

These rules make comparison by length and then by string order possible.

## Supported operations

| Operation | Meaning | Modifies the left operand? |
| --- | --- | --- |
| `bigint()` | Construct zero | — |
| `bigint(unsigned long)` | Construct from a built-in unsigned value | — |
| Copy construction / `=` | Copy a value | Assignment only |
| `out << a` | Print decimal digits | No |
| `a += b` | Add `b` to `a` | Yes |
| `a + b` | Return the sum | No |
| `++a` | Increment and return the updated object by reference | Yes |
| `a++` | Increment and return a copy of the old value | Yes |
| `==`, `!=`, `<`, `>`, `<=`, `>=` | Compare values | No |
| `a <<= n` / `a << n` | Append `n` decimal zeros, except when `a` is zero | Compound form only |
| `a >>= n` / `a >> n` | Remove `n` trailing digits; return zero if none remain | Compound form only |

The number constructor is not `explicit`, so expressions such as `a + 42` and `a << 3` can convert the right operand to a `bigint`.

The two uses of `<<` have different meanings: `std::cout << a` prints a number, while `a << n` shifts its decimal digits.

## Steps to build the exercise

1. Declare the class and its private decimal string. Implement default, number and copy constructors, assignment and destructor.
2. Implement stream output so you can inspect values during testing.
3. Implement `operator+=` using digit-by-digit addition with a carry.
4. Reuse `+=` for `+`, prefix increment and postfix increment.
5. Implement equality and less-than, then derive the other comparisons.
6. Implement `<<=` and `>>=`, then reuse them for the non-modifying shifts.
7. Compile the supplied main and check zero, carries, copies, comparisons, increments and shifts.

## Addition with a carry

Start at the rightmost digit of both operands. For each position:

1. Read each available digit, or use zero if that operand is exhausted.
2. Compute `sum = left + right + carry`.
3. Append the result digit, `sum % 10`, converted back to a character.
4. Set `carry = sum / 10`.

Continue until both operands and the carry are exhausted. The result was built backwards, so reverse it before storing it.

For example, `999 + 1` produces three zeros with a carry, then a final `1`. Reversing `"0001"` gives `"1000"`.

Build the result separately before assigning it to `digit`. This also allows self-addition such as `a += a`.

## Comparison

With no leading zeros:

- A number with fewer digits is smaller: `99 < 100`.
- For equal lengths, compare the strings lexicographically: `"123" < "124"`.
- Equality compares the stored strings directly.

## Decimal digit shifts

These are base-10 digit shifts, rather than binary bit shifts:

```text
42 << 3    = 42000
1337 >> 2  = 13
42 >> 2    = 0
0 << 3     = 0
```

A left shift by `n` multiplies by `10^n`. A right shift divides by `10^n`, discarding the remainder.

Keep zero as `"0"` after a left shift. Before a right shift, compare the shift count with the number of digits: if it is at least that length, set the result to zero.

## Reuse between operators

| Core implementation | Operators that reuse it |
| --- | --- |
| `operator+=` | `operator+`, `++a`, `a++` |
| `operator==` | `operator!=` |
| `operator<` | `>`, `<=`, `>=` |
| `operator<<=` | `operator<<` |
| `operator>>=` | `operator>>` |

Compound operators return `*this` by reference. Non-modifying arithmetic and shift operators copy the object, apply the compound operation to the copy, then return it by value. Postfix increment saves a copy before modifying the original.

## Useful checks

- `0 + 0` produces `0`.
- `999 + 1` produces `1000`.
- `a += a` doubles the value.
- Copying and modifying an object leaves the original unchanged.
- Prefix increment returns the new value; postfix increment returns the old value.
- Shifting by zero leaves the value unchanged.
- Shifting right by at least the digit count produces `0`.
- Shifting zero left still prints `0`.
- Comparisons work for both equal and different digit counts.

## Current implementation limits

The constructor accepts `unsigned long`, not an arbitrary decimal string. Larger values can be built through addition and shifts.

Addition uses `int` indices, which limits the size of strings it can safely process. Left shifts convert the count to `std::size_t` without checking stream conversion failure; extremely large counts are not handled robustly and may cause allocation or length exceptions. Arbitrary precision does not imply unlimited memory.
