# CPRINTF Library

`cprintf` is a header-only C library that adds ANSI colours and attributes to `printf` without having to write the full code out. This makes it easy to add coloured and styled text to your terminal output.

---

## FEATURES

- Header-only library
- Supports ANSI colours for foreground and background
- Supports various text attributes
- Easy integration with existing code

---

## INSTALLATION

Simply include the `cprintf.h` header file in your project.

---

## USAGE

To use `cprintf`, define `CPRINTF_IMPLEMENTATION` before including the header file in one of your source files.

```C
#define CPRINTF_IMPLEMENTATION
#include "cprintf.h"
```

Then, you can use cprintf in your code just like printf, but with additional formatting options.

Aditionally, you can enable/disable colored output with: `cprintf_enable`, `cprintf_disable`, and `cprintf_toggle`. The default behavior is enabled, this can be overwritten by defining `CPRINTF_ENABLE_FLAG_DEFAULT` to either `0` (disabled) or `1` (enabled).

```C
#define CPRINTF_IMPLEMENTATION
#define CPRINTF_ENABLE_FLAG_DEFAULT 0
#include "cprintf.h"
```

---

## EXAMPLE

```C
#define CPRINTF_IMPLEMENTATION
#include "cprintf.h"

int main(int argc, char * argv[]) {
    cprintf("%FbBLUE TEXT%Ar\n");

    cprintf_disable();
    cprintf("%FbNORMAL TEXT%Ar\n");

    cprintf_enable();
    cprintf("%FbBLUE TEXT%Ar\n");
    return 0;
}
```

---

## FORMATING OPTIONS

### FOREGROUND COLOURS

- **%Fk**: Black

- **%Fr**: Red

- **%Fg**: Green

- **%Fy**: Yellow

- **%Fb**: Blue

- **%Fm**: Magenta

- **%Fc**: Cyan

- **%Fw**: White

### BACKGROUND COLOURS

- **%Bk**: Black

- **%Br**: Red

- **%Bg**: Green

- **%By**: Yellow

- **%Bb**: Blue

- **%Bm**: Magenta

- **%Bc**: Cyan

- **%Bw**: White

### ATTRIBUTES

- **%Ar**: Reset

- **%Ab**: Bold

- **%Af**: Dim

- **%Ai**: Italic

- **%Au**: Underline

- **%Al**: Blink (slow)

- **%Ak**: Blink (rapid)

- **%Av**: Inverted

- **%Ah**: Hidden

- **%As**: Strikethrough

---

## LICENSE

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## CONTRIBUTING

Feel free to submit issues and pull requests. Contributions are welcome!
