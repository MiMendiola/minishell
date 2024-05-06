/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:15 by anadal-g          #+#    #+#             */
/*   Updated: 2024/05/06 15:22:56 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list(t_token **stack)
{
	t_token	*aux;

	while (*stack)
	{
		aux = (*stack)->next;
		free((*stack)->str);
		free(*stack);
		*stack = aux;
	}
	free(stack);
}

t_token	*last_node(t_token *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_node_back(t_token **stack, t_token *new)
{
	t_token	*aux;

	aux = last_node(*stack);
	if (*stack != NULL)
	{
		new->prev = aux;
		new->next = NULL;
		aux->next = new;
	}
	else
		*stack = new;
}

t_token	*create_node(int id, char *str)
{
	t_token	*tokens;

	tokens = ft_calloc(1, sizeof(t_token));
	if (!tokens)
		return (NULL);
	tokens->id = id;
	tokens->str = str;
	tokens->prev = NULL;
	tokens->next = NULL;
	return (tokens);
}

void	add_node_tokens(t_token **stack, char **splited_tokens)
{
	int		i;
	t_token	*node;
	t_token	*node_last;

	i = -1;
	while (splited_tokens[++i])
	{
		if (!*stack)
			node = create_node(1, splited_tokens[i]);
		else
		{
			node_last = last_node(*stack);
			node = create_node(node_last->id + 1, splited_tokens[i]);
		}
		add_node_back(stack, node);
	}
}

void	create_tokens(char *input, t_token **tokens)
{
	int		i;
	char	**tokens_splited;

	i = 0;
	if (input != NULL)
	{
		tokens_splited = ft_split(input, '|');
		add_node_tokens(tokens, tokens_splited);
		free(tokens_splited);
	}
	else
		ft_putstr_fd("Error\n", STDERR_FILENO);
}

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

void	show_history(void)
{
	HIST_ENTRY	**history;
	int			width;
	int			i;

	width = 6;
	history = history_list();
	if (history)
	{
		i = -1;
		while (history[++i])
			printf("%*d  %s\n", width, i + history_base, history[i]->line);
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
