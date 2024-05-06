/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:14:46 by anadal-g          #+#    #+#             */
/*   Updated: 2024/05/06 15:14:48 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* ================= PIPE ENDS =================== */
# define READ_FD 0
# define WRITE_FD 1

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