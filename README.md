# sish — A Simple Shell in C

A minimal Unix shell written in C, built as a first systems programming project. Supports command execution, dynamic input buffering, and a clean exit.

---

## Features

- **Command execution** — runs any program available in your `PATH` using `execvp`
- **Dynamic input buffering** — handles arbitrarily long input lines by reallocating memory as needed (Handalled by using `getline`)
- **Tokenization** — splits input on spaces, tabs, and newlines using `strtok`
- **Graceful exit** — type `exit` to quit the shell cleanly
- **built-in `cd` command** — directory changes possible

---

## Installation & Usage

**Requirements:**
- GCC
- A Unix-like OS (Linux / macOS)

**Build:**
```bash
gcc shell.c -o sish
```

**Run:**
```bash
./sish
```

**Example:**
```
> ls -la
> echo hello world
> exit
> mkdir
```

---

## Known Limitations & Future Objectives

- No support for piping (`|`) or I/O redirection (`>`, `<`)
- No command history
- Empty input (pressing Enter) previously caused a crash — fixed with a null guard on `args[0]`
