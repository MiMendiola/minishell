/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:59:23 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/28 16:08:59 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}


void exit_malloc(void)
{
    perror("malloc error");
    exit(EXIT_FAILURE);
}


char	*get_variable(char *arguments)
{
    int		i = 0;
    char	*variable;

    while (arguments[i] && arguments[i] != '=')
        i++;
    variable = malloc(i + 1);
    if (!variable)
        exit(EXIT_FAILURE);
    ft_strncpy(variable, arguments, i);
    variable[i] = '\0';
    return (variable);
}

char	*get_content(char *arguments)
{
    char	*equal_sign = ft_strchr(arguments, '=');
    if (equal_sign)
        return (ft_strdup(equal_sign + 1));
    return (ft_strdup(""));
}


int	check_if_variable_ok(char *argument)
{
    int	i = 0;

    if (ft_isalpha(argument[i]) || argument[i] == '_')
    {
        i++;
        while (argument[i] && (ft_isalnum(argument[i]) || argument[i] == '_'))
            i++;
        if (argument[i] == '=')
            return (1);
    }
    return (0);
}



void	manage_export(t_token *token, t_env *envp)
{
    int		i = 1;  // Comenzar en tokens[1] porque tokens[0] es "export"
    char	*variable;
    char	*content;

    while (token->tokens[i])
    {
        if (check_if_variable_ok(token->tokens[i]))  // Validar variable
        {
            variable = get_variable(token->tokens[i]);
            content = get_content(token->tokens[i]);
            if (check_if_variable_ok(variable))
                replace_content(envp, variable, content);  // Si existe, reemplazar
            else
                add_to_env(&envp, variable, content);  // Si no, añadir
            free(variable);
            free(content);
        }
        else
        {
            ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
            break;
        }
        i++;
    }
}


void	replace_content(t_env *envp, char *variable, char *content)
{
    t_env	*current = envp;

    while (current != NULL)
    {
        if (!ft_strcmp(current->name, variable))
        {
            free(current->value);
            current->value = strdup(content);
            return;
        }
        current = current->next;
    }
}


void	add_to_env(t_env **envp, char *variable, char *content)
{
    t_env	*new_var;

    new_var = malloc(sizeof(t_env));
    if (!new_var)
        exit_malloc();
    
    new_var->name = strdup(variable);
    new_var->value = strdup(content);
    new_var->next = NULL;
    new_var->prev = NULL;
    if (*envp == NULL)
        *envp = new_var;
    else
    {
        t_env *current = *envp;
        while (current->next != NULL)
            current = current->next;
        current->next = new_var;
        new_var->prev = current;
    }
}


static char	**order_alf_envp(t_env *envp)
{
    t_env	*current = envp;
    char	**ordered_env;
    int		count = 0;
    int		i = 0;

    while (current)
    {
        count++;
        current = current->next;
    }

    ordered_env = malloc((count + 1) * sizeof(char *));
    if (!ordered_env)
        exit_malloc();

    current = envp;
    while (current)
    {
        ordered_env[i] = ft_strdup(current->name);
        i++;
        current = current->next;
    }
    ordered_env[i] = NULL;
    return (order_alf_envp2(ordered_env));  // Ordenar alfabéticamente
}

char	**order_alf_envp2(char **new_envp)
{
    char	*aux;
    int		i = 0;
    int		j;

    while (new_envp[i])
    {
        j = i + 1;
        while (new_envp[j])
        {
            if (ft_strcmp(new_envp[i], new_envp[j]) > 0)
            {
                aux = new_envp[i];
                new_envp[i] = new_envp[j];
                new_envp[j] = aux;
            }
            j++;
        }
        i++;
    }
    return (new_envp);
}


void	export_alone(t_env *envp)
{
    char	**ordered_env;
    int		i;

    ordered_env = order_alf_envp(envp);
    if (!ordered_env)
        exit_malloc();
    i = 0;
    while (ordered_env[i])
    {
        printf("declare -x %s\n", ordered_env[i]);
        i++;
    }
    free(ordered_env);
}


void	do_export(t_token *token, t_env **env)
{
    if (!token->tokens[1])
        export_alone(*env);
    else
        manage_export(token, *env);
}
