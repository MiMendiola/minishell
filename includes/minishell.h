/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:12 by anadal-g          #+#    #+#             */
/*   Updated: 2024/07/30 16:43:58 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "./defines.h"
# include "./structs.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	show_lst(t_token **stack);

char	**tokenizer(char const *command);

void	lexerize(t_token **tokens);

/*
**  BUILT-INS
*/

//  CORE_BUILTINS.C
void	select_builtin(t_token **tokens, char *input);

//  ECHO.C
void	do_echo(char *input);

//  HISTORY.C
void	show_history(void);

/*
**  PARSING
*/

//  EXPANSOR.C
char	*get_env_value(char *var);
void	copy_env_name(char **src, char *dst);
void	expander(t_token *aux, char *str, int i);

//  PARSING.C
void	jump_character(char *str, int *counter, char c, int flag);
void	read_till_character(char *str, int *start, int *counter, char c);
int		write_command(char **r, char *str, char c);
int		command_counter(char *str, char c);
char	**command_spliter(char const *s, char c);


int	dollar_not_between_squotes(char *str);

//  TOKENIZER.C
void	add_node_tokens(t_token **stack, char **splited_tokens);
void	create_tokens(char *input, t_token **tokens);

//  UTILS_STACK.C
void	free_list(t_token **stack);
void	free_tokens(t_token **tokens);
t_token	*last_node(t_token *lst);
void	add_node_back(t_token **stack, t_token *new);
t_token	*create_node(int id, char *str);

#endif
