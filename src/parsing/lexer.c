/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:12:11 by mmendiol          #+#    #+#             */
/*   Updated: 2024/06/05 17:59:36 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_quote(char *input)
{
	char	quote;

	while (*input)
	{
		if (*input == DQUOTES || *input == SQUOTES)
		{
			quote = *input;
			input++;
			while (!character_finder(*input, quote))
			{
				printf("%c", *input);
				input++;
			}
		}
		else
			printf("%c", *input);
		input++;
	}
}


/*TODO - FUNCION QUE ME SALTE LAS ' O LAS " Y ME ESCRIBA TODO LO DEMAS EN ELLA*/


int	quote_detector(const char *s)
{
	size_t			i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			return (1);
		else if (s[i] == '\"')
			return (2);
		i++;
	}
	return (0);
}

void	do_single_quotes(t_token *tokens)
{
	int i;

	i = 0;
	while(tokens->tokens[i])
	{
		if (quote_detector(tokens->tokens[i]) == 1)
			printf("SINGLE %s\n", tokens->tokens[i]);
		i++;
	}
}

void	do_double_quotes()
{
	printf("DOUBLE \'\n");
}

void	lexer_state(t_token **tokens)
{
	t_token	*aux;

	aux = *tokens;
	if (!tokens || !*tokens)
		return ;
	while (aux)
	{
		if (quote_detector(aux->command) == 1)
			do_single_quotes(aux);
		else if (quote_detector(aux->command) == 2)
			do_double_quotes();
		aux = aux->next;
	}
}