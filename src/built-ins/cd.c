/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:19:17 by anadal-g          #+#    #+#             */
/*   Updated: 2024/11/05 11:51:21 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	go_home(t_env **envp)
{
	char	*old_path;
	char	*home;
	char	*cur_path;

	old_path = getcwd(NULL, PATH_MAX);
	home = ft_find_env(*envp, "HOME")->value;
	if (home == NULL)
		return (perror("minishell: cd: HOME not set"), 1);
	if (chdir(home) == -1)
		return (perror(home), 1);
	ft_set_env(envp, ft_new_env("OLDPWD", old_path));
	cur_path = getcwd(NULL, PATH_MAX);
	if (cur_path == NULL)
		return (perror_error("getcwd() error"), 1);
	ft_set_env(envp, ft_new_env("PWD", cur_path));
	free(old_path);
	free(cur_path);
	return (0);
}

int	go_old(t_env **envp)
{
	char	*old_path;
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_find_env(*envp, "OLDPWD")->value;
	if (oldpwd == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(oldpwd) == -1)
	{
		perror_error(oldpwd);
		return (1);
	}
	old_path = getcwd(NULL, PATH_MAX);
	if (old_path == NULL)
	{
		perror_error("getcwd() error");
		return (1);
	}
	pwd = ft_find_env(*envp, "PWD")->value;
	ft_set_env(envp, ft_new_env("OLDPWD", pwd));
	ft_set_env(envp, ft_new_env("PWD", old_path));
	free(old_path);
	return (0);
}

int	go_to_directory(char *path, t_env **envp, char *cwd)
{
	char	*cur_path;

	if (chdir(path) == -1)
	{
		perror_error(path);
		return (1);
	}
	ft_set_env(envp, ft_new_env("OLDPWD", cwd));
	cur_path = getcwd(NULL, PATH_MAX);
	if (cur_path == NULL)
	{
		perror_error("getcwd() error");
		return (1);
	}
	ft_set_env(envp, ft_new_env("PWD", cur_path));
	free(cur_path);
	return (0);
}

int	handle_cd_path(t_token *token, t_env **envp, char *cwd)
{
	if (token->tokens[1] == NULL || ft_strcmp(token->tokens[1], "~") == 0
		|| ft_strcmp(token->tokens[1], "--") == 0)
		return (go_home(envp));
	else if (ft_strcmp(token->tokens[1], "-") == 0)
		return (go_old(envp));
	else
		return (go_to_directory(token->tokens[1], envp, cwd));
}


int	do_cd(t_token *token, t_env *envp)
{
	char	*cwd;
	int		result;

	cwd = getcwd(NULL, PATH_MAX);
	if (!cwd)
	{
		perror_error("getcwd() error");
		return (1);
	}
	if (ft_find_env(envp, "OLDPWD") == NULL)
		ft_set_env(&envp, ft_new_env("OLDPWD", cwd));
	result = handle_cd_path(token, &envp, cwd);
	free(cwd);
	return result;
}
