/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:18:11 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/25 17:22:09 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* ================= PIPE ENDS =================== */
# define READ_FD 0
# define WRITE_FD 1

/* ================== BOOLEANS =================== */
# define FALSE 0
# define TRUE 1

/* =================== UTILS ===================== */
# define DQUOTES 34
# define SQUOTES 39
# define PIPE 124

# define PATH "PATH="
# define PATH_MAX "4096"
# define HERE_DOC "here_doc"
# define TMP_FILE "/tmp/pipex_tmp"

/* ================= BUILT-INS =================== */
# define ECHO_TXT "echo"
# define CD_TXT "cd"
# define PWD_TXT "pwd"
# define EXPORT_TXT "export"
# define UNSET_TXT "unset"
# define ENV_TXT "env"
# define EXIT_TXT "exit"
# define HSTRY_TXT "history"

/* ================== MESSAGES =================== */
# define NOT_FILE " 👺 minishell: no such file or directory: "
# define COMMAND_NOT_FOUND " 👺 minishell: command not found: "
# define COMMAND_NOT_FOUND_REVERSE ": command not found 👺"
# define QUOTES_NOT_VALID " 👺 minishell: invalid quotes "

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define CLEAR "\x1b[0m"

#endif