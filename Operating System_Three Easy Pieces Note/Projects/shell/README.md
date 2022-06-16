# 【Project】artsh

### 1. Program Specification

My shell is called `artsh`. It is an interactive loop: repeatedly prints a prompt `artsh>`, parses the input, executes the command specified on that line of input, and waits for the command to finish.

This is repeated  until `exit` is called.

The shell can be invoked with 0 or a single argument; anything else is an error.

```bash
$ ./artsh
artsh>
```

The mode above is called interactive mode.

The shell also supports a batch mode, which reads input from a batch file and executes commands from therein.

```bash
$ ./artsh batch.txt
```

One difference between the interactive and batch mode is that no prompt(`artsh>`) should be printed.

The shell should create a process for each new command.

### 2. Structure

**2.1 Basic Shell**

For reading lines of input, we use `getline()`. 

Generally, the shell will run in interactive mode. The shell also supports batch mode, in which case it should not read user input from `stdin` but rather from this file to get the commands to execute.

In either mode, if the user hits the end-of-file marker(EOF), `exit(0)` is called and exit gracefully.

To parse the input line into constituent pieces, we use `strsep()`. 

To execute commands, we use `fork()`, `exec()`, and `wait()`/`waitpid()`.

We use `execv()`. If `execv()` is successful, it will not return. If it returns, there is an error.

**2.2 Path**

The user must specify a `path` variable to describe the set of directories to search for executables; the set of directories that comprise the path are sometimes called the search path of the shell.

**2.3 Built-in Commands**

When the shell accepts a command, it checks whether the command is a built-in command or not. If it is a built-in command, it should not be executed like other programs.

In our shell, we implemented `exit`, `cd`, and `path` as built-in commands.

- `exit`: When the user types exit, our shell should simply call the exit system call with 0 as a parameter. It is an error to pass any arguments to exit.
- `cd`: cd always take one argument(0 or >1 arguments should be signalled as an error). To change directories, use the `chdir` system call with the argument supplied by the user; if `chdir` fails, that is also an error.
- `path`: The path command takes 0 or more arguments, with each argument separated by whitespace from the others. A typical usage would be `artsh> path /bin /usr/bin`, which would add `/bin` and `/usr/bin` to the search path of the shell.

**2.4 Redirection**

Our shell provides a nice feature to redirect wit the `>` character. The standard error output of the program is rerouted to the file output.

If the file doesn’t exist, the shell creates it(after truncating it).

**2.5 Parallel Commands**

Our shell will allow the user to launch parallel commands. 

```bash
artsh> cmd1 & cmd2 args1 args2 & cmd3 args1
```

Th shell run `cmd1`, `cmd2`, and `cmd3` in parallel, before waiting for any of them to complete.

**2.6 Program Errors**
Only this error message is printed:

```bash
char error_message[30] = "An error has occurred\n";
write(STDERR_FILENO, error_message, strlen(error_message));
```

After most errors, tje shell simply *continue processing* after printing the one and only error message. However, if the shell is invoked with more than one file, or if the shell is passed a bad batch file, it should exit by calling `exit(1)`
