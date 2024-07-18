/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:44:23 by mmendiol          #+#    #+#             */
/*   Updated: 2024/07/18 17:43:40 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *var)
{
	char	*value;

	value = getenv(var);
	if (!value)
		value = "";
	return (value);
}

void	copy_env_name(char **src, char *dst)
{
	int	i;

	i = 0;
	(*src)++;
	if (**src == '?')
	{
		(*src)++;
		return;
	}
	else if (!ft_isalpha(**src))
	{
		(*src)++;
		return;
	}
	while (**src && **src != ' ' && **src != DQUOTES && **src != SQUOTES
		&& **src != '$')
		dst[i++] = *(*src)++;
	dst[i] = '\0';
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*orig;

	orig = dest;
	while
		((*dest++ = *src++));
	return (orig);
}


void expand_variables(char **tmp_str, char **str, char **found, char *env_name)
{
    char	*env_value;
	
	copy_env_name(found, env_name);
	env_value = get_env_value(env_name);
	*tmp_str = ft_realloc(*tmp_str, ft_strlen(*tmp_str), ft_strlen(*tmp_str)
			+ ft_strlen(env_value) + 1);
	*tmp_str = ft_strcat(*tmp_str, env_value);
	// *found += ft_strlen(env_name) + 1;
	*str = *found;
	*found = ft_strchr(*found, '$');
	if (*found && ft_strcmp(*str, *found))
	{
		*tmp_str = ft_realloc(*tmp_str, ft_strlen(*tmp_str),
				(ft_strlen(*tmp_str) + (*found - *str)));
		ft_strlcat(*tmp_str, *str, (ft_strlen(*tmp_str) + (*found - *str) + 1));
	}
}


void	expander(t_token *aux, char *str, int i)
{
	char	*found;
	char	*env_name;
	char	*tmp_str;

	env_name = ft_calloc(1, ft_strlen(str));
	tmp_str = ft_calloc(1, ft_strlen(str) + 1);
	found = ft_strchr(str, '$');
	ft_strlcat(tmp_str, str, (found - str) + 1);
	while (found != NULL)
	{
		expand_variables(&tmp_str, &str, &found, env_name);
	}
	tmp_str = ft_realloc(tmp_str, ft_strlen(tmp_str), (ft_strlen(tmp_str)
				+ ft_strlen(str)));
	tmp_str = ft_strcat(tmp_str, str);
	aux->tokens[i] = ft_realloc(aux->tokens[i], ft_strlen(aux->tokens[i]),
			ft_strlen(tmp_str));
	ft_strcpy(aux->tokens[i], tmp_str);
	(free(env_name), free(tmp_str));
}
