/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:15:04 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/08 12:15:45 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Elimina uuna variable de la lista
void  ft_unset_env(t_env **envp, t_env *token)
{
    t_env *result;
    t_env *next;

    result = ft_find_env(*envp, token->name);  // Busca la variable con el nombre de token
    if (result == NULL)
        return;
    if (result == *envp)  // Si la variable a eliminar es la primera de la lista
    {
        next = (*envp)->next;
        ft_del_env(result);  // Elimina el nodo
        *envp = next;  // Actualiza el primer nodo
    }
    else
        ft_del_env(result);  // Si no es la primera, simplemente elimina el nodo
}

//Añade una nueva variable al final de la lista
void ft_addback_env(t_env **lst, t_env *new)
{
    t_env *mover;

    if (*lst == NULL)  // Si la lista está vacía, añadimos el nuevo nodo como el primero
    {
        *lst = new;
        return;
    }
    mover = *lst;
    while (mover->next != NULL)  // Recorremos hasta el último nodo
        mover = mover->next;
    mover->next = new;  // Añadimos el nuevo nodo al final
    new->last = mover;  // Actualizamos el puntero 'last'
}

void    ft_set_env(t_env **envp ,t_env *token)
{
    ft_unset_env(envp,token);
    ft_addback_env(envp, token);
}

t_env   *ft_new_env(char *name, char *args)
{
    t_env   *new_env;
    
    new_env = (t_env *)malloc(sizeof(t_env));
    if (new_env == 0)
        return (NULL);
    new_env->name = ft_strdup(name); 
    if (new_env->name ==  NULL)
    {
        free(new_env);
        return (NULL);
    }
    if (args != NULL) //Si no es null copia el contenido de args
        new_env->args = ft_strdup(args);
    else //Si es null se dea como null
        new_env->args = NULL;
    if (args != NULL && new_env->args == NULL) //Se copia el valor y si falla se liberan memorias
    {
        free(new_env->name);
        free(new_env);
        return (NULL);
    }
    new_env->next = NULL;
    new_env->last = NULL;
    return (new_env);
}
