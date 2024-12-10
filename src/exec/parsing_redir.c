/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:01:43 by mmendiol          #+#    #+#             */
/*   Updated: 2024/12/10 12:21:08 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
