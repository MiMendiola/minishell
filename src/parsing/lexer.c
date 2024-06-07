/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:12:11 by mmendiol          #+#    #+#             */
/*   Updated: 2024/06/07 01:44:10 by lmntrix          ###   ########.fr       */
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

void remove_quotes(char *input, char quote) {
    char *dst;
    char *src;
	
    if (!input)
		return;

	dst = input;
	src = input;
    while (*src) {
        if (*src != quote)
		{
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

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
		{
			remove_quotes(tokens->tokens[i], SQUOTES);
			printf("SINGLE %s\n", tokens->tokens[i]);
		}
		i++;
	}
}

void	do_double_quotes(t_token *tokens)
{
	int i;

	i = 0;
	while(tokens->tokens[i])
	{
		if (quote_detector(tokens->tokens[i]) == 1)
		{
			remove_quotes(tokens->tokens[i], DQUOTES);
			printf("DOUBLE %s\n", tokens->tokens[i]);
		}
		i++;
	}
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
			do_double_quotes(aux);
		aux = aux->next;
	}
}