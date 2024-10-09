/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:49:47 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/09 16:36:25 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(t_token *token)
{
	return (token->type == OPERATOR);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (is_operator(curr))
		{
			// Verifica que no haya operadores al principio o al final
			if (!curr->prev || !curr->next)
			{
				ft_putstr_fd("---------------------------------\n", STDERR_FILENO);
				return (0);
			}
			// Verifica que no haya dos operadores consecutivos
			if (is_operator(curr->prev) || is_operator(curr->next))
			{
				ft_putstr_fd("Syntax error: consecutive operators\n",
					STDERR_FILENO);
				return (0);
			}
			// Operdores invalidos
			if ((ft_strlen(curr->content) > 2) || (ft_strcmp(curr->content, "<>") == 0) || (ft_strcmp(curr->content, "><") == 0))
			{
                ft_putstr_fd("Syntax error: invalid operator sequence\n", STDERR_FILENO);
                return (0);
			}
		curr = curr->next;
		}
	}
	return (1);
}

void	divide_tokens(char *input, t_token **token_list)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		if (input[i] == '<' || input[i] == '>')
		{
			if (input[i + 1] == input[i]) // << o >>
			{
				token = ft_substr(input, i, 2);
				i += 2;
			}
			else // < o >
			{
				token = ft_substr(input, i, 1);
				i++;
			}
			create_tokens(token, token_list);
			free(token);
		}
		else
		{
			j = i;
			while (input[i] && !ft_isspace(input[i]) && input[i] != '<'
				&& input[i] != '>')
				i++;
			token = ft_substr(input, j, i - j);
			create_tokens(token, token_list);
			free(token);
		}
	}
	// if (!validate_tokens(*token_list))
	// {
	// 	ft_putstr_fd("Error after tokenization", STDERR_FILENO);
	// 	return ;
	// }
	// if (!validate_syntax(*token_list))
	// {
	// 	ft_putstr_fd("Error after syntax validation\n", STDERR_FILENO);
	// 	return ;
	// }
}
/*
  TODO
  Si hay redirecciones manejarlas en ejecutor
*/
