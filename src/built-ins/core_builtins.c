/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:01:25 by mmendiol          #+#    #+#             */
/*   Updated: 2024/06/17 17:55:05 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	select_builtin(t_token **tokens, char *input)
{
	t_token	*aux;

	aux = *tokens;
	if (!tokens || !*tokens)
		return ;
	while (aux)
	{
		if (ft_strcmp(aux->command, EXIT_TXT) == 0)
		{
			show_lst(tokens);
			printf("%s\n", EXIT_TXT);
			free_list(tokens);
			free(input);
			exit(EXIT_FAILURE);
		}
		else if (ft_strncmp(aux->command, ECHO_TXT, 4) == 0)
			do_echo(aux->command);
		else if (ft_strcmp(aux->command, HSTRY_TXT) == 0)
			show_history();
		if (ft_strcmp(input, "") != 0)
			add_history(input);
		aux = aux->next;
	}
}
