/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:18:11 by mmendiol          #+#    #+#             */
/*   Updated: 2024/05/10 17:23:56 by mmendiol         ###   ########.fr       */
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

/* ================= PIPE ENDS =================== */
# define HSTRY_TXT "history"
# define EXIT_TXT "exit"

/* ================== MESSAGES =================== */
# define FILES " 👺 minishell: no such file or directory: "
# define COMMAND " 👺 minishell: command not found: "
# define ARGUMENTS "Error: bad number of arguments\n"
# define CHILD "child error"
# define PIPE "pipe error"
# define PATH "PATH="
# define HERE_DOC "here_doc"
# define TMP_FILE "/tmp/pipex_tmp"

#endif