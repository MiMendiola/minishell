/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:31:11 by anadal-g          #+#    #+#             */
/*   Updated: 2024/05/28 12:38:40 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	input_printer_prueba(char *input)
{
	char	quote;

	while (*input)
	{
		if (*input == DQUOTES || *input == SQUOTES)
		{
			quote = *input;
			input++;
			while (!character_finder(*input, quote))
			{
				printf("%c", *input);
				input++;
			}
		}
		if (*input != DQUOTES && *input != SQUOTES)
			printf("%c", *input);
		input++;
	}
}

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
		    printf("%s", command[i++]);
		if (command[i])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	free_matrix(command);
}
