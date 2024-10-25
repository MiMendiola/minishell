/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:12:45 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/25 17:18:32 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_iofile	*first_iofile(t_iofile *lst)
{
	while (lst && lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}

t_iofile	*last_iofile(t_iofile *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	read_till_character_redir(char *input, int *start, int *counter)
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
		else if (is_redir(input, *counter) || input[*counter] == ' '
			|| input[*counter] == '\t' || input[*counter] == '\n')
			break ;
		(*counter)++;
	}
}
