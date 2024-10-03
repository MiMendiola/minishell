/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:11:05 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/02 20:00:29 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	quote_equal(char c)
{
	return (c == DQUOTES || c == SQUOTES);
}

void	conditional_quote_counter(char *str, int *i, int *commands)
{
	char	quote;
	int		in_quotes;

	quote = 0;
	in_quotes = 0;
	while (str[++(*i)])
	{
		if (quote_equal(str[*i]))
		{
			quote = str[(*i)++];
			jump_character(str, i, quote, FALSE);
			(*commands)++;
			in_quotes = 0;
		}
		else if (!quote_equal(str[*i]))
		{
			if (!in_quotes)
			{
				(*commands)++;
				in_quotes = 1;
			}
		}
		else
			in_quotes = 0;
	}
}

int	quote_command_counter(char *str)
{
	int	i;
	int	commands;

	i = -1;
	commands = 0;
	conditional_quote_counter(str, &i, &commands);
	return (commands);
}

void	extract_token(char *str, int *i, int *j, char **tokens)
{
	int		start;
	int		in_quotes;
	char	quote;

	start = *i;
	in_quotes = 0;
	if (quote_equal(str[*i]))
	{
		in_quotes = 1;
		quote = str[(*i)++];
		while (str[*i] && str[*i] != quote)
			(*i)++;
		tokens[*j] = ft_strndup(&str[start], ++(*i) - start);
	}
	else
	{
		while (str[*i] && !quote_equal(str[*i]))
			(*i)++;
		tokens[*j] = ft_strndup(&str[start], *i - start);
	}
	if (in_quotes)
		in_quotes = 0;
	(*j)++;
}

char	**quote_command_split(char *str)
{
	int		i;
	int		j;
	int		num_tokens;
	char	**tokens;

	i = 0;
	j = 0;
	num_tokens = quote_command_counter(str);
	tokens = ft_calloc((num_tokens + 1), sizeof(char *));
	if (!tokens)
		return (NULL);
	while (str[i])
		extract_token(str, &i, &j, tokens);
	tokens[j] = NULL;
	return (tokens);
}
