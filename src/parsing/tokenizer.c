/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:59:18 by mmendiol          #+#    #+#             */
/*   Updated: 2024/05/11 19:59:44 by mmendiol         ###   ########.fr       */
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
	int		i;
	char	**tokens_splited;

	i = 0;
	if (input != NULL)
	{
		tokens_splited = command_spliter(input, PIPE);
		add_node_tokens(tokens, tokens_splited);
		free(tokens_splited);
	}
	else
		ft_putstr_fd("Error\n", STDERR_FILENO);
}

/*	TODO
	
	Ahora hay un problema con la separacion de tokens, porque al hacer el split de la cadena por espacios
	me quita todos hata los que estan por la parte interior de las quotes.
	Ahora necesito dividir la cadenas por ' o " o < o > o 
	Necesito un token_spliter
*/