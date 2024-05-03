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

void    show_history()
{
    HIST_ENTRY **history;
    int        width;

    width = 6;
    history = history_list();
    if (history)
    {
        int j = -1;
        while (history[++j])
            printf("%*d  %s\n", width, j + history_base, history[j]->line);
    }
}

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
        if (ft_strcmp(input, "") != 0)
            add_history(input);

        printf("You write: '%s'\n", input);
        if (ft_strcmp(input, "history") == 0)
            show_history();
        
        free(input);
    }
    return (0);
}