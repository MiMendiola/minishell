/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:19:17 by anadal-g          #+#    #+#             */
/*   Updated: 2024/09/30 13:17:52 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char    *ft_strcpy(char *s1, char *s2)
//   {
//       int i;
 
//       i = 0;
//       while (s2[i])
//       {
//           s1[i] = s2[i]; // so this will make s1 = to whatever s2 is looping through the string
//           i++;
//       }
//       s1[i] = s2[i];  // now that we are finsihing looping though s1[i] will equal s2[i]
//       return (s1);
//   }

// char *get_env_value(char *name, t_env *envp)
// {
//     while (envp)
//     {
//         if (ft_strcmp(envp->name, name) == 0)
//             return (envp->value);
//         envp = envp->next;
//     }
//     return (NULL);
// }

// char *build_relative_path(const char *base_path, char *relative_path)
// {
//     size_t base_len;
//     size_t relative_len;
//     char *result;

//     if (!base_path || !relative_path)
//         return (NULL);
//     base_len = ft_strlen(base_path);
//     relative_len = ft_strlen(relative_path);
//     if (base_len == 0 || relative_len == 0)
//         return (NULL);
//     result = malloc(base_len + relative_len + 2); // +2 para '/' y '\0'
//     if (!result)
//         return (NULL);
//     ft_strcpy(result, base_path);
//     if (result[base_len - 1] != '/')
//         ft_strcat(result, "/");
//     ft_strcat(result, relative_path);
//     return (result);
// }

// int change_directory(const char *path)
// {
//     if (chdir(path) == -1)
//     {
//         perror("cd");
//         return (-1);
//     }
//     return (0);
// }

// //'cd' sin argumentos o 'cd -'
// int handle_special_cases(char **env, char **old, char **current, t_token *token)
// {
//     char *home;
//     char *actual_path;

//     home = get_env_value("HOME", token->envp);
//     if (!home)
//     {
//         ft_putstr_fd("Error: HOME no está configurada.\n", STDERR_FILENO);
//         return (-1);
//     }

//     if (!token->tokens[1] || !ft_strncmp(token->tokens[1], "--", 2))
//     {
//         if (chdir(home) == -1)
//             return (free(*old), free(*current), perror("cd"), -1);
//         *current = ft_strdup(home);
//     }
//     else if (!ft_strncmp(token->tokens[1], "-", 1))
//     {
//         actual_path = get_env_value("OLDPWD", token->envp);
//         if (actual_path && change_directory(actual_path) == 0)
//         {
//             ft_putstr_fd(actual_path, STDOUT_FILENO);
//             ft_putchar_fd('\n', STDOUT_FILENO);
//         }
//         else
//         {
//             ft_putstr_fd("Error: OLDPWD no está configurada.\n", STDERR_FILENO);
//             return (-1);
//         }
//     }
//     return (0);
// }

// int ft_cd(t_token *token, t_env *envp)
// {
//     char *cur_path;
//     char *old_path;
//     int result;
//     t_env *oldpwd_node;

//     old_path = getcwd(NULL, PATH_MAX);
//     if (!old_path)
//     {
//         perror("Error al obtener el directorio actual");
//         return (-1);
//     }
//     result = handle_special_cases(envp, &old_path, &cur_path, token);
//     if (result != 0)
//     {
//         free(old_path);
//         return (result);
//     }
//     if (change_directory(token->tokens[1]) == -1)
//     {
//         free(old_path);
//         return (-1);
//     }
//     oldpwd_node = ft_new_env("OLDPWD", old_path);
//     ft_set_env(&envp, oldpwd_node);
//     cur_path = getcwd(NULL, PATH_MAX);
//     if (cur_path)
//     {
//         t_env *pwd_node = ft_new_env("PWD", cur_path); 
//         ft_set_env(&envp, pwd_node);
//         free(cur_path);
//     }

//     free(old_path);
//     return (0);
// }

