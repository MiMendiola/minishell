/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:05:36 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/28 19:03:49 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor(t_token **tokens, t_env **env)
{
    t_token *aux;

    aux = *tokens;
    while (aux->infile || aux->outfile)
    {
        if (ft_strcmp(aux->infile->type, HERE_DOC))
            heredoc(aux->infile->name);
    }
}