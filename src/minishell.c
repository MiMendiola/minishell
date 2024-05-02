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

// void	ft_leaks(void)
// {
// 	system("leaks -q pipex");
// }
// atexit(ft_leaks);

int main(int ac, char **av, char **env)
{
    char *input;

    if (ac == 0 && av == NULL && env == NULL)
        printf("Hello");
    
    while (1)
    {
        input = readline("");
        
        if (!input)
            break;

        if (ft_strcmp(input, "exit") == 0)
        {
            printf("exit\n");
            exit(EXIT_FAILURE);
        }

        add_history(input);

        printf("You write: '%s'\n", input);

        free(input);
    }
    return (0);
}