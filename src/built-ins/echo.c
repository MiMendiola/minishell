/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:05 by mmendiol          #+#    #+#             */
/*   Updated: 2024/09/28 14:12:44 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_endl(char **command, int *counter)
{
	int	j;

	j = 0;
	if (!command || !command[*counter])
		return (FALSE);
	if (command[*counter][j] != '-' || command[*counter][j + 1] != 'n')
		return (FALSE);
	j = 2;
	while (command[*counter][j])
	{
		if (command[*counter][j] != 'n')
			return (FALSE);
		j++;
	}
	(*counter)++;
	return (TRUE);
}

void	do_echo(char *input)
{
	int		i;
	int		flag;
	char	**command;

	i = 1;
	flag = FALSE;
	command = command_spliter(input, ' ');
	while (command[i])
	{
		if (!skip_endl(command, &i))
			break ;
		flag = TRUE;
	}
	while (command[i])
	{
		if (*input != DQUOTES && *input != SQUOTES)
			ft_printf("%s", command[i++]);
		if (command[i])
			ft_printf(" ");
	}
	if (!flag)
		ft_printf("\n");
	free_matrix(command);
}
