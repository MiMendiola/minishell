/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:42:07 by anadal-g          #+#    #+#             */
/*   Updated: 2024/12/17 17:13:09 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void setup_child_io(int fd_in, int fd_out)
{
    if (dup2(fd_in, STDIN_FILENO) == -1)
    {
        perror_error("Error al redirigir entrada");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd_out, STDOUT_FILENO) == -1)
    {
        perror_error("Error al redirigir salida");
        exit(EXIT_FAILURE);
    }
    if (fd_in != STDIN_FILENO)
        close(fd_in);
    if (fd_out != STDOUT_FILENO && fd_out != STDERR_FILENO)
        close(fd_out);
}

char *handle_command_path(t_token *token, t_env *env, char ***env_array)
{
    char *path;
    int i;
    
    i = 0;
    *env_array = env_to_array(env);
    path = find_path(token->tokens[0], *env_array);
    if (!path)
    {
        perror_error("Error al encontrar el path del comando");
        while ((*env_array)[i])
        {
            free((*env_array)[i]);
            i++;
        }
        free(*env_array);
        exit(EXIT_FAILURE);
    }
    return path;
}

static void mid_child_setup(t_token *token, t_env *env, int *new_fd)
{
    int fd_in;
    int fd_out;

    close(new_fd[0]);
    fd_in = open_infile(token->infile);
    if (fd_in < 0)
    {
        perror_error("Error al abrir archivo de entrada");
        exit(EXIT_FAILURE);
    }
    fd_out = open_outfile(token->outfile);
    if (fd_out < 0)
    {
        perror_error("Error al abrir archivo de salida");
        exit(EXIT_FAILURE);
    }
    child_aux(token, env, fd_in, fd_out);
}


void mid_child(t_token *token, t_env *env, int *fd, int *new_fd)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror_error("Error en fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        mid_child_setup(token, env, new_fd);
        exit(EXIT_SUCCESS);
    }
    close(fd[0]);
    close(new_fd[1]);
}


void first_child(t_token *token, t_env *env, int *fd)
{
    int fd_in;
    int fd_out;

    close(fd[0]);
    fd_in = open_infile(token->infile);
    if (fd_in < 0)
	{
        perror("Error al abrir archivo de entrada");
        exit(EXIT_FAILURE);
	}
    fd_out = open_outfile(token->outfile);
    if (fd_out < 0)
	{
        perror("Error al abrir archivo de salida");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd_in, STDIN_FILENO) == -1)
    {
        perror("Error en redirección de entrada");
        exit(EXIT_FAILURE);
    }
    close(fd_in);
    close(fd_out);
    execute_command(token, env);
}
