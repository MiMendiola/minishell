/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:23:14 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/09 12:22:22 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_env_list(t_env *env_list)
{
    t_env *current;
    t_env *next;

    current = env_list;
    if (!env_list)
    {
        printf("Error con el env\n");
        return ;
    }
    
    while (current)
    {
        next = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = next;
    }
}

void free_tokens(t_token **tokens)
{
    t_token *current;
    t_token *next;

    if (!tokens || !*tokens)
        return;
    
    current = *tokens;
    while (current)
    {
        next = current->next;
        free(current->command);
        free(current->tokens);
        free(current->content);
        free(current);
        current = next;
    }
    *tokens = NULL;
}
