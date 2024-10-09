/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:12 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/09 11:54:41 by anadal-g         ###   ########.fr       */
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
# include <limits.h>

void	show_lst(t_token **stack);

char	**tokenizer(char const *command);
void	ft_init_env(t_env **env_list, char **env);



/*===========================================*/
/*                BUILTINGS.C                 */
/*===========================================*/

//  CORE_BUILTINS.C
void	select_builtin(t_token **tokens, char *input);

//  ECHO.C
void	do_echo(char *input);

//  HISTORY.C
void	show_history(void);

//	PWD.D
void	ft_pwd(void);

//	ENV.C
void	ft_env(char	**args, t_env *env);

//	CD.C
int ft_cd(t_token *token, t_env *envp);


/*===========================================*/
/*               PARSING.C                   */
/*===========================================*/
void	jump_character(char *str, int *counter, char c, int flag);
void	read_till_character(char *str, int *start, int *counter, char c);
//int		write_command(char **r, char *str, char c);
int		command_counter(char *str, char c);
char	**command_spliter(char const *s, char c);
void	parse_command(char *input, t_token **tokens, t_env *envp);
void	prepare_command(char **input, t_env *envp, t_token *tokens);
void 	divide_tokens(char *input, t_token **token_list);
int		ft_isspace(int c);


/*===========================================*/
/*              TOKENIZER                 */
/*===========================================*/
void	add_node_tokens(t_token **stack, char **splited_tokens);
void	create_tokens(char *input, t_token **tokens);
int	validate_tokens(t_token *tokens);
t_token	*create_node_operator(char *operator);



/*===========================================*/
/*               UTILS_STACK.C               */
/*===========================================*/
void	free_list(t_token **stack);
t_token	*last_node(t_token *lst);
void	add_node_back(t_token **stack, t_token *new);
char	**create_node(int id, char *str);


/*===========================================*/
/*                SIGNALS.C                  */
/*===========================================*/
void    crtl_c(int  sign);
void    signal_input(void);

/*===========================================*/
/*                SIGNALS.C                  */
/*===========================================*/

void do_echo(char *input);
char **command_spliter2(char *input, char delimiter);

/*===========================================*/
/*                SHLVl.C Y ENV.C            */
/*===========================================*/

void    ft_del_env(t_env *env_node);
t_env *ft_find_env(t_env *env_list, char *name);
void  ft_unset_env(t_env **envp, t_env *token);
void ft_addback_env(t_env **lst, t_env *new);
void    ft_set_env(t_env **envp ,t_env *token);
t_env   *ft_new_env(char *name, char *args);
void set_shell_lvl_aument(t_env **envp, t_env *data);
void set_shell_lvl(t_env **envp);


/*===========================================*/
/*               ERRORS.C         */
/*===========================================*/

void	perror_error(char *msg);

/*===========================================*/
/*                EXPANDER.C                 */
/*===========================================*/

void	expander(t_token *aux, char *str, int i);
void 	expand_variables(char **tmp_str, char **str, char **found, char *env_name);
int		dollar_not_between_squotes(char *str);
char	*found_dollar_not_squotes(char *str);
void	*ft_realloc(void *ptr, size_t original_size, size_t new_size);
char	 *ft_strcat(char *dest, const char *src);

/*===========================================*/
/*               FREE.C        				 */
/*===========================================*/

void free_env_list(t_env *env_list);
void free_tokens(t_token **tokens);

/*===========================================*/
/*               FREE.C        				 */
/*===========================================*/

void	reorder_and_verify(t_token **tokens);
int	validate_syntax(t_token *tokens);
int	is_operator(t_token *token);

#endif
