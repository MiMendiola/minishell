/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:12:11 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/25 17:19:40 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexerize_process(t_token *aux)
{
	int		i;
	char	**quote_divisor;
	char	*quote_joined;

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
		free_matrix(quote_divisor);
	}
}

void	lexerize(t_token **tokens)
{
	t_token	*aux;

	if (!tokens || !*tokens)
		return ;
	aux = *tokens;
	while (aux)
	{
		lexerize_process(aux);
		aux = aux->next;
	}
}
