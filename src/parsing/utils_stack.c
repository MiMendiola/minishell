/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:02:31 by mmendiol          #+#    #+#             */
/*   Updated: 2025/03/27 11:28:02 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Solo funciones que son exclusivas de este archivo */
static char **handle_redirections(char *command);

t_token *last_node(t_token *lst)
{
    while (lst && lst->next != NULL)
        lst = lst->next;
    return (lst);
}

void add_node_back(t_token **stack, t_token *new)
{
    t_token *aux;

    if (!stack || !new)
        return;
        
    aux = last_node(*stack);
    if (aux)
    {
        new->prev = aux;
        new->next = NULL;
        aux->next = new;
    }
    else
        *stack = new;
}

static char **handle_redirections(char *command)
{
    char **tokens;

    tokens = redir_divisor(command);
    if (!tokens)
        return (NULL);
    remove_redirection_tokens(tokens);
    return (tokens);
}

t_token *create_node(int id, char *command)
{
    t_token *tokens;

    if (!command)
        return (NULL);
        
    tokens = ft_calloc(1, sizeof(t_token));
    if (!tokens)
        return (NULL);
        
    tokens->id = id;
    tokens->command = ft_strdup(command);
    if (!tokens->command)
    {
        free(tokens);
        return (NULL);
    }
    
    if (ft_strchr(command, '<') || ft_strchr(command, '>'))
    {
        tokens->tokens = handle_redirections(command);
        if (!tokens->tokens)
        {
            free(tokens->command);
            free(tokens);
            return (NULL);
        }
        parse_redirections(tokens);
    }
    else
    {
        tokens->tokens = ft_split(command, ' ');
        if (!tokens->tokens)
        {
            free(tokens->command);
            free(tokens);
            return (NULL);
        }
    }
    
    tokens->prev = NULL;
    tokens->next = NULL;
    return (tokens);
}