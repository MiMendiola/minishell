/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:59:23 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/13 09:43:56 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO-ESTO HAY QUE MODIFICARLO PORQUE NO ESTA BIEN, COPIA DE DO_UNSET PERO PARECIDO
void	do_export(t_token *token, t_env **env)
{
	int i;
    t_env *result;
    t_env *next;

    i = 1;
    while (token->tokens[i])
    {
        result = ft_find_env(*env, token->tokens[i++]);
        if (result == NULL)
            return;
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
