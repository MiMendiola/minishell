/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:11:17 by anadal-g          #+#    #+#             */
/*   Updated: 2024/05/09 17:44:12 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char    *findenv(char *name, char **envp)
{
    char    str;
    char    len;

    len = strlen(name);
    while (envp != NULL && name != NULL)
    {
        if (ft_strcncmp(envp, str, len))
            free(str);
            return ((envp + len));
    }
    return (NULL);
}



void    shlvl(void)
{
    t_token  *data;
    
    data = findenv("SHLVL", data->envp);
    if(data != NULL)
        set_shlvl(); //TODO
    else
        data = new_env();
    
}