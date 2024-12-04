/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:00:35 by mmendiol          #+#    #+#             */
/*   Updated: 2024/12/03 11:08:08 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	other_childs(int *fd, int *fd2)
{
	dup2(fd[READ_FD], STDIN_FILENO);
	dup2(fd2[WRITE_FD], STDOUT_FILENO);
	close(fd[WRITE_FD]);
	close(fd2[READ_FD]);
	close(fd2[WRITE_FD]);
}

void	connect_next_cmd(int *fd, int *fd2)
{
	close(fd[READ_FD]);
	close(fd2[WRITE_FD]);
	fd[READ_FD] = fd2[READ_FD];
}
void first_child(t_token *tokens, t_env *env, int *fd)
{
    int infile;
    char *cmd_path;
    char **env_array;

    infile = -1;
    if (tokens->infile)
    {
        infile_till_last(tokens->infile);
        if (infile == -1) {
            show_error(FILE_ERROR, TMP_FILE);
            exit(EXIT_FAILURE);
        }
    }
    if (fd && fd[1] >= 0)
    {
        if (dup2(fd[1], STDOUT_FILENO) == -1)
        {
            perror("Error en dup2 para fd[1]");
            exit(EXIT_FAILURE);
        }
        close(fd[1]);
    }

    if (fd && fd[0] >= 0)
        close(fd[0]);
    env_array = env_to_array(env);
    cmd_path = check_path(tokens->tokens, env);
    if (cmd_path)
        execve(cmd_path, tokens->tokens, env_array);
    else
    {
        perror("Comando no encontrado");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (env_array[i])
    {
        free(env_array[i]);
        i++;
    }
    free(env_array);
}


void next_cmds(char **arg, t_env *env_path, int *pid, int *fd)
{
    int fd2[2] = {-1, -1};  // Inicializar con -1
    int ac;
    int i = 2;

    ac = 0;
    while (arg[ac])
        ac++;
    if (ft_strcmp(arg[1], HERE_DOC))
        i++;
    while (++i < (ac - 2))
    {
        if (pipe(fd2) == -1)
        {
            perror("Error al crear pipe");
            exit(EXIT_FAILURE);
        }

        *pid = fork();
        if (*pid == -1)
        {
            perror("Error en fork");
            exit(EXIT_FAILURE);
        }
        if (*pid == 0)
        {
            if (fd && fd[0] >= 0 && fd2[1] >= 0)
            {
                other_childs(fd, fd2);
                check_access(arg[i], env_path);
            }
            else
            {
                perror("Descriptores de archivo inválidos");
                exit(EXIT_FAILURE);
            }
        }
        if (fd2[0] >= 0)
            fd[0] = fd2[0];
    }
    parent_bonus(arg, env_path, pid, fd);
}

void parent_bonus(char **arguments, t_env *env_path, int *pid, int *fd)
{
    int outfile;
    int ac;

    ac = 0;
    while (arguments[ac])
        ac++;
    close(fd[WRITE_FD]);
    *pid = fork();
    if (*pid == -1)
        show_error(CHILD, NULL);
    if (*pid == 0)
    {
        if (ft_strcmp(arguments[1], HERE_DOC))
            outfile = open(arguments[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            outfile = open(arguments[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd[READ_FD], STDIN_FILENO);
        dup2(outfile, STDOUT_FILENO);
        close(fd[READ_FD]);
        check_access(arguments[ac - 2], env_path);
    }
    else
        close(fd[READ_FD]);
}
