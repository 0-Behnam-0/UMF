# Uncomplicated Microterminal Framework (UMF)

The Uncomplicated Microterminal Framework (UMF) is a small simulation of a shell written in the C programming language. It provides a command-line interface for executing commands and performing basic operations.

## Features

- Command Execution: UMF allows users to execute various commands supported by the underlying operating system.
- Change Directory: Users can change their current working directory using the "cd" command.
- Output Redirection: UMF supports redirecting command output to a file using the ">" symbol.
- Background Processes: Users can run commands in the background by appending "&" at the end of the command.
- Program Information: The "globalusage" command displays information about UMF.

## Getting Started

To compile and run the UMF program, follow these steps:

1. Make sure you have a C compiler installed on your system (e.g., GCC).
2. Clone this repository or download the source code files.
3. Open a terminal or command prompt and navigate to the directory where the UMF source code is located.
4. Compile the code using the following command:
`gcc umf.c -o umf`
5. Run the program with the following command:
`./umf`

## Usage

Once you have started the UMF program, you can interact with it using the command-line interface. Here are some important commands and features:

### Prompt

The UMF prompt displays the username, hostname, and current working directory in the following format:
> (username@hostname)-[~current_directory] $

### Basic Commands

- `exit`: Exits the UMF program.
- `cd [path]`: Changes the current directory to the specified path.
- `globalusage`: Displays information about UMF.

### Output Redirection

UMF supports redirecting command output to a file using the ">" symbol. For example, to redirect the output of a command to a file, use the following syntax:
`command > filename`

The output of the command will be appended to the specified file.

### Background Processes

To run a command in the background, append "&" at the end of the command. For example:
`command &`

The command will be executed in the background, and control will be returned to the prompt immediately.

## Limitations

- UMF has a maximum limit of 20 arguments for a command.
- The program assumes that the user's environment has a `USER` environment variable set.
- UMF does not support input redirection or pipelining.

## Conclusion

The Uncomplicated Microterminal Framework (UMF) is a simple shell simulation in C that provides basic command execution, directory navigation, output redirection, and background process support. It can serve as a starting point for building more advanced shell programs or as a learning tool for understanding shell concepts and system calls.

## Contribution

Contributions to the Uncomplicated Microterminal Framework (UMF) are welcome! If you have any ideas, suggestions, or bug reports, please open an issue or submit a pull request.
