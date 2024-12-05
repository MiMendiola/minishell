/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:15:14 by anadal-g          #+#    #+#             */
/*   Updated: 2024/12/05 12:05:16 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void one_cmd(t_token *token, t_env *env)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        execute_command(token, &env);
        exit(EXIT_SUCCESS);
    }
    waitpid(pid, &status, 0);
}

void wait_childs(pid_t final_pid, int *last_exit_status)
{
    pid_t current_pid;
    int status;
    
    while (1)
    {
        current_pid = waitpid(-1, &status, 0);
        if (current_pid <= 0)
            break;
        if (current_pid == final_pid)
        {
            if (last_exit_status)
                *last_exit_status = WEXITSTATUS(status);
        }
    }
}

void executor(t_token *tokens, t_env *env)
{
    int fd[2];
    int new[2];
    pid_t pid;
    int final_status;
    int counter;

    final_status = 0;
    counter = 0;
    if (!tokens->next)
    {
        if (is_builtin(tokens->command))
            select_builtin(&tokens, &env, tokens->command);
        else
            one_cmd(tokens, env);
        return;
    }
    if (pipe(fd) == -1)
    {
        perror("Error al crear pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1)
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
    while (tokens->next && tokens->next->next)
    {
        tokens = tokens->next;
        if (pipe(new) < 0)
        {
            perror("Error al crear pipe");
            exit(EXIT_FAILURE);
        }
        mid_child(tokens, env, fd, new);
        close(fd[0]);
        close(new[1]);
        fd[0] = new[0];
    }
    tokens = tokens->next;
    last_child(tokens, env, fd);
    close(fd[0]);
    wait_childs(pid, &final_status);
    unlink(TMP_FILE);
}

