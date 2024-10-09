/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:39:07 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/09 16:34:15 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_node_tokens(t_token **stack_tokens, char **splited_tokens)
{
	int		i;
	t_token	*node;
	t_token	*node_last;

	i = -1;
	while (splited_tokens[++i])
	{
		printf("Token[%d]: %s\n", i, splited_tokens[i]);
		if (ft_strcmp(splited_tokens[i], "|") || ft_strcmp(splited_tokens[i],
				">") || ft_strcmp(splited_tokens[i], ">>")
			|| ft_strcmp(splited_tokens[i], "<"))
			node = create_node_operator(splited_tokens[i]);
		else
		{
			if (!*stack_tokens)
				node = (t_token *)create_node(1, splited_tokens[i]);
			else
			{
				node_last = last_node(*stack_tokens);
				node = (t_token *)create_node(node_last->id + 1, splited_tokens[i]);
			}
		}
		if (!node || !node->tokens)
		{
			node->tokens = ft_calloc(2, sizeof(char *));
			if (!node->tokens)
			{
				ft_putstr_fd("Error: No se pudo crear el nodo para el token.\n",
					STDERR_FILENO);
				return ;
			}
			node->tokens[0] = ft_strdup(splited_tokens[i]);
			node->tokens[1] = NULL;
		}
		add_node_back(stack_tokens, node);
	}
}

t_token	*create_node_operator(char *operator)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->type = OPERATOR;
	new_node->content = ft_strdup(operator);
	if (!new_node->content)
	{
		printf("Fallo al duplicar el operador\n");
		free(new_node);
		return (NULL);
	}
	new_node->tokens = ft_calloc(2, sizeof(char *));
	if (!new_node->tokens)
	{
		printf(" Fallo en la asignación de tokens\n");
		free(new_node->content);
		free(new_node);
		return (NULL);
	}
	new_node->tokens[0] = ft_strdup(operator);
	new_node->tokens[1] = NULL;
	new_node->next = NULL;
	return (new_node);
}

int	validate_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == OPERATOR)
		{
			if (!current->next || current->next->type == OPERATOR)
			{
				ft_putstr_fd("Syntax error: invalid use of operator\n",
					STDERR_FILENO);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

void	create_tokens(char *input, t_token **tokens)
{
	char	**tokens_splited;

	if (input != NULL)
	{
		tokens_splited = command_spliter(input, PIPE);
		add_node_tokens(tokens, tokens_splited);
		free(tokens_splited);
	}
	else
		ft_putstr_fd("Error\n", STDERR_FILENO);
}

// void	create_tokens(char *input, t_token **tokens)
// {
// 	char	**tokens_splited;

// 	tokens_splited = command_spliter(input, PIPE);
// 	if (!tokens_splited || !*tokens_splited)
// 	{
// 		ft_putstr_fd("Error, fallo en la tokenizacion \n", STDERR_FILENO);
// 		return ;
// 	}
// 	if (!*tokens)
// 	{
// 		*tokens = ft_calloc(1, sizeof(t_token));
// 		if (!*tokens)
// 		{
// 			ft_putstr_fd("Error: No se pudo asignar memoria para tokens.\n",
// 				STDERR_FILENO);
// 			free(tokens_splited);
// 			return ;
// 		}
// 	}
// 	add_node_tokens(tokens, tokens_splited);
// 	free(tokens_splited);
// }
