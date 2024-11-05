/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:01:25 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/29 12:11:16 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	select_builtin(t_token **tokens, t_env **env, char *input)
{
	t_token	*aux;

	aux = *tokens;
	if (!tokens || !*tokens)
		return ;
	while (aux)
	{
		printf("HOLA %s\n", aux->command);
		if (ft_strcmp(aux->command, EXIT_TXT) == 0)
			do_exit(tokens, input);
		else if (ft_strncmp(aux->command, ECHO_TXT, 4) == 0)
			do_echo(aux->command);
		else if (ft_strcmp(aux->tokens[0], CD_TXT) == 0)
		 	do_cd(aux, *env);
		else if (ft_strcmp(input, PWD_TXT) == 0)
			do_pwd();
		else if (ft_strcmp(input, EXPORT_TXT) == 0)
			do_export(aux, env);
		else if (ft_strncmp(aux->command, UNSET_TXT, 5) == 0)
		 	do_unset(*tokens, env);
		else if (ft_strncmp(aux->command, ENV_TXT, 3) == 0)
		 	do_env(*env);
		else if (ft_strcmp(aux->command, HSTRY_TXT) == 0)
			show_history();
		if (ft_strcmp(input, "") != 0)
			add_history(input);
		aux = aux->next;
	}
}
