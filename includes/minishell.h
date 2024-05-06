/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:12 by anadal-g          #+#    #+#             */
/*   Updated: 2024/05/06 17:58:10 by mmendiol         ###   ########.fr       */
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

/*===========================================*/
/*                TOKENIZER.C                */
/*===========================================*/
void	add_node_tokens(t_token **stack, char **splited_tokens);
void	create_tokens(char *input, t_token **tokens);

/*===========================================*/
/*               UTILS_STACK.C               */
/*===========================================*/
void	free_list(t_token **stack);
t_token	*last_node(t_token *lst);
void	add_node_back(t_token **stack, t_token *new);
t_token	*create_node(int id, char *str);

/*===========================================*/
/*                 HISTORY.C                 */
/*===========================================*/
void	show_history(void);

#endif