# Build and Run Guide

This repository contains a simple setup for building and running a project. Follow the steps below to execute the provided `project.sh` script and then run the build.

---

## Prerequisites

Ensure you have the following installed on your system:

- **Bash**: The `project.sh` script requires a Bash-compatible shell.
- **Necessary Packages**: `sudo apt-get install libssl-dev` are needed to test against SHA-1 implementation
- **Compiler/Dependencies**: Make sure you have the necessary tools (e.g., GCC, Clang, or any language-specific build tools) to compile the code.

---

## Instructions

### 1. Make the `build.sh` Script Executable

Before running the script, ensure it has executable permissions. Open a terminal and navigate to the project directory, then run:

```bash
chmod +x project.sh
 
 ./project.sh

```
---

## Whats Included

I created two sets of the SHA-1 and DJB2 files one shows steps of the hashing process and one that is used for running the test cases. The non-testing files are used to show what is being done each step of the hashing process by outputting the binary. The testing files do not output any steps and only return a string for comparison for testing.


## Testing

For testing DJB2 we will run two instances of the DJB2 and compare the hash values with the same input. 

For testing SHA-1 we will use a well known SHA-1 library to test against my implementation of SHA-1. We will run both algorithms with the same input expecting the same output hash.






