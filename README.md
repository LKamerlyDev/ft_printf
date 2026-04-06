*This project has been created as part of the 42 curriculum by lcamerly.*

# ft_printf

## Description

`ft_printf` is a reimplementation of the C standard library function `printf`. The goal is to produce a static library `libftprintf.a` that can be linked into any C project as a drop-in replacement for the real `printf`.

The project comes in two versions:

- **Standard** (`make all`): supports the core conversion specifiers `%c`, `%s`, `%d`, `%i`, `%u`, `%x`, `%X`, `%p`, and `%%`.
- **Bonus** (`make bonus`): adds full support for the flags `-`, `0`, `.` (precision), minimum field width, `+`, ` ` (space), and `#`.

The library is built on top of **libft**, a personal re-implementation of a subset of the C standard library that is compiled and archived together with the printf object files.

---

## Instructions

### Requirements

- `cc` (clang or gcc)
- GNU `make`

### Compilation

```bash
# Build the standard library
make

# Build the bonus (flag-aware) library
make bonus

# Remove object files
make clean

# Remove object files and the library
make fclean

# Full rebuild
make re
```

Both targets produce `libftprintf.a` at the root of the repository.

### Linking with your project

```bash
cc main.c -L. -l:libftprintf.a -I includes/ -I libft/
```

### Running the test suite

```bash
make test
```

This clones [ft_printf_tester](https://github.com/paulo-santana/ft_printf_tester) and runs it against the bonus build automatically.

---

## Usage Examples

```c
#include "ft_printf.h"

int main(void)
{
    // Basic types
    ft_printf("Hello, %s!\n", "world");
    ft_printf("Decimal: %d | Unsigned: %u\n", -42, 42u);
    ft_printf("Hex lower: %x | Hex upper: %X\n", 255, 255);
    ft_printf("Pointer: %p\n", (void *)main);

    // Bonus flags
    ft_printf("[%10d]\n",  42);      // right-aligned, width 10
    ft_printf("[%-10d]\n", 42);      // left-aligned
    ft_printf("[%010d]\n", 42);      // zero-padded
    ft_printf("[%+d]\n",   42);      // explicit sign
    ft_printf("[%.5d]\n",  42);      // precision
    ft_printf("[%#x]\n",   255);     // alternate form → 0xff

    return (0);
}
```

---

## Algorithm and Data-Structure Design

### Parsing pipeline

`ft_printf` processes the format string one character at a time inside a single `while` loop. When a `%` is encountered, control is handed to `ft_args_process`, which advances the pointer and runs three sequential parsing steps before dispatching to the appropriate print function:

1. **Flag parsing** (`ft_procest_flags`) — consumes any combination of `-`, `0`, `+`, ` `, and `#` and records them as individual fields inside a `t_flag` struct.
2. **Width parsing** (`ft_process_width`) — reads an optional decimal integer and stores it as `flags.justify`.
3. **Precision parsing** (`ft_process_precision`) — reads an optional `.n` sequence and stores it as `flags.precision` (defaulting to `-1` when absent so that "no precision" and "precision zero" can be distinguished).

This strict left-to-right, single-pass approach mirrors how the real `printf` parser works and avoids backtracking entirely.

### String-building strategy

Rather than writing directly to the file descriptor during number formatting, each conversion first builds a heap-allocated string representation of the value, then passes it through a single padded-output function (`ft_print_padded`). This two-phase design keeps padding logic in one place and makes precision handling straightforward:

- `ft_precision_pad` reallocates the string with leading zeros inserted between an optional sign/prefix and the numeric digits.
- `ft_handle_zero_precision` replaces a zero value with an empty string when `%.0d` is requested, which is the specified POSIX behaviour.
- `ft_print_padded` then applies field-width padding (spaces or zeros) and respects the `-` flag for left-alignment.

For hexadecimal output, `putnbr_base` is a small recursive function that converts any unsigned integer to an arbitrary base by building the digit string directly into a caller-supplied buffer, avoiding an extra allocation.

### Error propagation

All `write(2)` calls are wrapped in `ft_write`, which sets `flags->errno` on failure and returns `-1`. Callers propagate this upward by returning early when the count is negative. The main loop checks the flag after every conversion and breaks with `return -(flags.errno)` if an error is detected, so the caller receives a negative return value just as `printf` would on a write error.

### Standard vs. bonus split

The Makefile compiles either `src/` or `src_bonus/` and links the result into `libftprintf.a`. The only file that differs meaningfully between the two is `args_process*.c`: the standard version skips flag/width/precision parsing entirely (it just fast-forwards past those characters), while the bonus version calls the three parsing helpers in sequence. All other files are functionally identical copies.

---

## Resources

### Official documentation and references

- [printf IBM](https://www.ibm.com/docs/fr/i/7.6.0?topic=output-printf)
- [Tester 1](https://github.com/paulo-santana/ft_printf_tester)
- [Tester 2](https://github.com/Tripouille/printfTester)


### Use of AI

AI (Claude mainly) was used during this project for the following tasks:

- **Debugging edge cases**: discussing the expected output of combinations such as `%-0.*d` with conflicting flags, and verifying that the implementation matched the POSIX specification.
- **Error-handling review**: analysing the `ft_write` wrapper and the sticky-error pattern to ensure negative return values propagated correctly through all code paths.
- **Writing this README**: the structure, wording, and technical explanations in this document were drafted with AI assistance and then reviewed and verified against the actual source code.
