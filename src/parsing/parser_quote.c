/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:11:05 by mmendiol          #+#    #+#             */
/*   Updated: 2024/09/19 21:36:32 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quote_detector(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == SQUOTES || s[i] == DQUOTES)
			return (1);
		i++;
	}
	return (0);
} 

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








void	jump_character(char *input, int *counter, char c, int flag)
{
	if (flag)
		while (input[*counter] && character_finder(input[*counter], c))
			(*counter)++;
	else
		while (input[*counter] && !character_finder(input[*counter], c))
			(*counter)++;
}

int	quote_command_counter(char *str)
{
	int		i;
	int		commands;
	char	quote;

	i = -1;
	commands = 0;
	while (str[++i])
	{
		if (str[i] && (str[i] == DQUOTES || str[i] == SQUOTES))
		{
			quote = str[i++];
			jump_character(str, &i, quote, FALSE);
		}
		if (!character_finder(str[i], c) && (character_finder(str[i + 1], c)
				|| str[i + 1] == '\0'))
			commands++;
	}
	return (commands);
}

void	read_till_character(char *input, int *start, int *counter, char c)
{
	char	quote;

	*start = *counter;
	while (input[*counter])
	{
		if (input[*counter] == DQUOTES || input[*counter] == SQUOTES)
		{
			quote = input[(*counter)++];
			jump_character(input, counter, quote, FALSE);
		}
		else if (character_finder(input[*counter], c))
			break ;
		(*counter)++;
	}
}

int	write_quote_command(char **r, char *str, char c)
{
	int		i;
	int		j;
	int		comands;
	char	*tmp_substr;
	char	*tmp_trim;

	i = 0;
	comands = 0;
	while (str[i])
	{
		jump_character(str, &i, c, TRUE);
		if (str[i] == '\0')
			break ;
		read_till_character(str, &j, &i, c);
		tmp_substr = ft_substr(str, j, i - j);
		if (tmp_substr == NULL)
			return (free_matrix_bool(r));
		tmp_trim = ft_strtrim(tmp_substr, " ");
		free(tmp_substr);
		if (tmp_trim == NULL)
			return (free_matrix_bool(r));
		r[comands] = tmp_trim;
		comands++;
	}
	return (1);
}

char	**quote_spliter(char const *s, char c)
{
	int		commands;
	char	**list_commands;

	if (!s)
		return (0);
	commands = quote_command_counter((char *)s);
	list_commands = ft_calloc(commands + 1, sizeof(char *));
	if (!list_commands)
		return (NULL);
	if (!write_quote_command(list_commands, (char *)s, c))
		return (NULL);
	return (list_commands);
}


