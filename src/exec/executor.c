/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:24:16 by anadal-g          #+#    #+#             */
/*   Updated: 2025/03/27 11:54:15 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_tokens(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	one_command(t_token *token, t_env **env)
{
	if (is_builtin(token->command))
		exe_built_ins(token, env);
	else
		exe_one_cmd(token, env);
}

static void	two_or_more_cmds(t_token *tokens, t_env **env)
{
	int		new[2];
	int		fd[2];
	t_token	*current;
	pid_t	final_pid;
	int		last_out;

	current = tokens;
	final_pid = 0;
	last_out = 0;
	if (pipe(fd) < 0)
		exit_fork_pipe(PIPE);
	first_child(current, env, fd);
	close(fd[1]);
	current = current->next;
	while (current->next)
	{
		if (pipe(new) < 0)
			exit_fork_pipe(PIPE);
		mid_child(current, env, fd, new);
		close(fd[0]);
		close(new[1]);
		fd[0] = new[0];
		current = current->next;
	}
	final_pid = fork();
	if (final_pid == 0)
		last_child(current, env, fd);
	else if (final_pid < 0)
		exit_fork_pipe(FORK);
	close(fd[0]);
	wait_childs(final_pid, &last_out);
	(*env)->last_out = last_out;
}

void	executor(t_token *tokens, t_env **env)
{
	int cmd_count = count_tokens(tokens);

	if (cmd_count == 1)
		one_command(tokens, env);
	else
		two_or_more_cmds(tokens, env);
}
