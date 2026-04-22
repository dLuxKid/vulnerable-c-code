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

### Key Details
 
- The declaration order matters — `authenticated` must be declared before `password` so that it sits adjacent in memory where the overflow can reach it.
- The authentication check uses `!= 0` rather than `== 1`, since the overflow writes arbitrary byte values (e.g. `0x61` from the character 'a'), not exactly `1`.
- Too many characters will overwrite the return address and cause a segmentation fault. The input length needs to be just enough to corrupt `authenticated` without crashing the program.

### Testing Environment
 
This program was tested using **GitHub Codespaces** (Ubuntu). Codespaces provides a reliable Linux GCC environment where the overflow can be demonstrated.

### How to Reproduce
 
```bash
# Compile with protections disabled
gcc -o vulnerable vulnerable_program.c -fno-stack-protector -no-pie -O0
./vulnerable
# Enter between 9-12 'A' characters (e.g. AAAAAAAAA)
# The program prints "ACCESS GRANTED" without the correct password
```
 
## Fixed Program
 
The corrected version replaces `gets()` with `fgets()`, which limits input to the size of the buffer. The buffer itself is also increased to 32 bytes, and a proper password comparison using `strcmp()` is added so that authentication depends on correct input rather than memory state.
 
### How to Verify
 
```bash
# Compile with protections enabled
gcc -o fixed fixed_program.c -fstack-protector-all
./fixed
# The same oversized input no longer bypasses authentication
# Only the correct password ("password") grants access
```

## References

- [CWE-121: Stack-based Buffer Overflow](https://cwe.mitre.org/data/definitions/121.html)
- [Buffer overflow attacks in C++: A hands-on guide.](https://snyk.io/blog/buffer-overflow-attacks-in-c/)
- [Buffer Overflow.](https://www.fortinet.com/resources/cyberglossary/buffer-overflow)
- [Buffer Overflow Attack Explained with a C Program Example.](https://www.thegeekstuff.com/2013/06/buffer-overflow/) 