<br/>
<p>
  <a href="https://github.com/Ocyn/Minishell">
    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/8d/42_Logo.svg/768px-42_Logo.svg.png" alt="Logo" width="120" height="120">
  </a>

  <h1>Minishell</h1>

  <p>
    42 School Project | Made in 2024 - 2025
    <br/>
    <br/>
  </p>
</p>

![Contributors](https://img.shields.io/github/contributors/Ocyn/Minishell?color=dark-green) ![Issues](https://img.shields.io/github/issues/Ocyn/Minishell) 

## Table Of Contents

* [About the Project](#about-the-project)
* [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Authors](#authors)
* [Acknowledgements](#acknowledgements)

## About The Project

The `Minishell` project involves reproducing a working Shell like program. It must behave exactly like GNU Bash, managing environnement variables, builtin commands, pipeline, heredocument, fd redirection, etc.... The program is executed with the following format:
```bash
./Minishell
```
It take no argument.

## Project Structure

- **Source Files (`src/`):**
  - `main.c`: Main program logic and entry point.
  - `memory/`: Memory managing functions.
  - `builtin/`: builtin commands functions.
  - Other supporting files for parsing, sorting, and utility functions.

- **Header File (`header/`):**
  - Declarations of structures and function prototypes.

## Built With

* [C](https://en.wikipedia.org/wiki/C_(programming_language))

## Getting Started

**Compatibility Warning**
This project, **Minishell**, has primarily been developed and tested on a Linux Ubuntu system. It is essential to note that the project may encounter compatibility issues when executed on different operating systems. The utilization of Linux-specific features, libraries, or commands could lead to unexpected behavior on non-Linux platforms.

To ensure optimal performance and compatibility, it is recommended to run this project on a Linux environment, preferably Ubuntu. Attempting to execute the project on other operating systems may result in errors or unintended behavior.

Please consider this compatibility notice before proceeding with the compilation and execution of **Minishell**.

### Prerequisites

If you don't have Make
* Make

```sh
apt-get install build-essential make
```

### Installation

Clone the repo

```sh
git clone https://github.com/Ocyn/Minishell.git
cd Minishell/
```

### Compilation and Usage:

1. **Makefile:**
   - The project includes a Makefile with the following rules: `NAME`, `all`, `clean`, `fclean`, and `re`.

2. **Compilation:**
   - Compile the project using the provided Makefile.

  ```bash
  make
  ```

3. **Execution:**

Run the program with file names and shell commands.
```bash
./minishell
```
4. **Expected Behavior:**

The program should replicate the behavior of the specified shell command.


6. **Clean Up:**

Clean up object files and executable.
```bash
make clean
```

**Error Handling:**
- The program incorporates error handling for various scenarios, such as failed system calls, file access issues, wrong command syntax, and unexpected behavior.

**Cleanup**:
- Ensures proper cleanup by closing file descriptors, waiting for child processes to finish, and freeing allocated memory.

## Rules and Requirements:
The project must be written in C and adhere to the Norme.
Functions should not terminate unexpectedly, and no memory leaks are tolerated.
Error handling must be implemented sensibly.
The program must handle pipes, input and output redirection, and execute shell commands.
A Makefile must be provided for compilation.
Detailed instructions and examples are provided in the project description.

Follow the provided instructions in the README file for successful compilation and execution of the program.

## Authors

* **Ocyn** - *A Random Dev | 42 Student* - [Ocyn](https://github.com/Ocyn) - *Make parsing / execution / redirection part*
* **Nonomex** - *42 Student* - [Nonomex](https://github.com/nonomex) - *Made env variables / builtin commands / signals part*

## Acknowledgements

* [42 School](https://github.com/42School)
