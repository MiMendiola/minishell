/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:15 by anadal-g          #+#    #+#             */
/*   Updated: 2024/09/30 08:59:07 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	show_error(char *str, char *cmd_file)
{
	char	*msg;

	msg = ft_strjoin(str, cmd_file);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

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
			printf("PREV COMMAND[%d]	->	%s\n", aux->prev->id,
				aux->prev->command);
		printf("NODE COMMAND[%d]	->	%s\n", aux->id, aux->command);
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
		free_tokens(tokens);
		create_tokens(input, tokens);
		if (!quotes_handler(tokens, input))
			continue ;
		lexerize(tokens);
		select_builtin(tokens, input);
		show_lst(tokens);
		free(input);
	}
	free(tokens);
	return (0);
}
