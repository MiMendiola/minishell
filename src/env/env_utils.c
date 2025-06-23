/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:07:53 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/23 13:43:44 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char **env_to_array(t_env *env)
{
    int count = 0;
    t_env *tmp = env;
    char **env_array;
    char *var;
    
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    
    env_array = malloc(sizeof(char *) * (count + 1));
    if (!env_array)
        return (NULL);
    
    tmp = env;
    count = 0;
    while (tmp)
    {
        var = ft_strjoin(tmp->name, "=");
        if (!var)
        {
            free_matrix(env_array);
            return (NULL);
        }
        env_array[count] = ft_strjoin(var, tmp->value ? tmp->value : "");
        free(var);
        if (!env_array[count])
        {
            free_matrix(env_array);
            return (NULL);
        }
        count++;
        tmp = tmp->next;
    }
    env_array[count] = NULL;
    return (env_array);
}

t_env *ft_new_env(char *name, char *value)
{
    t_env *new_env;

    new_env = ft_calloc(1, sizeof(t_env));
    if (!new_env)
        return (NULL);
    
    new_env->name = ft_strdup(name);
    if (!new_env->name)
    {
        free(new_env);
        return (NULL);
    }
    
    if (value)
    {
        new_env->value = ft_strdup(value);
        if (!new_env->value)
        {
            free(new_env->name);
            free(new_env);
            return (NULL);
        }
    }
    else
        new_env->value = NULL;
    
    new_env->prev = NULL;
    new_env->next = NULL;
    new_env->last_out = 0;
    return (new_env);
}

void ft_addback_env(t_env **lst, t_env *new)
{
    t_env *mover;

    if (!lst || !new)
        return;
    
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

t_env *ft_find_env(t_env *env_list, char *name)
{
    t_env *token;

    if (!name)
        return (NULL);
    
    token = env_list;
    while (token != NULL)
    {
        if (ft_strcmp(token->name, name) == 0)
            return (token);
        token = token->next;
    }
    return (NULL);
}

void ft_del_env(t_env *env_node)
{
    if (!env_node)
        return;
    
    if (env_node->name)
        free(env_node->name);
    if (env_node->value)
        free(env_node->value);
    
    if (env_node->next)
        env_node->next->prev = env_node->prev;
    if (env_node->prev)
        env_node->prev->next = env_node->next;
    
    free(env_node);
}
