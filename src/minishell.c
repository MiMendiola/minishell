/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:15 by anadal-g          #+#    #+#             */
/*   Updated: 2024/05/11 21:12:56 by mmendiol         ###   ########.fr       */
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
	char	*input;

	tokens = ft_calloc(1, sizeof(t_token *));
	if (ac == 0 && av == NULL && env == NULL)
		printf("Hello");
	while (1)
	{
		input = readline(" 💻 $ ");
		select_builtin(tokens, input);
		create_tokens(input, tokens);
		
		// char	**pipe;
		// int		x;
		// pipe = pipe_spliter(input);
		// x = -1;
		// while (pipe[++x])
		// 	printf("\t@ %d: [%s]\n", x, pipe[x]);
		free(input);
	}
	return (0);
}
