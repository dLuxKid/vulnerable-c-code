# Task A: Vulnerability Discovery and Remediation

## Overview

This task demonstrates a stack-based buffer overflow (CWE-121) in a simple C login program. A vulnerable version is exploited to bypass authentication without knowing the correct password, and a fixed version is provided that eliminates the flaw using secure coding practices.

## Files

| File | Description |
|---|---|
| `vulnerable_program.c` | Login program with a deliberate buffer overflow via `gets()` |
| `fixed_program.c` | Corrected version using `fgets()` with bounds checking |

## Vulnerable Program

The program declares an 8-byte password buffer and an `authenticated` flag initialised to 0. It uses `gets()` to read user input, which performs no bounds checking. By entering more than 8 characters, the input overflows into the adjacent `authenticated` variable on the stack, changing its value and granting access without the correct password.

### Testing Environment
 
This program was tested using **Windows Subsystem for Linux (WSL2 — Ubuntu)** rather than native Windows.

### How to Reproduce
 
```bash
# Run inside WSL (Ubuntu)
gcc -o vulnerable vulnerable_program.c -fno-stack-protector -no-pie -O0
./vulnerable
# Enter a string longer than 8 characters (e.g. "AAAAAAAAAAAAAAAA")
```

The program prints "ACCESS GRANTED" despite no correct password being provided.

## Fixed Program

The corrected version replaces `gets()` with `fgets()`, which limits input to the size of the buffer. The buffer itself is also increased to 32 bytes, and a proper password comparison using `strcmp()` is added so that authentication depends on correct input rather than memory state.

### How to Verify
 
```bash
# Run inside WSL (Ubuntu)
gcc -o fixed fixed_program.c -fstack-protector-all
./fixed
# The same oversized input no longer bypasses authentication
```

## References

- [CWE-121: Stack-based Buffer Overflow](https://cwe.mitre.org/data/definitions/121.html)
- [Buffer overflow attacks in C++: A hands-on guide.](https://snyk.io/blog/buffer-overflow-attacks-in-c/)
- [Buffer Overflow.](https://www.fortinet.com/resources/cyberglossary/buffer-overflow)
- [Buffer Overflow Attack Explained with a C Program Example.](https://www.thegeekstuff.com/2013/06/buffer-overflow/) 