# Byteshell

> **Parikshit Ramchandra Sahu, BTech 3rd year, ECE, IIT Roorkee**

This is a simple shell program implemented in C. It provides a basic command-line interface with several built-in commands and additional features.

## Introduction to shell and it's operations

### Basic shell concept

In the context of an operating system, a shell is a program that serves as a command interpreter. It provides a user-friendly interface for interacting with the operating system by accepting and executing commands. The shell acts as an intermediary between the user and the underlying operating system, facilitating the execution of various tasks and programs.

The command line interface (CLI) is a text-based interface that allows users to interact with the shell and execute commands by typing them in a terminal or console window. The CLI offers several advantages, including flexibility, scripting & automation, remote access, and repeatability.

### Command-Line Arguments
Command-line arguments allow users to pass additional information to a script or program when executing it from the command line. Arguments are typically specified after the command itself and can be used to modify the behavior or provide input to the script. For example:

```
./script.sh arg1 arg2
```
In this example, arg1 and arg2 are command-line arguments passed to the script script.sh. The script can access and process these arguments within its code.

Command-line arguments can be used to provide input data, specify options or flags, control the execution flow, or customize the behavior of a script or program.
Please note that the actual usage and syntax of commands and command-line arguments may vary depending on the specific shell or operating system you are using.

## Getting Started

If you just want to check the functionality of this project you can do it online [here](https://www.programiz.com/c-programming/online-compiler/). For running it in your system follow the next steps:

1. Make sure you have GCC (GNU Compiler Collection) installed on your system.

2. Clone this repository or download the source code files.

3. Open a terminal or command prompt (WSL Recommended).

4. Navigate to the directory where the source code files are located.

5. Compile the code using the GCC compiler:

   ```
   gcc -o shell shell.c
   ```

6. Run the program:

   ```
   ./shell
   ```

7. The shell program will start, and you will see a prompt (`>`) where you can enter commands.

> In case you don't have gcc refer [this](https://gist.github.com/alandsilva26/53cd2fecf253554c2f671766d3df5d66).

## Features
Here are some features you can use in this shell:
- cd: Change the current working directory.
- exit: Terminate the shell program.
- help: Display a list of available commands.
- execute calls: Execute external commands by forking and creating child processes.
- wait: Wait for child processes to finish before executing the next command.
- fork and parent-child process: Demonstrate the creation of child processes using fork.
- history: Store and display a history of executed commands.
- bind: Bind a command to a specific key combination for quick execution.
- bg: Execute a command in the background.
- caller: Display the Parent Process ID (PID).

## References

https://learn.microsoft.com/en-us/windows/wsl/install

https://www.ibm.com/docs/en/aix/7.2?topic=administration-operating-system-shells

https://www.geeksforgeeks.org/introduction-linux-shell-shell-scripting/

https://blog.ehoneahobed.com/building-a-simple-shell-in-c-part-1

https://www.geeksforgeeks.org/bind-command-in-linux-with-examples/

https://www.cyberciti.biz/faq/unix-linux-bg-command-examples-usage-syntax/

https://unix.stackexchange.com/questions/19323/what-is-the-caller-command
