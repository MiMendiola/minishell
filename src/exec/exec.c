/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:05:36 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/29 09:49:02 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    infile_till_last(t_iofile *infiles)
{
    int infile;

    while (infiles)
    {
        if (infiles->next == NULL)
        {
            if (infiles->type == HEREDOC)
                infile = open(TMP_FILE, O_RDONLY);
            else if (infiles->type == INFILE)
                infile = open(infiles->name , O_RDONLY);
            if (infile == -1)
            {
                show_error(FILE_ERROR, infiles->name);
                continue;   
            }
            dup2(infile, STDIN_FILENO);
            dup2(infiles->fd[WRITE_FD], STDOUT_FILENO);
            close(infile);
            close(infiles->fd[READ_FD]);
            close(infiles->fd[WRITE_FD]);
        }
        else
        {
            if (infiles->type == HEREDOC)
                infile = open(TMP_FILE, O_RDONLY);
            else if (infiles->type == INFILE)
                infile = open(infiles->name , O_RDONLY);
            if (infile == -1)
            {
                show_error(FILE_ERROR, infiles->name);
                perror("Mal");   
            }
            close(infile);
        }
        infiles = infiles->next;
    }
}

void	executor(t_token **tokens, t_env **env)
{
    t_token *aux_token;
    t_env *aux_env;

    aux_token = *tokens;
    aux_env = *env;
    if (aux_env->name == NULL)
        printf("mal");
    infile_till_last(aux_token->infile);
}