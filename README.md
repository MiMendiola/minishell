<p align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/minishellm.png" alt="minishell Badge"/>
</p>

<h1 align="center">🐚 minishell</h1>

<p align="center">
  <strong>As beautiful as a shell</strong><br>
  Implementacion de una shell minima en C inspirada en bash
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" />
  <img src="https://img.shields.io/badge/Library-readline-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/School-42_Madrid-black?style=for-the-badge&logo=42" />
  <a href="Documentation/en/README.en.md">
    <img src="https://img.shields.io/badge/Read_in-English-purple?style=for-the-badge" alt="Read in English" />
  </a>
</p>

---

## 📋 Tabla de Contenidos

- [Sobre el Proyecto](#-sobre-el-proyecto)
- [Caracteristicas](#-caracteristicas)
- [Requisitos](#-requisitos)
- [Instalacion](#-instalacion)
- [Uso](#-uso)
- [Parsing y Tokenizacion](#-parsing-y-tokenizacion)
- [Built-ins](#-built-ins)
- [Caracteristicas Tecnicas](#-caracteristicas-tecnicas)
- [Estructura del Proyecto](#-estructura-del-proyecto)
- [Recursos](#-recursos)

---

## 🎯 Sobre el Proyecto

**minishell** es un proyecto del cursus de 42 que consiste en construir una shell propia en C. El objetivo es entender como un interprete de comandos lee la entrada del usuario, la divide en tokens, gestiona el historial y prepara la ejecucion de comandos.

Este repositorio contiene la base del proyecto con:

- **Readline** para prompt interactivo e historial.
- **Parsing por pipes** respetando comillas simples y dobles.
- **Lista enlazada de tokens** para representar los comandos introducidos.
- **Built-ins iniciales** como `exit` e `history`.
- **libft propia** como libreria auxiliar.

---

## ✨ Caracteristicas

### Funcionalidades Core

- ✅ Prompt interactivo con `readline`
- ✅ Historial de comandos con `add_history`
- ✅ Comando `history`
- ✅ Comando `exit` con liberacion de la lista de tokens
- ✅ Separacion de comandos por pipes (`|`)
- ✅ Respeto basico de comillas simples y dobles durante el split
- ✅ Estructura de tokens en lista doblemente enlazada

### Parsing

- ✅ Contador de comandos
- ✅ Split por delimitador sin romper contenido entre comillas
- ✅ Trim de espacios exteriores en cada comando
- ✅ Creacion incremental de nodos con identificador
- ✅ Utilidades para recorrer y liberar la lista

### Base para Expansion

- ✅ Definiciones preparadas para built-ins clasicos (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
- ✅ Campos en la estructura para `envp`, redirecciones, `PATH` y `SHLVL`
- ✅ Modulos separados para parsing, built-ins y senales
- ✅ Compilacion con `libft` y `readline`

---

## 🛠️ Requisitos

- **Sistema Operativo**: Linux o macOS
- **Compilador**: `cc`, `gcc` o `clang`
- **Make**
- **Librerias**:
  - `readline`
  - `libft` incluida en el repositorio

### Instalacion de dependencias

**En Ubuntu/Debian:**

```bash
sudo apt-get update
sudo apt-get install build-essential make libreadline-dev
```

**En macOS:**

```bash
# Xcode Command Line Tools
xcode-select --install

# Si readline no esta disponible por defecto:
brew install readline
```

---

## 📦 Instalacion

```bash
# Clonar el repositorio
git clone https://github.com/MiMendiola/minishell.git
cd minishell

# Compilar el proyecto
make

# Ejecutar minishell
./minishell
```

### Comandos Make disponibles

```bash
make        # Compila minishell
make clean  # Elimina archivos objeto
make fclean # Elimina archivos objeto, libft.a y ejecutable
make re     # Recompila desde cero
```

---

## 🚀 Uso

### Iniciar la shell

```bash
./minishell
```

El programa muestra un prompt interactivo:

```text
 💻 $
```

### Ejemplos

```bash
 💻 $ history
 💻 $ echo hola mundo
 💻 $ ls -la | wc -l
 💻 $ exit
```

### Comportamiento actual

La version actual construye y almacena tokens a partir del input. El parsing por pipes ya conserva las partes entre comillas:

```text
echo "hola | mundo" | wc -c
```

Se interpreta como dos comandos principales:

```text
echo "hola | mundo"
wc -c
```

---

## 🔍 Parsing y Tokenizacion

El parser esta centrado en separar la entrada del usuario por un caracter delimitador, normalmente `|`, sin cortar cuando ese caracter aparece dentro de comillas.

### Flujo Principal

```text
Input del usuario
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
Lista doblemente enlazada de t_token
```

### Algoritmo Basico

```text
Para cada caracter del input:
  1. Saltar delimitadores repetidos
  2. Si aparece una comilla, avanzar hasta su cierre
  3. Si aparece el delimitador fuera de comillas, cerrar comando
  4. Crear substring del comando
  5. Limpiar espacios exteriores
  6. Guardar el resultado en la lista de tokens
```

### Ejemplo Visual

```text
Input:
  echo "hola | mundo" | grep hola

Tokens por pipe:
  [1] echo "hola | mundo"
  [2] grep hola
```

---

## 🧩 Built-ins

### Implementados

| Built-in | Descripcion |
| --- | --- |
| `exit` | Sale de minishell, muestra la lista de tokens y libera memoria |
| `history` | Muestra el historial registrado por readline |

### Preparados en definiciones

| Built-in | Objetivo |
| --- | --- |
| `echo` | Imprimir argumentos |
| `cd` | Cambiar directorio |
| `pwd` | Mostrar directorio actual |
| `export` | Exportar variables de entorno |
| `unset` | Eliminar variables de entorno |
| `env` | Mostrar entorno |

---

## 🔬 Caracteristicas Tecnicas

### Estructura Principal

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

### Funciones Clave

```c
char    **command_spliter(char const *s, char c);
int     command_counter(char *str, char c);
void    create_tokens(char *input, t_token **tokens);
void    add_node_tokens(t_token **stack, char **splited_tokens);
void    free_list(t_token **stack);
```

### Gestion de Memoria

- Los comandos se almacenan en nodos dinamicos.
- Cada substring se recorta con `ft_strtrim`.
- `free_list` centraliza la liberacion de la lista enlazada.
- `libft` aporta utilidades de memoria, strings, listas, `printf` y `get_next_line`.

---

## 📁 Estructura del Proyecto

```text
minishell/
├── Makefile
├── README.md
├── includes/
│   ├── defines.h          # Constantes, built-ins y mensajes
│   ├── minishell.h        # Includes y prototipos principales
│   └── structs.h          # Estructuras t_token y t_env
├── src/
│   ├── minishell.c        # Loop principal y prompt
│   ├── shlvl.c            # Gestion de SHLVL
│   ├── built-ins/
│   │   ├── core_builtins.c
│   │   ├── echo.c
│   │   └── history.c
│   ├── parsing/
│   │   ├── parsing.c
│   │   ├── tokenizer.c
│   │   └── utils_stack.c
│   └── signals/
│       └── signals.c
└── libft/
    ├── lib/
    ├── bonus/
    ├── ft_printf/
    └── gnl/
```

---

## 📚 Recursos

### Shell y Bash

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)

### Sistemas Unix

- [fork(2)](https://man7.org/linux/man-pages/man2/fork.2.html)
- [execve(2)](https://man7.org/linux/man-pages/man2/execve.2.html)
- [pipe(2)](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [dup2(2)](https://man7.org/linux/man-pages/man2/dup.2.html)

---

## 🎓 Aprendizajes Clave

Este proyecto permite trabajar conceptos fundamentales de Unix y C:

- **Parsing**: Separar comandos respetando reglas de comillas y delimitadores.
- **Estructuras dinamicas**: Modelar comandos con listas enlazadas.
- **Readline**: Crear una experiencia interactiva con historial.
- **Gestion de memoria**: Evitar fugas al crear y destruir tokens.
- **Arquitectura modular**: Separar built-ins, parsing, senales y utilidades.

---

## 👥 Autores

- **Miguel** - [@MiMendiola](https://github.com/MiMendiola)
- **anadal-g** - 42 Madrid

---

## 📄 Licencia

Este proyecto es parte del cursus de 42 Madrid y esta sujeto a sus normas academicas.

---

<p align="center">
  <sub>Desarrollado con C en 42 Madrid</sub>
</p>
