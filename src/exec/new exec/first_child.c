/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:42:07 by anadal-g          #+#    #+#             */
/*   Updated: 2024/12/03 11:43:06 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
    if (dup2(fd_in, STDIN_FILENO) == -1) {
        perror("Error en redirección de entrada");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd_out, STDOUT_FILENO) == -1) {
        perror("Error en redirección de salida");
        exit(EXIT_FAILURE);
    }
    close(fd_in);
    close(fd_out);
    execute_command(token, env);
}
