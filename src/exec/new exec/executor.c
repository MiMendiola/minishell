/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:15:14 by anadal-g          #+#    #+#             */
/*   Updated: 2024/12/04 12:58:52 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void executor(t_token *tokens, t_env *env)
{
    int fd[2] = {-1, -1};
    pid_t pid;

	
    while (tokens)
	{
        if (tokens->next && pipe(fd) == -1)
		{
            perror("Error al crear pipe");
            exit(EXIT_FAILURE);
        }
        if ((pid = fork()) == -1)
		{
            perror("Error en fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
		{
			first_child(tokens, env, fd);
            exit(EXIT_SUCCESS);
        }
        close(fd[1]);
        if (tokens->next)
            fd[0] = fd[1];
        waitpid(pid, NULL, 0);
        tokens = tokens->next;
    }
}

