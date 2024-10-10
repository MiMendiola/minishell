/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:07:53 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/09 12:20:37 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_envfind(t_env *env_list, char *name)
{
	t_env	*token;

	token = env_list; // Apunta al inicio de la lista de entornos.
	while (token != NULL && name != NULL)
	{
		if (ft_strncmp(token->name, name, -1) == 0)
			// Compara los nombres de entorno.
			return (token);
		token = token->next;
	}
	return (NULL); // Devuelve NULL si no encuentra el entorno.
}

t_env	*ft_create_env_node(char *env_var)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(env_var, '=');
		// Buscar el signo '=' para separar la variable y el valor
	if (!equal_sign)
	{
		free(new_node);
		return (NULL); // No hay signo '=' en la cadena, formato inválido
	}
	new_node->name = ft_substr(env_var, 0, equal_sign - env_var);
		// Copiar el nombre de la variable
	new_node->value = ft_strdup(equal_sign + 1);                 
		// Copiar el valor de la variable (lo que viene después del '=')
	new_node->next = NULL;                                       
		// El siguiente nodo es NULL por defecto
	return (new_node);
}

void	ft_init_env(t_env **env_list, char **env)
{
	int		i;
	t_env	*new_env;

	i = 0;
	while (env[i])
	{
		new_env = ft_create_env_node(env[i]);
			// crea el nuyeuvo nodp para la variable de entorno
		ft_addback_env(env_list, new_env);
		i++;
	}
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
	if (env_node->args != NULL)
		free(env_node->args);
	if (env_node->next != NULL)
		env_node->next->last = env_node->last;
	if (env_node->last != NULL)
		env_node->last->next = env_node->next;
	free(env_node);
}

t_env	*ft_find_env(t_env *env_list, char *name)
{
	t_env	*token;

	token = env_list; // Apunta al inicio de la lista de entornos.
	while (token != NULL && name != NULL)
	{
		if (ft_strncmp(token->name, name, -1) == 0)
			// Compara los nombres de entorno.
			return (token);
		token = token->next;
	}
	return (NULL); // Devuelve NULL si no encuentra el entorno.
}
