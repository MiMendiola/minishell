/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:25:30 by anadal-g          #+#    #+#             */
/*   Updated: 2024/12/17 17:10:41 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int env_size(t_env *env)
{
    int size = 0;

    while (env)
    {
        size++;
        env = env->next;
    }
    return size;
}


char **env_to_array(t_env *env)
{
    int size;
    char **env_array;
    int i;
    char *aux;
    
    size = env_size(env);
    i = 0;
    env_array = malloc((size + 1) * sizeof(char *));
    while (env)
    {
        aux = ft_strjoin(env->name, "=");
        env_array[i++] = ft_strjoin(aux, env->value);
        free(aux);
        env = env->next;
    }
    env_array[i] = NULL;
    return env_array;
}

static void execute_child(int infile, int outfile, char *cmd_path, char **tokens, t_env *env)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        dup2(infile, STDIN_FILENO);
        dup2(outfile, STDOUT_FILENO);
        close(infile);
        close(outfile);
        if (execve(cmd_path, tokens, env_to_array(env)) == -1)
        {
            perror("Error al ejecutar el comando");
            exit(EXIT_FAILURE);
        }
    }
    close(infile);
    close(outfile);
    waitpid(pid, NULL, 0);
}

void execute_command(t_token *token, t_env *env)
{
    int infile, outfile;
    char *cmd_path;

    infile = open_infile(token->infile);
    if (infile == -1)
        return;
    outfile = open_outfile(token->outfile);
    if (outfile == -1)
    {
        close(infile);
        return;
    }
    cmd_path = find_path(token->tokens[0], env_to_array(env));
    if (!cmd_path)
    {
        perror("Comando no encontrado");
        close(infile);
        close(outfile);
        return;
    }
    execute_child(infile, outfile, cmd_path, token->tokens, env);
    free(cmd_path);
}

// void execute_command(t_token *token, t_env *env)
// {
//     pid_t pid;
//     int infile, outfile;
//     char *cmd_path;

//     infile = open_infile(token->infile);
//     if (infile == -1)
// 		return;
//     outfile = open_outfile(token->outfile);
//     if (outfile == -1)
// 	{
//         close(infile);
//         return;
//     }
//     cmd_path = find_path(token->command, env_to_array(env));
//     if (!cmd_path)
// 	{
//         perror("Comando no encontrado");
//         return;
//     }
//     if ((pid = fork()) == 0)
// 	{
//         dup2(infile, STDIN_FILENO);
//         dup2(outfile, STDOUT_FILENO);
//         close(infile);
//         close(outfile);
//         if (execve(cmd_path, token->tokens, env_to_array(env)) == -1)
// 		{
//             perror("Error al ejecutar el comando");
//             exit(EXIT_FAILURE);
//         }
//     }
//     close(infile);
//     close(outfile);
//     free(cmd_path);
//     waitpid(pid, NULL, 0);
// }
