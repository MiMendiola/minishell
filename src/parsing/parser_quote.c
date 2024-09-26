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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DQUOTES '"'
#define SQUOTES '\''


void	jump_character(char *str, int *i, char quote)
{
	while (str[*i] && str[*i] != quote)
		(*i)++;
}

int	character_finder(char c)
{
	return (c == DQUOTES || c == SQUOTES);
}

void    conditional_quote_counter(char *str, int *i, int *commands)
{
	char	quote;
    int		in_quotes;

	quote = 0;
    in_quotes = 0;
    while (str[++(*i)])
    {
        if (str[*i] == SQUOTES || str[*i] == DQUOTES)
        {
            quote = str[(*i)++];
            jump_character(str, i, quote);
            (*commands)++;
            in_quotes = 0;
        }
        else if (!character_finder(str[*i]))
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
	int		i;
	int		commands;

	i = -1;
	commands = 0;
	conditional_quote_counter(str, &i, &commands);





	return (commands);
}

char *ft_strndup(const char *s, size_t n)
{
    char	*dst;
	int		i;
    int     len;

	i = 0;
    len = 0;
    while (len < (int)n && s[len])
    {
        len++;
    }

	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		return (NULL);
	while (s[i] && len > i)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}


char **quote_command_split(char *str)
{
    int i = 0;
    int j = 0;
    int start = 0;
    int num_tokens = quote_command_counter(str);
    char **tokens = ft_calloc((num_tokens + 1), sizeof(char *));
    char quote = 0;
    
    while (str[i])
    {
        while (character_finder(str[i]))
            i++;
        start = i;
        if (str[i] == SQUOTES || str[i] == DQUOTES)
        {
            quote = str[i++];
            while (str[i] && str[i] != quote) i++;
            tokens[j] = ft_strndup(&str[start], i - start + 1);
        }
        else
        {
            while (str[i] && !character_finder(str[i]) && str[i] != SQUOTES && str[i] != DQUOTES)
                i++;
            tokens[j] = ft_strndup(&str[start], i - start);
        }
        j++;
        i++;
    }
    tokens[j] = NULL;
    return tokens;
}

int main() {
    char str[] = "\"sfd     hello\"     'rwer example'    \"hola\"      asdasd dfsfdsf     \"tardes buenas\"   'asd'    ddfgdf     g";
    char **tokens = quote_command_split(str);

    printf("Token %d: %s\n", 1, tokens[0]);
    printf("Token %d: %s\n", 2, tokens[1]);
    printf("Token %d: %s\n", 3, tokens[2]);
    printf("Token %d: %s\n", 4, tokens[3]);
    printf("Token %d: %s\n", 5, tokens[4]);
    printf("Token %d: %s\n", 6, tokens[5]);
    printf("Token %d: %s\n", 7, tokens[6]);
    printf("Token %d: %s\n", 8, tokens[7]);
    printf("Token %d: %s\n", 9, tokens[8]);
    printf("Token %d: %s\n", 9, tokens[9]);
    printf("Token %d: %s\n", 9, tokens[10]);
    
    free(tokens);
    return 0;
}
