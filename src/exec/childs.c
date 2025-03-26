/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:13:47 by anadal-g          #+#    #+#             */
/*   Updated: 2025/03/26 12:13:51 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void child_aux(t_token *token, t_env *env, int fd_in, int fd_out)
{
    char *path;
    char **env_array;

    path = handle_command_path(token, env, &env_array);
    setup_child_io(fd_in, fd_out);
    
    if (is_builtin(token->command))
    {
        select_builtin(&token, &env, token->command);
        exit(env->last_out);
    }
    
    execve(path, token->tokens, env_array);
    perror("execve");
    free(path);
    free_matrix(env_array);
    exit(126);
}

void first_child(t_token *token, t_env **env, int *fd)
{
    pid_t pid;
    int fd_in;
    int fd_out;

    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        fd_in = open_infile(token->infile);
        if (fd_in < 0)
            exit(1);
        
        fd_out = open_outfile(token->outfile);
        if (fd_out < 0)
            fd_out = fd[1];
        else
            close(fd[1]);
        
        child_aux(token, *env, fd_in, fd_out);
    }
    else if (pid < 0)
        exit_fork_pipe(FORK);
}

void mid_child(t_token *token, t_env **env, int *fd, int *new)
{
    pid_t pid;
    int fd_in;
    int fd_out;

    pid = fork();
    if (pid == 0)
    {
        close(new[0]);
        fd_in = open_infile(token->infile);
        if (fd_in < 0)
            fd_in = fd[0];
        else
            close(fd[0]);
        
        fd_out = open_outfile(token->outfile);
        if (fd_out < 0)
            fd_out = new[1];
        else
            close(new[1]);
        
        child_aux(token, *env, fd_in, fd_out);
    }
    else if (pid < 0)
        exit_fork_pipe(FORK);
}

void last_child(t_token *token, t_env **env, int *fd)
{
    pid_t pid;
    int fd_in;
    int fd_out;

    pid = fork();
    if (pid == 0)
    {
        fd_in = open_infile(token->infile);
        if (fd_in < 0)
            fd_in = fd[0];
        else
            close(fd[0]);
        
        fd_out = open_outfile(token->outfile);
        if (fd_out < 0)
            exit(1);
        
        child_aux(token, *env, fd_in, fd_out);
    }
    else if (pid < 0)
        exit_fork_pipe(FORK);
}

void wait_childs(pid_t final_pid, int *last_out)
{
    pid_t current_pid;
    int status;

    while (1)
    {
        current_pid = waitpid(-1, &status, 0);
        if (current_pid <= 0)
            break;
        if (current_pid == final_pid)
            *last_out = WEXITSTATUS(status);
    }
}