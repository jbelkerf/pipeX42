# Pipex

Pipex is a project that replicates the behavior of piping (`|`) in a Unix shell. It takes multiple commands, executes them in sequence while redirecting their input and output properly through pipes. This project is part of the 42 curriculum.

## Features

- Simulates shell piping (`|`) in C
- Supports multiple commands
- Handles here-document (`<<`) functionality
- Works with absolute and relative command paths
- Supports environment path resolution
- Mimics Bash behavior

## System Calls Used

Pipex interacts with the operating system using the following system calls:

- `open()` - Opens files for reading or writing
- `close()` - Closes file descriptors
- `read()` - Reads from a file descriptor
- `write()` - Writes to a file descriptor
- `malloc()` / `free()` - Memory allocation and deallocation
- `perror()` / `strerror()` - Error handling and debugging
- `access()` - Checks file permissions
- `dup()` / `dup2()` - Duplicates file descriptors
- `execve()` - Executes a command
- `exit()` - Exits the program
- `fork()` - Creates a child process
- `pipe()` - Creates a pipe for interprocess communication
- `unlink()` - Removes a file (used for here-document)
- `wait()` / `waitpid()` - Waits for child processes to terminate

## Installation

To compile and use Pipex, clone this repository and run:

```sh
make
```

This will generate the `pipex` executable.

## Usage

### Basic Pipe Usage

```sh
./pipex infile "cmd1" "cmd2" outfile
```

Equivalent to:

```sh
< infile cmd1 | cmd2 > outfile
```

Example:

```sh
./pipex input.txt "cat" "wc -l" output.txt
```

### Here-Document Mode

```sh
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```

Equivalent to:

```sh
echo "text" | cmd1 | cmd2 >> outfile
```

## File Structure

- `Makefile` – Compilation rules
- `header.h` – Header file with function prototypes
- `pipex.c` – Main logic for standard pipe execution
- `pipex_bonus.c` – Extended functionality with here-document handling
- `pipex_utils.c` – Helper functions for process management
- `pipex_utils1.c` – Additional utility functions
- `check_cmd.c` – Command validation and execution
- `here_doc.c` – Handles here-document mode (`<<`)
- `ft_split2.c` – Custom string splitting function for argument parsing
- `ft_split3.c` – Specialized parsing method for handling `awk` command
- `execute.sh` – Script to compare Pipex with Bash behavior
- `libft/` – Custom library used in the project
- `get_the_next_line/` – Helper function for reading input
- `pipex.pdf` – Project subject documentation

## Example

```c
#include "header.h"

int main(int argc, char **argv, char **envp) {
    if (argc >= 5)
        return (pipex(argc, argv, envp));
    return (1);
}
```

## Contributing

If you want to contribute, fork the repository, make changes, and submit a pull request.

## License

This project is open-source under the MIT License.

## Author

Developed by Jaouad Belkerf (jbelkerf) as part of the 42 curriculum.

