/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:09:32 by anadal-g          #+#    #+#             */
/*   Updated: 2024/12/09 12:10:37 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	perror_error("Error en el envp");
	exit(EXIT_FAILURE);
}

char	*find_path(char *command, char **envp)
{
	int		i;
	int		env;
	char	**paths;
	char	*path;
	char	*part_path;

	/* NOTE
		- Si el comando tiene una barra --> es una ruta absoluta o relativa
		- SI no hay barra --> buscamos en PATH
	*/
	if (ft_strchr(command, '/'))
		return (command);
	env = check_envp(envp);
	paths = ft_split(envp[env] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, command);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}
