/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:01:43 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/25 17:02:47 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

enum e_iotype	get_redirection_type(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (INFILE);
	else if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(token, ">") == 0)
		return (TRUNCT);
	else if (ft_strcmp(token, ">>") == 0)
		return (APPEND);
	else
		return (-1);
}

void	detect_redirections(t_token *token)
{
	int				i;
	enum e_iotype	type;
	char			**tokens;

	tokens = token->tokens;
	i = 0;
	while (tokens[i])
	{
		type = get_redirection_type(tokens[i]);
		if ((int)type == -1)
		{
			i++;
			continue ;
		}
		if (tokens[i + 1])
		{
			if (type == INFILE || type == HEREDOC)
				add_iofile(&token->infile, tokens[i + 1], type);
			else
				add_iofile(&token->outfile, tokens[i + 1], type);
		}
		i += 2;
	}
}

void	remove_redirection_tokens(char **tokens)
{
	int	i;
	int	j;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], "<<") == 0
			|| ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i],
				">>") == 0)
		{
			free(tokens[i]);
			free(tokens[i + 1]);
			j = i;
			while (tokens[j + 2])
			{
				tokens[j] = tokens[j + 2];
				j++;
			}
			tokens[j] = NULL;
			tokens[j + 1] = NULL;
		}
		else
			i++;
	}
}

void	rebuild_command(t_token *token)
{
	int		i;
	char	*new_command;
	char	*tmp;

	i = 0;
	new_command = ft_strdup("");
	while (token->tokens[i])
	{
		tmp = new_command;
		new_command = ft_strjoin(new_command, token->tokens[i]);
		free(tmp);
		if (token->tokens[i + 1])
		{
			tmp = new_command;
			new_command = ft_strjoin(new_command, " ");
			free(tmp);
		}
		i++;
	}
	free(token->command);
	token->command = new_command;
}

void	parse_redirections(t_token *token)
{
	detect_redirections(token);
	remove_redirection_tokens(token->tokens);
	rebuild_command(token);
}
