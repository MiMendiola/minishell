/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:05 by mmendiol          #+#    #+#             */
/*   Updated: 2024/05/23 19:56:24 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void    input_printer(char *input)
// {
//     char    quote;
    
//     while (*input)
//     {
//         if (*input == DQUOTES || *input == SQUOTES)
//         {
//             quote = *input;
//             input++;
//             while (!character_finder(*input, quote))
//             {
//                 printf("%c", *input);
//                 input++;
//             }
//         }
//         if (*input != DQUOTES && *input != SQUOTES)
//             printf("%c", *input);
//         input++;
//     }
// }

// void    do_echo(char *input)
// {
//     char *last = ft_strrchr(input, '-');
//     if (ft_strncmp(input, ECHO_TXT, 4) == 0)
//     {
//         input += 4;
//         while (*input == ' ')
//             input++;
//         if (ft_strncmp(input, "-n", 2) == 0)
//         {
//             input += 2;
//             while (*input == '-' || *input == 'n' || *input == ' ')
//             {
//                 input++;
//                 if (*input != '-' && *input != 'n' && *input != ' ')
//                 {
//                     if (*(input - 1) == 'n')
//                         input_printer(last);
//                     else
//                         input_printer(input);
//                     return;  
//                 }
//             }
//         }
//         else
//         {
//             input_printer(input);
//             printf("\n");
//         }
//     }
// }






void    input_printer_prueba(char *input)
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
    char    **command;
    char    quote;
    
    command = command_spliter(input, ' ');
    int i = 1;
    int j = 0;

    // while (command[i])
    //     printf("[%s]\n", command[i++]);
    
        if (command[i] == "-n")
        {
            i++;
            while (command[i][j] == '-' || command[i][j] == 'n' || command[i][j] == ' ')
            {
                j++;
                if (command[i][j] != '-' && command[i][j] != 'n' && command[i][j] != ' ')
                {
                    if (command[i][j - 1] == 'n')
                    {
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
                    else
                    {
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
                    return;  
                }
            }
        }
        else
        {
            j = 0;
            while (command[i][j])
            {
                if (command[i][j] == DQUOTES || command[i][j] == SQUOTES)
                {
                    quote = command[i][j];
                    input++;
                    while (!character_finder(command[i][j], quote))
                    {
                        printf("%c", command[i][j]);
                        input++;
                    }
                }
                if (command[i][j] != DQUOTES && command[i][j] != SQUOTES)
                    printf("%c", command[i][j]);
                j++;
            }
            printf("\n");
            return;
        }
        i++;
}
