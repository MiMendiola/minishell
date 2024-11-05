/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:02:31 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/14 18:24:33 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*last_node(t_token *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_node_back(t_token **stack, t_token *new)
{
	t_token	*aux;

	aux = last_node(*stack);
	if (*stack != NULL)
	{
		new->prev = aux;
		new->next = NULL;
		aux->next = new;
	}
	else
		*stack = new;
}

t_token	*create_node(int id, char *command)
{
	t_token	*tokens;

	tokens = ft_calloc(1, sizeof(t_token));
	if (!tokens)
		return (NULL);
	tokens->id = id;
	tokens->command = command;
	tokens->tokens = command_spliter(command, ' ');
	// tokens->tokens = redirection_splitter(command);
	tokens->prev = NULL;
	tokens->next = NULL;
	return (tokens);
}
