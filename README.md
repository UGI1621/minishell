*This project has been created as part of the 42 curriculum by saan.*

# Description

This project implements a simple shell, modeled after bash.
It reads a command line from the user, parses it, and executes the commands with their pipes and redirections.

## 1. Project Goal

Understand how a shell works internally: processes, file descriptors, pipes, signals, and environment variables.

## 2. Process

When the program is executed, it shows the `minishell> ` prompt and waits for input using `readline`.
Every non-empty line is added to the history.

The input line is handled in the following order.

1. **Validation**<br>
   Lines with unclosed quotes, `\` or `;` are rejected as a syntax error (exit status 2).

2. **Lexing**<br>
   The line is split into tokens (words, `|`, `<`, `>`, `<<`, `>>`).
   Environment variables (`$VAR`, `$?`) are expanded, and quotes are removed.

3. **Command listing**<br>
   Tokens are grouped into a list of command nodes separated by `|`.
   Each node holds its `argv`, input/output files and redirection types.

4. **Heredoc**<br>
   Every `<<` is processed in a child process before execution.
   Variables inside a heredoc are expanded only when the delimiter is not quoted.

5. **Execution**<br>
   A single built-in command runs in the parent process, so that commands like `cd`, `export` and `exit` affect the shell itself.
   Otherwise, a child process is forked for each command, connected with pipes, and executed through `execve` after searching `PATH`.
   The exit status of the last command is stored and can be read with `$?`.

## 3. Features

Redirections
---

`<` : Redirect input<br>
`>` : Redirect output<br>
`<<` : Heredoc<br>
`>>` : Redirect output in append mode<br>

Built-in commands
---

`echo` with option `-n`<br>
`cd` with a relative or absolute path<br>
`pwd` with no options<br>
`export` with no options<br>
`unset` with no options<br>
`env` with no options or arguments<br>
`exit` with no options<br>

Signals
---

Ctrl-C : Display a new prompt on a new line<br>
Ctrl-D : Exit the shell<br>
Ctrl-\ : Do nothing<br>

## 4. Notes

Special characters not required by the subject, such as `\` and `;`, are not supported.

`&&`, `||` and wildcards (`*`) are not supported.

Heredoc input is stored in a temporary file named `heredoc_temp` in the current directory, and it is removed after the command finishes.

# Instructions

The `readline` library is required.
On Debian/Ubuntu, it can be installed with the command below.

```bash
sudo apt install libreadline-dev
```

Open a terminal in the root folder of the project.

```bash
make
```
Use the command above to compile the program.

```bash
./minishell
```
Use the command above to run the program. It takes no arguments.

```bash
make clean
```
This command removes the object files.

```bash
make fclean
```
This command removes both the object files and the program executable.

```bash
make re
```
This command rebuilds the program from scratch.

Memory check
---

`readline` itself has memory that is never freed, so a suppression file is included.

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=no --suppressions=readline.supp ./minishell
```

# Resource

[Bash Reference Manual]<https://www.gnu.org/software/bash/manual/bash.html><br>
[GNU Readline Library]<https://tiswww.case.edu/php/chet/readline/rltop.html><br>
`man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`, `man 2 waitpid`, `man 7 signal`, `man 3 termios`<br>
<br><br>

# AI Usage

AI was used for:

__Translating and writing this README__<br>
