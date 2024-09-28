/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:39:07 by mmendiol          #+#    #+#             */
/*   Updated: 2024/09/28 14:08:43 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_node_tokens(t_token **stack_tokens, char **splited_tokens)
{
	int		i;
	t_token	*node;
	t_token	*node_last;

	i = -1;
	while (splited_tokens[++i])
	{
		if (!*stack_tokens)
			node = create_node(1, splited_tokens[i]);
		else
		{
			node_last = last_node(*stack_tokens);
			node = create_node(node_last->id + 1, splited_tokens[i]);
		}
		add_node_back(stack_tokens, node);
	}
}

void	create_tokens(char *input, t_token **tokens)
{
	char	**tokens_splited;

	if (input != NULL)
	{
		tokens_splited = command_spliter(input, PIPE);
		add_node_tokens(tokens, tokens_splited);
		free(tokens_splited);
	}
	else
		ft_putstr_fd("Error\n", STDERR_FILENO);
}
