/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:28:31 by anadal-g          #+#    #+#             */
/*   Updated: 2025/03/27 11:54:27 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_and_cleanup(char *path, char **tokens, char **env_array)
{
	if (execve(path, tokens, env_array) == -1)
	{
		perror_error("Error al ejecutar el comando");
		free_matrix(env_array);
		free(path);
		exit(EXIT_FAILURE);
	}
	free_matrix(env_array);
	free(path);
}

static void	setup_last_child(t_token *token, t_env *env, int fd_in, int fd_out)
{
	char	*path;
	char	**env_array;

	path = handle_command_path(token, env, &env_array);
	setup_child_io(fd_in, fd_out);
	execute_and_cleanup(path, token->tokens, env_array);
}

void	last_child(t_token *token, t_env **env, int *fd)
{
	pid_t pid;
	int fd_in;
	int fd_out;

	pid = fork();
	if (pid == -1)
	{
		perror("Error en fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		fd_in = open_infile(token->infile);
		if (fd_in < 0)
			exit(1);
		fd_out = open_outfile(token->outfile);
		if (fd_out < 0)
			exit(1);
		setup_last_child(token, *env, fd_in, fd_out); // Cambio clave aquí: *env
	}
	close(fd[0]);
}
