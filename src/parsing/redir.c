/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:20:05 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/14 17:28:42 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int write_redirections(char **list_parts, char *s)
{
    int i = 0;
    int j = 0;

    while (s[i])
    {
        if (s[i] == '>' || s[i] == '<')
        {
            if (s[i + 1] == s[i])
            {
                list_parts[j++] = ft_substr(s, i, 2);
                i += 2;
            }
            else
            {
                list_parts[j++] = ft_substr(s, i, 1);
                i++;
            }
        }
        else if (!ft_isspace(s[i]))
        {
            int start = i;
            while (s[i] && !ft_isspace(s[i]) && s[i] != '>' && s[i] != '<')
                i++;
            list_parts[j++] = ft_substr(s, start, i - start);
        }
        else
            i++;
    }
    return (1);
}


int redirection_counter(char *s)
{
    int count = 0;
    int i = 0;

    while (s[i])
    {
        if (s[i] == '>' || s[i] == '<')
        {
            count++;
            if (s[i + 1] == s[i]) //>> o <<
                i++;
        }
        else if (!ft_isspace(s[i]))
            count++;
        i++;
    }
    return (count);
}


char    **redirection_splitter(char const *s)
{
    int     parts;
    char    **list_parts;

    if (!s)
        return (NULL);
    parts = redirection_counter((char *)s);
    list_parts = ft_calloc(parts + 1, sizeof(char *));
    if (!list_parts)
        return (NULL);
    if (!write_redirections(list_parts, (char *)s))
        return (NULL);
    return (list_parts);
}
