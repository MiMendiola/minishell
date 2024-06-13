/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:12:11 by mmendiol          #+#    #+#             */
/*   Updated: 2024/06/13 18:59:54 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_env_value(char *var)
{
    char *value;

	value = getenv(var);
	if (!value)
		value = "";
    return (value);
}

void copy_env_name(const char *src, char *dst)
{
	int i;

	i = 0;
	src++;
    while (*src && *src != ' ' && *src != DQUOTES && *src != '$')
		dst[i++] = *src++;
    dst[i] = '\0';
}

// void	var_expansor(char **input, char **src, char *final)
// {
// 	char	dst[256];
// 	char	*env_value;
	
// 	while (**src && **src != DQUOTES)
// 	{
// 		if (**src == '$')
// 		{
// 			if (ft_isdigit((*src)[1]))
// 			{
// 				*src += 2;
// 				while (**src)
// 					*(*input)++ = *(*src)++;
// 			}
// 			else if (ft_isalpha((*src)[1]))
// 			{
// 				copy_env_name(*src, dst);
// 				*src += ft_strlen(dst);
// 				env_value = get_env_value(dst);
// 				printf("Puta: %s\n", final);
// 				printf("Puta: %s\n", *input);
// 				// TENGO QUE REALOCAR EL TAMAÑO DE LA STRING PARA QUE ENTRE LS EXPANSION COMPLETA (REALLOC)
// 				while (*env_value)
// 					*(*input)++ = *env_value++; 
// 				*(*src) = '\0'; 
// 			}
// 		}
// 		*(*input)++ = *(*src)++;
// 	}
// 	*(*input)++ = **src;
// }

// void	expander(char *input)
// {
// 	char	*src;
// 	char	*dst;

// 	if (!input)
// 		return ;
// 	src = input;
// 	dst = input;
// 	while (*src)
// 	{
//         if (*src == SQUOTES)
// 		{
// 			*input++ = *src++;
// 			while (*src && *src != SQUOTES)
// 				*input++ = *src++;
// 			if (*src == SQUOTES)
// 				*input++ = *src;
// 		}
// 		else if (*src == DQUOTES)
// 		{
// 			*input++ = *src++;
// 			var_expansor(&input, &src, dst);
// 		}
// 		else
//             *input++ = *src;
//         src++;
//     }
// 	*input = '\0';
// }

void	expander(char *str)
{
	char *env_name = ft_calloc(1, ft_strlen(str));
	char *env_value;
	char *found;
	char *final_str;

	while (ft_strchr(str, '$') != NULL)
	{
		found = ft_strchr(str, '$');
		final_str = ft_substr(str, 0, (found - str));
		copy_env_name(found, env_name);
		env_value = get_env_value(env_name);
		final_str = ft_strcat(final_str, env_value);
		if (found + (ft_strlen(env_name) + 1))
			final_str = ft_strcat(final_str, found + (ft_strlen(env_name) + 1));
		ft_strlcpy(str, final_str, ft_strlen(final_str) + 2);
		printf("[%s]\n", final_str);
	}
}


void	remove_quotes(char *input)
{
	char	*src;
	char	exterior_quote;

	if (!input)
		return ;
	src = input;
	exterior_quote = 0;
	while (*src)
	{
        if ((*src == DQUOTES || *src == SQUOTES) && (exterior_quote == 0 || exterior_quote == *src))
		{
            if (exterior_quote == 0)
                exterior_quote = *src;
			else if (exterior_quote == *src)
                exterior_quote = 0;
        }
		else
            *input++ = *src;
		src++;
    }
	*input = '\0';
}

void lexerize(t_token **tokens)
{
    int i;
    t_token *aux;

    if (!tokens || !*tokens)
        return;
    aux = *tokens;
    while (aux)
	{
        i = -1;
        while (aux->tokens[++i])
		{
			if (ft_strchr_bool(aux->tokens[i], '$'))
				expander(aux->tokens[i]);
        	remove_quotes(aux->tokens[i]);
		}
        aux = aux->next;
    }
}







/*

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

int	quote_detector(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == SQUOTES)
			return (1);
		else if (s[i] == DQUOTES)
			return (2);
		i++;
	}
	return (0);
}

void	do_single_quotes(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens->tokens[i])
	{
		if (quote_detector(tokens->tokens[i]) == 1)
		{
			remove_quotes(tokens->tokens[i]);
			printf("SINGLE %s\n", tokens->tokens[i]);
		}
		i++;
	}
}

void	do_double_quotes(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens->tokens[i])
	{
		if (quote_detector(tokens->tokens[i]) == 2)
		{
			remove_quotes(tokens->tokens[i]);
			printf("DOUBLE %s\n", tokens->tokens[i]);
		}
		i++;
	}
}

void	lexerize(t_token **tokens)
{
	int i;
	t_token *aux;

	aux = *tokens;
	if (!tokens || !*tokens)
		return ;
	while (aux)
	{
		i = -1;
		while (aux->tokens[++i])
		{
			if (quote_detector(aux->tokens[i]) == 1)
				do_single_quotes(aux);
			else if (quote_detector(aux->tokens[i]) == 2)
				do_double_quotes(aux);
		}
		aux = aux->next;
	}
}*/
