/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:08:26 by anadal-g          #+#    #+#             */
/*   Updated: 2024/05/10 17:25:41 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	jump_character(char *str, int *counter, char c, int flag)
{
	if (flag)
		while (str[*counter] && character_finder(str[*counter], c))
        	(*counter)++;
	else
		while (str[*counter] && !character_finder(str[*counter], c))
        	(*counter)++;
}

void	jump_quotes(char *str, int *start, int *counter)
{
	char	quote;

	*start = *counter;
	while (str[*counter])
	{
		if (str[*counter] == '\"' || str[*counter] == '\'')
		{
			quote = str[(*counter)++];
			jump_character(str, counter, quote, FALSE);
		}
		else if (character_finder(str[*counter], '|'))
			break ;
		(*counter)++;
	}
}

static int	write_str(char **r, char *str, char c)
{
	int i = 0;
    int j;
    int words = 0;
    char *tmp_substr;
    char *tmp_trim;

    while (str[i])
    {
		jump_character(str, &i, c, TRUE);
        if (str[i] == '\0')
            break;
        jump_quotes(str, &j, &i);
        tmp_substr = ft_substr(str, j, i - j);
        if (tmp_substr == NULL)
            return (free_matrix_bool(r));
        tmp_trim = ft_strtrim(tmp_substr, " ");
        free(tmp_substr);
        if (tmp_trim == NULL)
            return (free_matrix_bool(r));
        r[words] = tmp_trim;
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
			jump_character(str, &i, quote, FALSE);
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
