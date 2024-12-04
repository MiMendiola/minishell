/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:55:47 by anadal-g          #+#    #+#             */
/*   Updated: 2024/12/03 12:00:32 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void heredoc(char *args[])
{
    int infile;
    char *line;
    char *delimiter;

    infile = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (infile == -1)
    {
        perror("Error al crear archivo temporal para heredoc");
        return;
    }
    delimiter = ft_strjoin(args[2], "\n");
    line = get_next_line(0);
    while (line != NULL && ft_strcmp(line, delimiter) != 0)
    {
        ft_putstr_fd(line, infile);
        free(line);
        line = get_next_line(0);
    }
    free(delimiter);
    if (line)
        free(line);
    close(infile);
}
