/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:58:03 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/13 05:22:43 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_env(t_env *env)
{
	while (env)
	{
		if (env->value && ft_strcmp(env-> value, ""))
		{
			printf("%s", env->name);
			printf("=");
			printf("%s\n", env->value);
		}
		env = env->next;
	}
}
