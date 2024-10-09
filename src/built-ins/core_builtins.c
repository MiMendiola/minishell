/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:01:25 by mmendiol          #+#    #+#             */
/*   Updated: 2024/09/30 13:22:54 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	select_builtin(t_token **tokens, char *input)
{
	if (!input || ft_strcmp(input, EXIT_TXT) == 0)
	{
		show_lst(tokens);
		printf("%s\n", EXIT_TXT);
		free_list(tokens);
		free(input);
		exit(EXIT_FAILURE);
	}
	else if (ft_strncmp(input, ECHO_TXT, 4) == 0)
		do_echo(input);
	else if (ft_strcmp(input, HSTRY_TXT) == 0)
		show_history();
	else if (ft_strcmp(input, "") != 0)
		add_history(input);
	else if (ft_strcmp(input, PWD_TXT) == 0)
		ft_pwd();
	else if (ft_strcmp(input, ENV_TXT) == 0)
		ft_env(&input, NULL);
	// else if (ft_strcmp(input, CD_TXT) == 0)
	// 	ft_cd(*tokens, NULL);
}
