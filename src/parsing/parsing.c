/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:08:26 by anadal-g          #+#    #+#             */
/*   Updated: 2024/05/09 19:40:15 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	jump_quotes(char *str, int *counter)
{
	char	quote;

	while (str[*counter])
	{
		if (str[*counter] == '\"' || str[*counter] == '\'')
		{
			quote = str[(*counter)++];
			while (str[*counter] && str[*counter] != quote)
				(*counter)++;
		}
		else if (character_finder(str[*counter], '|'))
			break ;
		(*counter)++;
	}
}

static int	write_str(char **r, char *str, char c)
{
	int	i;
	int	j;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && character_finder(str[i], c))
			i++;
		if (str[i] == '\0')
			break ;
		j = i;
		jump_quotes(str, &i);
		r[words] = ft_substr(str, j, i - j);
		if (r[words] == NULL)
			return (free_matrix_bool(r));
		words++;
	}
	return (1);
}

static int	tokens_counter(char *str, char c)
{
	int		i;
	int		token;
	char	quote;

	i = -1;
	token = 0;
	while (str[++i])
	{
		if (str[i] && (str[i] == '\"' || str[i] == '\''))
		{
			quote = str[i++];
			while (str[i] && !character_finder(str[i], quote))
				i++;
		}
		if (!character_finder(str[i], c) && (character_finder(str[i + 1], c)
				|| str[i + 1] == '\0'))
			token++;
	}
	return (token);
}

char	**pipe_spliter(char const *s)
{
	int		tokens;
	char	**res;

	if (!s)
		return (0);
	tokens = tokens_counter((char *)s, '|');
	printf("%d\n", tokens);
	res = ft_calloc(tokens + 1, sizeof(char *));
	if (!res)
		return (NULL);
	if (!write_str(res, (char *)s, '|'))
		return (NULL);
	return (res);
}
