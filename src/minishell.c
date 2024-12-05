/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:15 by anadal-g          #+#    #+#             */
/*   Updated: 2024/12/05 11:58:51 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	show_lst(t_token **stack)
{
	t_token		*aux;
	int			i;
	t_iofile	*io_aux;

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
				printf("TOKEN[%d]	->	[%s]\n", i, aux->tokens[i]);
		}
		if (aux->infile)
		{
			io_aux = aux->infile;
			while (io_aux)
			{
				printf("INFILE		->	[%s] (TYPE: %d)\n", io_aux->name,
					io_aux->type);
				io_aux = io_aux->next;
			}
		}
		if (aux->outfile)
		{
			io_aux = aux->outfile;
			while (io_aux)
			{
				printf("OUTFILE		->	[%s] (TYPE: %d)\n", io_aux->name,
					io_aux->type);
				io_aux = io_aux->next;
			}
		}
		printf("PREV NODE	->	%p\n", aux->prev);
		printf("NEXT NODE	->	%p\n\n\n", aux->next);
		aux = aux->next;
	}
}

void	show_env_list(t_env **env_list)
{
	t_env	*current_node;

	current_node = *env_list;
	while (current_node != NULL)
	{
		printf("NODE ADDRESS  ->  %p\n", current_node);
		if (current_node->prev)
			printf("PREV NODE     ->  %p\n", current_node->prev);
		else
			printf("PREV NODE     ->  [None]\n");
		printf("ENV NAME      ->  %s\n", current_node->name);
		printf("ENV VALUE     ->  %s\n", current_node->value);
		if (current_node->next)
			printf("NEXT NODE     ->  %p\n\n", current_node->next);
		else
			printf("NEXT NODE     ->  [None]\n\n");
		current_node = current_node->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_token	**tokens;
	t_env	**env_list;
	char	*input;

	tokens = ft_calloc(1, sizeof(t_token *));
	env_list = ft_calloc(1, sizeof(t_env *));
	if (ac == 0 && av == NULL && env == NULL)
		printf("Hello");
	ft_init_env(env_list, env);
	// show_env_list(env_list);
	while (1)
	{
		input = readline(" 💻 $ ");
		free_tokens(tokens);
		create_tokens(input, tokens);
		if (!quotes_handler(tokens, input))
			continue ;
		lexerize(tokens);
		executor(*tokens, *env_list);
		//select_builtin(tokens, env_list, input);
		//show_lst(tokens);
		free(input);
	}
	free(tokens);
	return (0);
}
