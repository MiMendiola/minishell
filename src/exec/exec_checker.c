/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:58:56 by mmendiol          #+#    #+#             */
/*   Updated: 2024/10/29 09:47:07 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_path(char **flags_cmd, t_env *env_path)
{
	char	**path;
	char	*command;
	char	*aux;
	int		i;

	i = 0;
	if (!env_path)
		return (flags_cmd[0]);
	path = ft_split(env_path->value, ':');
	while (path[i])
	{
		aux = ft_strjoin(path[i++], "/");
		command = ft_strjoin(aux, flags_cmd[0]);
		free(aux);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
	}
	free_matrix(path);
	return (flags_cmd[0]);
}

/*int	exec_checker(char *argument, t_env **env)
{
	char	**flags_cmd;
	char	*command;
	t_env 	*env_aux;

	env_aux = ft_find_env(*env, "PATH");
	flags_cmd = ft_split(argument, ' ');
	if (!flags_cmd[0])
		show_error(COMMAND_NOT_FOUND, argument);
	if (ft_strchr(flags_cmd[0], '/'))
		command = flags_cmd[0];
	else
		command = check_path(flags_cmd, env_aux);
	if (access(command, F_OK | X_OK) == 0)
		execve(command, flags_cmd, enviroment);
	else
		show_error(COMMAND_NOT_FOUND, argument);
	free_matrix(flags_cmd);
	return (-1);
}*/
