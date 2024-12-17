/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:55:47 by anadal-g          #+#    #+#             */
/*   Updated: 2024/12/17 12:47:09 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int read_heredoc_input(int infile, char *delimiter_input)
{
    char *line;
    char *delimiter;

    delimiter = ft_strjoin(delimiter_input, "\n");
    if (!delimiter)
    {
        perror("Error al asignar delimitador");
        return 0;
    }
    line = get_next_line(0);
    while (line && ft_strcmp(line, delimiter) != 0)
    {
        ft_putstr_fd(line, infile);
        free(line);
        line = get_next_line(0);
    }
    free(delimiter);
    if (line)
        free(line);
    return 1;
}
char *heredoc(char *args[])
{
    int infile;
    char *tmp_file = TMP_FILE;

    infile = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (infile == -1)
    {
        perror("Error al crear archivo temporal para heredoc");
        return NULL;
    }
    if (!read_heredoc_input(infile, args[2]))
    {
        close(infile);
        return NULL;
    }
    close(infile);
    return tmp_file;
}

// char *heredoc(char *args[])
// {
//     int infile;
//     char *line;
//     char *delimiter;
//     char *tmp_file = TMP_FILE;

//     infile = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (infile == -1)
//     {
//         perror("Error al crear archivo temporal para heredoc");
//         return NULL;
//     }
//     delimiter = ft_strjoin(args[2], "\n");
//     if (!delimiter) {
//         perror("Error al asignar delimitador");
//         close(infile);
//         return NULL;
//     }
//     line = get_next_line(0);
//     while (line != NULL && ft_strcmp(line, delimiter) != 0) {
//         ft_putstr_fd(line, infile);
//         free(line);
//         line = get_next_line(0);
//     }
//     free(delimiter);
//     if (line)
//         free(line);
//     close(infile);
//     return tmp_file;
// }

