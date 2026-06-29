<p align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/minishellm.png" alt="minishell Badge"/>
</p>

<h1 align="center">🐚 minishell</h1>

<p align="center">
  <strong>As beautiful as a shell</strong><br>
  Minimal shell implementation in C inspired by bash
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" />
  <img src="https://img.shields.io/badge/Library-readline-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/School-42_Madrid-black?style=for-the-badge&logo=42" />
  <a href="../../README.md">
    <img src="https://img.shields.io/badge/Leer_en-Español-purple?style=for-the-badge" alt="Leer en Español" />
  </a>
</p>

---

## 📋 Table of Contents

- [About the Project](#-about-the-project)
- [Features](#-features)
- [Requirements](#-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
- [Parsing and Tokenization](#-parsing-and-tokenization)
- [Built-ins](#-built-ins)
- [Technical Features](#-technical-features)
- [Project Structure](#-project-structure)
- [Resources](#-resources)

---

## 🎯 About the Project

**minishell** is a 42 cursus project focused on building a small shell in C. The goal is to understand how a command interpreter reads user input, splits it into tokens, handles command history, and prepares command execution.

This repository contains the project base with:

- **Readline** for an interactive prompt and history.
- **Pipe parsing** while respecting single and double quotes.
- **Linked-list tokens** to represent entered commands.
- **Initial built-ins** such as `exit` and `history`.
- **Custom libft** as the support library.

---

## ✨ Features

### Core Features

- ✅ Interactive prompt with `readline`
- ✅ Command history with `add_history`
- ✅ `history` command
- ✅ `exit` command with token-list cleanup
- ✅ Command splitting by pipes (`|`)
- ✅ Basic quote-aware splitting
- ✅ Doubly linked token list

### Parsing

- ✅ Command counting
- ✅ Delimiter split without breaking quoted content
- ✅ Outer-space trim for each command
- ✅ Incremental node creation with ids
- ✅ Utilities to traverse and free the list

### Expansion Base

- ✅ Definitions prepared for classic built-ins (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
- ✅ Structure fields for `envp`, redirections, `PATH`, and `SHLVL`
- ✅ Separate modules for parsing, built-ins, and signals
- ✅ Build with `libft` and `readline`

---

## 🛠️ Requirements

- **Operating System**: Linux or macOS
- **Compiler**: `cc`, `gcc`, or `clang`
- **Make**
- **Libraries**:
  - `readline`
  - `libft` included in the repository

### Dependency Installation

**On Ubuntu/Debian:**

```bash
sudo apt-get update
sudo apt-get install build-essential make libreadline-dev
```

**On macOS:**

```bash
xcode-select --install
brew install readline
```

---

## 📦 Installation

```bash
git clone https://github.com/MiMendiola/minishell.git
cd minishell
make
./minishell
```

### Available Make Commands

```bash
make        # Compiles minishell
make clean  # Removes object files
make fclean # Removes object files, libft.a and executable
make re     # Rebuilds from scratch
```

---

## 🚀 Usage

```bash
./minishell
```

The program displays an interactive prompt:

```text
 💻 $
```

### Examples

```bash
 💻 $ history
 💻 $ echo hello world
 💻 $ ls -la | wc -l
 💻 $ exit
```

---

## 🔍 Parsing and Tokenization

The parser splits user input by a delimiter, usually `|`, without splitting when that delimiter appears inside quotes.

```text
User input
  |
  v
readline()
  |
  v
select_builtin()
  |
  v
command_spliter(input, '|')
  |
  v
add_node_tokens()
  |
  v
Doubly linked t_token list
```

### Example

```text
Input:
  echo "hello | world" | grep hello

Pipe tokens:
  [1] echo "hello | world"
  [2] grep hello
```

---

## 🧩 Built-ins

### Implemented

| Built-in | Description |
| --- | --- |
| `exit` | Exits minishell, displays the token list, and frees memory |
| `history` | Displays readline history |

### Prepared in Definitions

| Built-in | Goal |
| --- | --- |
| `echo` | Print arguments |
| `cd` | Change directory |
| `pwd` | Print working directory |
| `export` | Export environment variables |
| `unset` | Remove environment variables |
| `env` | Print environment |

---

## 🔬 Technical Features

```c
typedef struct s_token
{
    int             id;
    char            *command;
    char            **tokens;
    struct s_token  *prev;
    struct s_token  *next;
    char            **envp;
    char            *outfile;
    char            *infile;
    char            **path;
    char            *shlvl;
}   t_token;
```

Key functions:

```c
char    **command_spliter(char const *s, char c);
int     command_counter(char *str, char c);
void    create_tokens(char *input, t_token **tokens);
void    add_node_tokens(t_token **stack, char **splited_tokens);
void    free_list(t_token **stack);
```

---

## 📁 Project Structure

```text
minishell/
├── Makefile
├── README.md
├── includes/
│   ├── defines.h
│   ├── minishell.h
│   └── structs.h
├── src/
│   ├── minishell.c
│   ├── shlvl.c
│   ├── built-ins/
│   ├── parsing/
│   └── signals/
└── libft/
```

---

## 📚 Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [fork(2)](https://man7.org/linux/man-pages/man2/fork.2.html)
- [execve(2)](https://man7.org/linux/man-pages/man2/execve.2.html)
- [pipe(2)](https://man7.org/linux/man-pages/man2/pipe.2.html)

---

## 🎓 Key Learnings

- **Parsing** quote-aware command input.
- **Dynamic structures** with linked lists.
- **Readline** integration for interactive input.
- **Memory management** for token creation and cleanup.
- **Modular architecture** for built-ins, parsing, signals, and utilities.

---

## 👥 Authors

- **Miguel** - [@MiMendiola](https://github.com/MiMendiola)
- **anadal-g** - 42 Madrid

---

## 📄 License

This project is part of the 42 Madrid cursus and follows its academic rules.

---

<p align="center">
  <sub>Developed with C at 42 Madrid</sub>
</p>
