/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:11:15 by anadal-g          #+#    #+#             */
/*   Updated: 2024/05/01 18:11:16 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int ac, char **av, char **env)
{
    char *input;

    if (ac == 0 && av == NULL && env == NULL)
        printf("Hello");
    
    while (1)
    {
        input = readline("Ingrese algo: ");
        
        if (!input)
            break;

        if (strcmp(input, "exit") == 0)
            exit(EXIT_FAILURE);

        add_history(input);

        printf("Usted escribió: '%s'\n", input);

        free(input);
    }
    return (0);
}