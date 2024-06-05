/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:59:18 by mmendiol          #+#    #+#             */
/*   Updated: 2024/05/28 13:35:11 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	write_token(char **r, char *str, char c)
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
		if (str[i] == '\0')
			break ;
		read_till_character(str, &j, &i, c);
		tmp_substr = ft_substr(str, j, (i + 1) - j);
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

int	token_counter(char *str, char c)
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

char	**tokenizer(char const *command)
{
	int		tokens;
	char	**list_tokens;

	if (!command)
		return (0);
	tokens = token_counter((char *)command, ' ' | '<' | '>');
	printf("%d\n",tokens);
	list_tokens = ft_calloc(tokens + 1, sizeof(char *));
	if (!list_tokens)
		return (NULL);
	if (!write_token(list_tokens, (char *)command, ' ' | '<' | '>'))
		return (NULL);
	return (list_tokens);
}



/* TODO - Uns funcion que dependiendo de < << >> > me lo divida
		lo guarde en mi estructura guardando todos los tokens ordenados
*/
