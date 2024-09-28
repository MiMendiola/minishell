/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:12:11 by mmendiol          #+#    #+#             */
/*   Updated: 2024/09/28 14:04:37 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexerize(t_token **tokens)
{
	int		i;
	t_token	*aux;
	char	**quote_divisor;
	char	*quote_joined;

	if (!tokens || !*tokens)
		return ;
	aux = *tokens;
	while (aux)
	{
		i = -1;
		while (aux->tokens[++i])
		{
			quote_divisor = quote_command_split(aux->tokens[i]);
			expander(quote_divisor);
			quote_joined = quote_joiner(quote_divisor);
			if (quote_joined)
			{
				free(aux->tokens[i]);
				aux->tokens[i] = quote_joined;
			}
			quotes_remover(aux->tokens[i]);
		}
		aux = aux->next;
	}
}
