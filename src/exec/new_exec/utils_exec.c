/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:23:37 by anadal-g          #+#    #+#             */
/*   Updated: 2024/12/17 12:09:42 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	add_iofile(t_iofile **list, char *filename, enum e_iotype type)
{
	t_iofile	*new_file;
	t_iofile	*tmp;
	new_file = ft_calloc(1, sizeof(t_iofile));
	if (!new_file)
		return ;
	new_file->name = ft_strdup(filename);
	new_file->fd = -1;
	new_file->type = type;
	new_file->next = NULL;
	if (*list == NULL)
	{
		new_file->prev = NULL;
		*list = new_file;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_file;
		new_file->prev = tmp;
	}
}

enum e_iotype	get_redirection_type(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return INFILE;
	else if (ft_strcmp(token, "<<") == 0)
		return HEREDOC;
	else if (ft_strcmp(token, ">") == 0)
		return TRUNC;
	else if (ft_strcmp(token, ">>") == 0)
		return APPEND;
	else
		return -1;
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

void	parse_redirections(t_token *token)
{
	detect_redirections(token);
	remove_redirection_tokens(token->tokens);
}

