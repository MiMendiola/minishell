/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:15:14 by anadal-g          #+#    #+#             */
/*   Updated: 2025/01/28 10:52:01 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void one_child(t_token *token, t_env *env)
{
    int fd_in;
    int fd_out;
    char *path;
    char **env_array;

    fd_in = open_infile(token->infile);
    if (fd_in < 0)
        perror_error("Error al abrir archivo de entrada");
    fd_out = open_outfile(token->outfile);
    if (fd_out < 0)
        perror_error("Error al abrir archivo de salida");
    if (dup2(fd_in, STDIN_FILENO) == -1)
        perror_error("Error en dup2 para entrada");
    if (dup2(fd_out, STDOUT_FILENO) == -1)
        perror_error("Error en dup2 para salida");
    env_array = env_to_array(env);
    path = find_path(token->command, env_array);
    if (!path)
    {
        printf("Comando no encontrado: %s\n", token->command);
        exit(127);
    }
    execve(path, token->tokens, env_array);
    perror_error("Error al ejecutar el comando");
    free(path);
    exit(EXIT_FAILURE);
}

void one_cmd(t_token *token, t_env *env)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
        perror_error("Error en fork");
    if (pid == 0)
    {
        one_child(token, env);
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
static void handle_intermediate_commands(t_token *tokens, t_env *env, int *fd, int *new)
{
    while (tokens->next && tokens->next->next)
    {
        tokens = tokens->next;
        if (pipe(new) < 0) {
            perror("Error al crear pipe");
            exit(EXIT_FAILURE);
        }
        mid_child(tokens, env, fd, new);
        close(fd[0]);
        close(new[1]);
        fd[0] = new[0];
    }
}

static void execute_multiple_commands(t_token *tokens, t_env *env, int *final_status)
{
    int fd[2];
    int new[2];
    pid_t pid;

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
    handle_intermediate_commands(tokens, env, fd, new);
    last_child(tokens->next, env, fd);
    close(fd[0]);
    wait_childs(pid, final_status);
}

static void handle_single_command(t_token *tokens, t_env *env)
{
    if (is_builtin(tokens->command))
        select_builtin(&tokens, &env, tokens->command);
    else
        one_cmd(tokens, env);
}

void executor(t_token *tokens, t_env *env)
{
    int final_status;

    final_status = 0;
    if (!tokens->next)
    {
        handle_single_command(tokens, env);
        return;
    }
    execute_multiple_commands(tokens, env, &final_status);
    unlink(TMP_FILE);
}


// void executor(t_token *tokens, t_env *env)
// {
//     int fd[2];
//     int new[2];
//     pid_t pid;
//     int final_status;
//     int counter;

//     final_status = 0;
//     counter = 0;
//     if (!tokens->next)
//     {
//         if (is_builtin(tokens->command))
//             select_builtin(&tokens, &env, tokens->command);
//         else
//             one_cmd(tokens, env);
//         return;
//     }
//     if (pipe(fd) == -1)
//     {
//         perror("Error al crear pipe");
//         exit(EXIT_FAILURE);
//     }
//     pid = fork();
//     if (pid == -1)
//     {
//         perror("Error en fork");
//         exit(EXIT_FAILURE);
//     }
//     if (pid == 0)
//     {
//         first_child(tokens, env, fd);
//         exit(EXIT_SUCCESS);
//     }
//     close(fd[1]);
//     while (tokens->next && tokens->next->next)
//     {
//         tokens = tokens->next;
//         if (pipe(new) < 0)
//         {
//             perror("Error al crear pipe");
//             exit(EXIT_FAILURE);
//         }
//         mid_child(tokens, env, fd, new);
//         close(fd[0]);
//         close(new[1]);
//         fd[0] = new[0];
//     }
//     tokens = tokens->next;
//     last_child(tokens, env, fd);
//     close(fd[0]);
//     wait_childs(pid, &final_status);
//     unlink(TMP_FILE);
// }

