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

char **command_spliter2(char *input, char delimiter)
{
    char **result = malloc(10 * sizeof(char *));
    int i = 0;

    char *token = strtok(input, &delimiter);
    while (token != NULL)
    {
        result[i++] = token;
        token = strtok(NULL, &delimiter);
    }
    result[i] = NULL;
    return result;
}


void do_echo(char *input)
{
    char **command;
    int i = 0;
    int n_flag = 0;

    command = command_spliter2(input, ' ');
    if (command[i] && ft_strcmp(command[i], "echo") == 0)
        i++;
    while (command[i] && ft_strncmp(command[i], "-n", 2) == 0) 
    {
        const char *arg = command[i] + 2;
        int valid_n_flag = 1;
        while (*arg) 
        {
            if (*arg != 'n')
            {
                valid_n_flag = 0;
                break;
            }
            arg++;
        }
        if (valid_n_flag)
        {
            n_flag = 1;
            i++;
        } else
            break;
    }

    while (command[i]) 
    {
        printf("%s", command[i]);
        if (command[i + 1])
            printf(" ");
        i++;
    }

    if (!n_flag)
        printf("\n");
}

