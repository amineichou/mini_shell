# Minishell Project

Welcome to MINISHELL project! This project involves creating a basic shell (similar to Bash) to deepen your understanding of processes and file descriptors in a Unix-like operating system.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The minishell project is a 42Network Project designed to help you gain hands-on experience with:
- **Processes:** How to create and manage processes using system calls like `fork()`, `exec()`, and `wait()`.
- **File Descriptors:** Understanding standard input, output, and error streams, and how to redirect them.
By implementing your own shell, you will explore these concepts in depth and develop a stronger grasp of how Unix-like operating systems function under the hood.

## Features

- Execute built-in commands like `cd`, `exit`, and `echo`.
- Launch external programs.
- Handle pipe `|`.
- Implement input/output redirection (`>`, `>>`, `<`) and also Heredoc `<<`.
- Support for basic environment variables.
- Signals (`Ctrl ^ C`, `Ctrl ^ \`).

## Installation

To install and run the minishell, follow these steps:

1. Clone the repository:
   ```
   git clone https://github.com/amineichou/minishell.git
   ```
2. Navigate to the project directory:
    ```
    cd minishell
    ```
3. Compile:
    ```
    make
    ```

## Usage

- Run `./minishell`
- Example 
```
minishell> ls -la
minishell> cd /path/to/directory
minishell> echo "Hello, World!" > output.txt
```

Happy coding!