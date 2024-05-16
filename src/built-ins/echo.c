/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:05 by mmendiol          #+#    #+#             */
/*   Updated: 2024/05/15 19:23:49 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    input_printer(char *input)
{
    char    quote;
    
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

void    do_echo(char *input)
{
    
    if (ft_strncmp(input, "echo -n", 7) == 0)
    {
        input += 7;
        while (*input == 'n' || *input == ' ')
            input++;
        input_printer(input);
    }
    else if (ft_strncmp(input, "echo", 4) == 0)
    {
        input += 4;
        while (*input == ' ')
            input++;
        input_printer(input);
        printf("\n");
    }
}
