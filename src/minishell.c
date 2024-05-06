/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:15 by anadal-g          #+#    #+#             */
/*   Updated: 2024/05/06 17:05:37 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	show_lst(t_token **stack)
{
	t_token	*aux;

	aux = *stack;
	while (aux != NULL)
	{
		printf("STACK NODE	->	%p\n", *stack);
		printf("NODE		->	%p\n", aux);
		if (aux->prev)
			printf("PREV STR[%d]	->	%s\n", aux->prev->id, aux->prev->str);
		printf("STR NODE[%d]	->	%s\n", aux->id, aux->str);
		printf("PREV NODE	->	%p\n", aux->prev);
		printf("NEXT NODE	->	%p\n\n\n", aux->next);
		aux = aux->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_token	**tokens;
	char	*input;

	tokens = ft_calloc(1, sizeof(t_token *));
	if (ac == 0 && av == NULL && env == NULL)
		printf("Hello");
	while (1)
	{
		input = readline(" 💻 $ ");
		if (!input || ft_strcmp(input, EXIT_TXT) == 0)
		{
			show_lst(tokens);
			free_list(tokens);
			printf("%s\n", EXIT_TXT);
			free(input);
			exit(EXIT_FAILURE);
		}
		if (ft_strcmp(input, "") != 0)
			add_history(input);
		create_tokens(input, tokens);
		if (ft_strcmp(input, HSTRY_TXT) == 0)
			show_history();
		free(input);
	}
	return (0);
}
