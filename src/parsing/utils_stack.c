/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:02:31 by mmendiol          #+#    #+#             */
/*   Updated: 2025/03/26 13:17:15 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char **handle_redirections(char *command);
static char **redir_divisor(char const *s);
static void remove_redirection_tokens(char **tokens);
static void parse_redirections(t_token *token);

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

/* Implementación de redir_divisor */
static char **redir_divisor(char const *s)
{
    int commands = 0;
    char **list_commands = NULL;

    if (!s)
        return (NULL);
    
    commands = redir_counter((char *)s);
    list_commands = ft_calloc(commands + 1, sizeof(char *));
    if (!list_commands)
        return (NULL);
        
    if (!redir_command_spliter(list_commands, (char *)s))
    {
        free(list_commands);
        return (NULL);
    }
    return (list_commands);
}

/* Implementación de remove_redirection_tokens */
static void remove_redirection_tokens(char **tokens)
{
    int i = 0;
    int j;
    
    if (!tokens)
        return;
        
    while (tokens[i])
    {
        if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], "<<") == 0 ||
            ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0)
        {
            free(tokens[i]);
            free(tokens[i + 1]);
            j = i;
            while (tokens[j + 2])
            {
                tokens[j] = tokens[j + 2];
                j++;
            }
            tokens[j] = NULL;
            tokens[j + 1] = NULL;
        }
        else
            i++;
    }
}

/* Implementación de parse_redirections */
static void parse_redirections(t_token *token)
{
    if (!token)
        return;
        
    detect_redirections(token);
    remove_redirection_tokens(token->tokens);
}
