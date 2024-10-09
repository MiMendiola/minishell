/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:15 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/09 12:43:42 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	show_lst(t_token **stack)
{
	t_token	*aux;
	int		i;

	aux = *stack;
	while (aux != NULL)
	{
		printf("STACK NODE	->	%p\n", *stack);
		printf("NODE		->	%p\n", aux);
		if (aux->prev)
			printf("PREV STR[%d]	->	%s\n", aux->prev->id,
				aux->prev->command);
		printf("STR NODE[%d]	->	%s\n", aux->id, aux->command);
		if (aux->tokens)
		{
			i = -1;
			while (aux->tokens[++i])
			{
				printf("TOKEN[%d]	->	[%s]\n", i, aux->tokens[i]);
			}
		}
		printf("PREV NODE	->	%p\n", aux->prev);
		printf("NEXT NODE	->	%p\n\n\n", aux->next);
		aux = aux->next;
	}
}


int	main(int ac, char **av, char **env)
{
	t_token	**tokens;
	t_env	*env_list;
	char	*input;

	env_list = NULL;
	tokens = ft_calloc(1, sizeof(t_token *));
	if (ac == 0 && av == NULL && env == NULL)
		printf("Hello");
	if (!tokens)
	{
		ft_putstr_fd("-----------------------.\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_init_env(&env_list, env);
	while (1)
	{	
		input = readline(" 💻 $ ");
		if (!input) 
		{
    	    ft_putstr_fd("Salida del shell\n", STDERR_FILENO);
    	    break ; 
        }
		if (*input)
		{
			set_shell_lvl(&env_list);
			parse_command(input, tokens, env_list);
			if (!tokens || !*tokens)
			{                
				printf("Tokens no fueron inicializados o procesados en parse_command.\n");
				break ;
			}
			select_builtin(tokens, input);
			//show_lst(tokens);
		}
		free_tokens(tokens);
		free(input);
        input = NULL;
	}
	free_tokens(tokens);
	free_env_list(env_list);
	free(input);
	return (0);
}
