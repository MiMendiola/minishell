/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:15:04 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/12 07:24:11 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_create_env_node(char *env_var)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(env_var, '=');
	if (!equal_sign)
	{
		free(new_node);
		return (NULL);
	}
	new_node->name = ft_substr(env_var, 0, equal_sign - env_var);
	new_node->value = ft_strdup(equal_sign + 1);
    new_node->sh_lvl = NULL;                
	new_node->prev = NULL;                                      
	new_node->next = NULL;                                      
	return (new_node);
}

void	  ft_init_env(t_env **env_list, char **env)
{
	int		i;
	t_env	*new_env;

	i = 0;
	while (env && env[i])
	{
		new_env = ft_create_env_node(env[i]);
		ft_addback_env(env_list, new_env);
		i++;
	}
    //if (!env || !env[i])
        //TODO - crear del enviroment el PWD, SHLVL y _=/usr/...
}
