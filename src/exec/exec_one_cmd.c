/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:13:21 by anadal-g          #+#    #+#             */
/*   Updated: 2025/03/27 11:54:07 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_process(t_token *token, t_env **env)
{
	int		fd_in;
	int		fd_out;
	char	*path;
	char	**env_array;

	fd_in = open_infile(token->infile);
	if (fd_in < 0)
		exit(1);
	fd_out = open_outfile(token->outfile);
	if (fd_out < 0)
		exit(1);
	setup_child_io(fd_in, fd_out);
	path = handle_command_path(token, *env, &env_array);
	if (!path)
	{
		printf("minishell: %s: command not found\n", token->tokens[0]);
		free_matrix(env_array);
		exit(127);
	}
	execve(path, token->tokens, env_array);
	perror("execve");
	free(path);
	free_matrix(env_array);
	exit(126);
}

void	exe_one_cmd(t_token *token, t_env **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit_fork_pipe(FORK);
	if (pid == 0)
		child_process(token, env);
	waitpid(pid, &status, 0);
	(*env)->last_out = WEXITSTATUS(status);
}

void	exe_built_ins(t_token *token, t_env **env)
{
	int fd_in;
	int fd_out;
	int saved_stdin;
	int saved_stdout;

	fd_in = open_infile(token->infile);
	if (fd_in < 0)
	{
		(*env)->last_out = 1;
		return ;
	}
	fd_out = open_outfile(token->outfile);
	if (fd_out < 0)
	{
		(*env)->last_out = 1;
		return ;
	}
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);

	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	select_builtin(&token, env, token->command);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
