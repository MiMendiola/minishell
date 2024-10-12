/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:07:53 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/12 07:15:56 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env   *ft_new_env(char *name, char *value)
{
    t_env   *new_env;
    
    new_env = ft_calloc(1, sizeof(t_env));
    if (new_env == 0)
        return (NULL);
    new_env->name = ft_strdup(name); 
    if (new_env->name ==  NULL)
    {
        free(new_env);
        return (NULL);
    }
    if (value != NULL)
        new_env->sh_lvl = ft_strdup(value);
    else
        new_env->sh_lvl = NULL;
    if (value != NULL && new_env->sh_lvl == NULL)
    {
        free(new_env->name);
        free(new_env);
        return (NULL);
    }
    new_env->prev = NULL;
    new_env->next = NULL;
    return (new_env);
}

void ft_addback_env(t_env **lst, t_env *new)
{
    t_env *mover;

    if (*lst == NULL)
    {
        *lst = new;
        return;
    }
    mover = *lst;
    while (mover->next != NULL)
        mover = mover->next;
    new->prev = mover;
    mover->next = new;
}

t_env	*ft_find_env(t_env *env_list, char *name)
{
	t_env	*token;

	token = env_list;
	while (token != NULL && name != NULL)
	{
		if (ft_strncmp(token->name, name, -1) == 0)
			return (token);
		token = token->next;
	}
	return (NULL);
}

void	ft_del_env(t_env *env_node)
{
	if (!env_node)
	{	
		printf("Error: Variable de entorno no inicializada\n");
		return ;
	}
	if (env_node->name != NULL)
		free(env_node->name);
	if (env_node->sh_lvl != NULL)
		free(env_node->sh_lvl);
	if (env_node->next != NULL)
		env_node->next->prev = env_node->prev;
	if (env_node->prev != NULL)
		env_node->prev->next = env_node->next;
	free(env_node);
}

void  ft_unset_env(t_env **envp, t_env *token)
{
    t_env *result;
    t_env *next;

    result = ft_find_env(*envp, token->name);
    if (result == NULL)
        return;
    if (result == *envp)
    {
        next = (*envp)->next;
        ft_del_env(result);
        *envp = next;
    }
    else
        ft_del_env(result);
}
