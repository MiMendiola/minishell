/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:12 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/24 18:38:16 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "./defines.h"
# include "./structs.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	show_lst(t_token **stack);

/*===========================================*/
/*                BUILTINGS                  */
/*===========================================*/
//  CORE_BUILTINS.C
void	select_builtin(t_token **tokens, t_env **env, char *input);

//  ECHO.C
void	do_echo(char *input);

//	CD.C

//	PWD.D
void	do_pwd(void);

//	EXPORT.C
void	do_export(t_token *token, t_env **env);

//	UNSET.C
void	do_unset(t_token *token, t_env **env);

//	ENV.C
void	do_env(t_env *env);

//	EXIT.C
void	do_exit(t_token **tokens, char *input);

//  HISTORY.C
void	show_history(void);

/*===========================================*/
/*                   ENV                     */
/*===========================================*/
//  ENV_CREATOR.C
t_env	*ft_create_env_node(char *env_var);
void	ft_init_env(t_env **env_list, char **env);

//  ENV_UTILS.C
t_env	*ft_new_env(char *name, char *value);
void	ft_addback_env(t_env **lst, t_env *new);
t_env	*ft_find_env(t_env *env_list, char *name);
void	ft_del_env(t_env *env_node);

//  SHLVL.C
void	set_shell_lvl_aument(t_env **envp, t_env *data);
void	set_shell_lvl(t_env **envp);

/*===========================================*/
/*                   EXEC                    */
/*===========================================*/
//  REDIR.C
char	**redir_divisor(char const *s);

void	parse_redirections(t_token *token);

/*===========================================*/
/*               PARSING                     */
/*===========================================*/
//  QUOTE_HANDLER.C
void	quotes_check_in_token(char *token, int *in_quotes);
int		quotes_checker(t_token *token);
int		quotes_handler(t_token **token, char *input);
void	quotes_remover(char *input);
char	*quote_joiner(char **tokens);

//  QUOTE_PARSER.C
int		quote_equal(char c);
char	**quote_command_split(char *str);

//  COMMAND_LIST.C
void	add_node_tokens(t_token **stack_tokens, char **splited_tokens);
void	create_tokens(char *input, t_token **tokens);

//  ERRORS.C
void	show_error(char *str, char *cmd_file);
void	show_error_reverse(char *cmd_file, char *str);
void	perror_error(char *msg);

//  EXPANSOR.C
char	*get_variable_name(char **str);
void	append_expanded(char **result, size_t *result_len, char *var_name);
void	append_other_characters(char **result, size_t *result_len, char c);
char	*expand_variable(char *str);
void	expander(char **tokens);

//  FREES.C
void	free_list(t_token **stack);
void	free_tokens(t_token **tokens);
void	free_env(t_env **env);
void	free_iofile(t_iofile *iofile);

//  LEXER.C
void	lexerize_process(t_token *aux);
void	lexerize(t_token **tokens);

//  PARSING.C
void	jump_character(char *str, int *counter, char c, int flag);
void	read_till_character(char *str, int *start, int *counter, char c);
int		write_command(char **r, char *str, char c);
int		command_counter(char *str, char c);
char	**command_spliter(char const *s, char c);

//  TOKENIZER.C
int		write_token(char **r, char *str, char c);
int		token_counter(char *str, char c);
char	**tokenizer(char const *command);

//  UTILS_STACK.C
t_token	*last_node(t_token *lst);
void	add_node_back(t_token **stack, t_token *new);
t_token	*create_node(int id, char *command);

/*===========================================*/
/*                SIGNALS                    */
/*===========================================*/
//  SIGNALS.C
void	crtl_c(int sign);
void	signal_input(void);

#endif
