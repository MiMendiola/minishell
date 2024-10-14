/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:01:25 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/13 10:15:57 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void  do_unset(t_token *token, t_env **env)
{
    int i;
    t_env *result;
    t_env *next;

    i = 1;
    if (!token->tokens[i] && ft_strcmp(token->tokens[0], UNSET_TXT) != 0)
        show_error_reverse(token->tokens[0], COMMAND_NOT_FOUND_REVERSE);
    while (token->tokens[i])
    {
        result = ft_find_env(*env, token->tokens[i++]);
        if (result == NULL)
            return ;
        if (result == *env)
        {
            next = (*env)->next;
            ft_del_env(result);
            *env = next;
        }
        else
            ft_del_env(result);
    }  
}
