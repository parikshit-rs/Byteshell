# Byteshell

This is a simple shell program implemented in C. It provides basic command functionalities such as `cd`, `exit`, and `help`. It also includes features like executing external commands, forking and waiting for child processes, and maintaining a command history.

## Getting Started

If you just want to check the functionality of this project you can do it online [here](https://www.programiz.com/c-programming/online-compiler/). For running it in your system follow the next steps:

1. Make sure you have GCC (GNU Compiler Collection) installed on your system.

> In case you don't have gcc refer [this](https://gist.github.com/alandsilva26/53cd2fecf253554c2f671766d3df5d66).

2. Clone this repository or download the source code files.

3. Open a terminal or command prompt.

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

## Usage

The shell program supports the following commands:

- `cd [directory]`: Change the current working directory. If no directory is specified, it will change to the home directory.

- `exit`: Exit the shell program.

- `help`: Display information about the available commands.

The shell program also allows you to execute external commands. Simply enter the command as you would in a regular terminal.

Additionally, the shell keeps track of the command history. You can use the up and down arrow keys to navigate through the history and press Enter to execute a previous command.

## Contributing

Contributions to this project are welcome! If you have any suggestions, improvements, or bug fixes, feel free to open an issue or submit a pull request.

## References

https://www.ibm.com/docs/en/aix/7.2?topic=administration-operating-system-shells

https://www.geeksforgeeks.org/introduction-linux-shell-shell-scripting/

https://blog.ehoneahobed.com/building-a-simple-shell-in-c-part-1
