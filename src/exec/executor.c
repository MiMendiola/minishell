/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:24:16 by anadal-g          #+#    #+#             */
/*   Updated: 2025/03/28 11:06:16 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// static void child_process(t_token *token, t_env **env);

static void execute_command(t_token *token, t_env **env)
{
    if (is_builtin(token->command))
        exe_built_ins(token, env);
    else
        child_process(token, env);
}

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

static void two_or_more_cmds(t_token *tokens, t_env **env)
{
    int     fd[2];
    int     new_fd[2];
    pid_t   pid;
    t_token *current = tokens;

    if (pipe(fd) < 0)
        exit_fork_pipe(PIPE);
    pid = fork();
    if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execute_command(current, env);
        exit(EXIT_SUCCESS);
    }
    close(fd[1]);
    current = current->next;
    while (current->next)
	{
        if (pipe(new_fd) < 0)
            exit_fork_pipe(PIPE);
        pid = fork();
        if (pid == 0) {
            close(new_fd[0]);
            dup2(fd[0], STDIN_FILENO);
            dup2(new_fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(new_fd[1]);
            execute_command(current, env);
            exit(EXIT_SUCCESS);
        }
        close(fd[0]);
        close(new_fd[1]);
        fd[0] = new_fd[0];
        current = current->next;
    }
    pid = fork();
    if (pid == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execute_command(current, env);
        exit(EXIT_SUCCESS);
    }
    close(fd[0]);
    while (waitpid(-1, NULL, 0) > 0);
}

void	executor(t_token *tokens, t_env **env)
{
	int cmd_count = count_tokens(tokens);

	if (cmd_count == 1)
		one_command(tokens, env);
	else
		two_or_more_cmds(tokens, env);
}
