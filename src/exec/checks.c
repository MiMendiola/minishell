/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:43:49 by anadal-g          #+#    #+#             */
/*   Updated: 2024/11/25 12:49:15 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_envp(char **envp, char **flags_cmd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	show_error(COMMAND, flags_cmd[0]);
	exit(EXIT_FAILURE);
}

// char	*check_path(char **flags_cmd, char **enviroment)
// {
// 	char	**path;
// 	char	*command;
// 	char	*aux;
// 	int		i;

// 	i = check_envp(enviroment, flags_cmd);
// 	path = ft_split(enviroment[i] + 5, ':');
// 	i = 0;
// 	while (path[i])
// 	{
// 		aux = ft_strjoin(path[i++], "/");
// 		command = ft_strjoin(aux, flags_cmd[0]);
// 		if (!command)
// 			show_error(COMMAND, command);
// 		free(aux);
// 		if (access(command, F_OK | X_OK) == 0)
// 			return (command);
// 		free(command);
// 	}
// 	free_matrix(path);
// 	return (NULL);
// }

int check_access(char *argument, t_env *env_path)
{
    char    **flags_cmd;
    char    *command;

    flags_cmd = ft_split(argument, ' ');
    if (!flags_cmd[0])
        show_error(COMMAND, argument);
    if (ft_strchr(flags_cmd[0], '/'))
        command = flags_cmd[0];
    else
        command = check_path(flags_cmd, env_path);
    
    if (access(command, F_OK | X_OK) == 0)
        execve(command, flags_cmd, env_to_array(env_path));
    else
        show_error(COMMAND, argument);

    free_matrix(flags_cmd);
    return (-1);
}
