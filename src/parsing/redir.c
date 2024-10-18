/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:49:47 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/18 19:11:53 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	read_hasta_caracter(char *input, int *start, int *counter)
{
	char	quote;

	*start = *counter;
	while (input[*counter])
	{
		if (input[*counter] == DQUOTES || input[*counter] == SQUOTES)
		{
			quote = input[(*counter)++];
			jump_character(input, counter, quote, TRUE);
		}
		else if (is_redir(input, *counter))
			break ;
		(*counter)++;
	}
}

int	process_operator_or_space(char **r, char *str, int *i, int *commands)
{
    int op_len;

    while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'))
        (*i)++;
    if (str[*i] == '\0')
        return (0);
    op_len = is_redir(str, *i);
    if (op_len)
    {
        r[(*commands)++] = ft_substr(str, *i, op_len);
        *i += op_len;
        return (1);
    }
    return (0);
}

int	redir_command_spliter(char **r, char *str)
{
	int		i;
	int		j;
	int		commands;
	char	*tmp_substr;
	char	*tmp_trim;

	i = 0;
	commands = 0;
	while (str[i])
	{
		if (process_operator_or_space(r, str, &i, &commands))
			continue;
		read_hasta_caracter(str, &j, &i);
		tmp_substr = ft_substr(str, j, i - j);
		if (!tmp_substr || !*tmp_substr)
			continue;
		tmp_trim = ft_strtrim(tmp_substr, " ");
		free(tmp_substr);
		if (!tmp_trim)
			return (0);
		r[commands++] = tmp_trim;
	}
	r[commands] = NULL;
	return (1);
}

void	conditional_operator_counter(char *str, int *i, int *commands)
{
	int		op_len;
	int		in_word;

	in_word = 0;
	while (str[++(*i)])
	{
		op_len = is_redir(str, *i);
		if (op_len)
		{
			(*commands)++;
			*i += (op_len - 1);
			in_word = 0;
		}
		else if (!is_redir(str, *i))
		{
			if (!in_word)
			{
				(*commands)++;
				in_word = 1;
			}
		}
	}
}

int	redir_counter(char *str)
{
	int	i;
	int	commands;

	i = -1;
	commands = 0;
	conditional_operator_counter(str, &i, &commands);
	return (commands);
}

char	**redir_divisor(char const *s)
{
	int		commands;
	char	**list_commands;

	if (!s)
		return (0);
	commands = redir_counter((char *)s);
	list_commands = ft_calloc(commands + 1, sizeof(char *));
	if (!list_commands)
		return (NULL);
	if (!redir_command_spliter(list_commands, (char *)s))
		return (NULL);
	return (list_commands);
}
