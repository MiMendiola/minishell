/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:58:03 by anadal-g          #+#    #+#             */
/*   Updated: 2024/08/05 17:18:41 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_env(char	**args, t_env *env)
{
	if (args[1])
	{	
		printf("No such file or directory\n");
		return ;
	}
	while (env)
	{
		if (env->value && ft_strcmp(env-> value, ""))
		{
			printf("%s", env->name);
			printf("=");
			printf("%s", env->value);
		}
		env = env->next;
	}
}
