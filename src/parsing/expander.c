/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:45:31 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/08 12:16:01 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest + ft_strlen(dest);
	while (*src != '\0')
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';
	return (dest);
}
// char	*get_env_value(t_env *env_list,char *var)
// {
// 	t_env	*env_var;

// 	env_var = ft_find_env(env_list, var);
// 	if (env_var)
// 		return (env_var->value);
// 	return (""); // si no lo encuentra devulve cadena vacia
// 	// char	*value;

// 	// value = getenv(var);
// 	// if (!value)
// 	// 	value = "";
// 	// return (value);
// }

char	*get_env_value(char *var)
{
	char	*value;

	value = getenv(var);
	if (!value)
		value = "";
	return (value);
}
void	*ft_realloc(void *ptr, size_t original_size, size_t new_size)
{
	void	*new_ptr;
	size_t	size_to_cpy;

	if (new_size == 0)
		return (free(ptr), NULL);
	new_ptr = ft_calloc(1, new_size + 1);
	if (!new_ptr)
		return (free(ptr), NULL);
	if (ptr)
	{
		if (original_size < new_size)
			size_to_cpy = original_size;
		else
			size_to_cpy = new_size;
		ft_memcpy(new_ptr, ptr, size_to_cpy);
		free(ptr);
	}
	return (new_ptr);
}
void	copy_env_name(char **src, char *dst)
{
	int	i;

	i = 0;
	(*src)++;         // salta el $
	if (**src == '?') // maneja caso especial $?
	{
		(*src)++;
		return ;
	}
	else if (!ft_isalpha(**src) && **src != DQUOTES && **src != SQUOTES)
	{
		(*src)++;
		dst = ft_strcat(dst, *src);
		return ;
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
	while ((*dest++ = *src++))
		;
	return (orig);
}

void	expand_variables(char **tmp_str, char **str, char **found,
		char *env_name)
{
	char	*env_value;

	copy_env_name(found, env_name);
	env_value = get_env_value(env_name);
	*tmp_str = ft_realloc(*tmp_str, ft_strlen(*tmp_str), ft_strlen(*tmp_str)
			+ ft_strlen(env_value) + 1);
	*tmp_str = ft_strcat(*tmp_str, env_value);
	*str = *found;
	*found = ft_strchr(*found, '$');
	if (*found && ft_strcmp(*str, *found))
	{
		*tmp_str = ft_realloc(*tmp_str, ft_strlen(*tmp_str),
				(ft_strlen(*tmp_str) + (*found - *str)));
		ft_strlcat(*tmp_str, *str, (ft_strlen(*tmp_str) + (*found - *str) + 1));
	}
}

char	*found_dollar_not_squotes(char *str)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*str)
	{
		if (*str == '"' && !single_quotes)
			double_quotes = !double_quotes;
		else if (*str == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if (*str == '$' && (!single_quotes || double_quotes))
			return (str);
		str++;
	}
	return (0);
}

void	expander(t_token *aux, char *str, int i)
{
	char	*found;
	char	*env_name;
	char	*tmp_str;

	env_name = ft_calloc(1, ft_strlen(str) + 1);
	tmp_str = ft_calloc(1, ft_strlen(str) + 1);
	/* Aqui utilizaba ft_strchr(str, $),
		ahora uso found para encontrar de primeras el $ que no esta en las comillas simples */
	found = found_dollar_not_squotes(str);
	ft_strlcat(tmp_str, str, (found - str) + 1);
	while (found != NULL)
	{
		if (dollar_not_between_squotes(found))
			expand_variables(&tmp_str, &str, &found, env_name);
		found = ft_strchr(found + 1, '$');
	}
	// redimensiona la cadena para incluir el comando
	tmp_str = ft_realloc(tmp_str, ft_strlen(tmp_str), (ft_strlen(tmp_str)
				+ ft_strlen(str) + 1));
	if (!tmp_str)
	{
		return (free(env_name));
		return ;
	}
	tmp_str = ft_strcat(tmp_str, str); // añade el resyto del comando
	// redimensiona la cadena y la copia ya expandida
	aux->tokens[i] = ft_realloc(aux->tokens[i], ft_strlen(aux->tokens[i]),
			ft_strlen(tmp_str) + 1);
	ft_strcpy(aux->tokens[i], tmp_str);
	(free(env_name), free(tmp_str));
}
