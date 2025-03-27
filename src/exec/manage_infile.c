/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_infile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:24:36 by anadal-g          #+#    #+#             */
/*   Updated: 2025/03/27 11:56:26 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_heredoc_infile(t_iofile *infile, int *error)
{
	int		fd;
	char	*name;

	name = heredoc(infile->name);
	if (!name)
	{
		perror_error("Error al procesar heredoc");
		exit(EXIT_FAILURE);
	}
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror_error(name);
		*error = 1;
	}
	free(name);
	return (fd);
}

static int	open_normal_infile(t_iofile *infile, int *error)
{
	int	fd;

	fd = open(infile->name, O_RDONLY);
	if (fd < 0)
	{
		perror_error(infile->name);
		*error = 1;
	}
	return (fd);
}

int	aux_open_infile(t_iofile *infile, int i, int count, int *error)
{
	int	fd;

	fd = -1;
	if (infile->type == INFILE)
		fd = open_normal_infile(infile, error);
	else
		fd = open_heredoc_infile(infile, error);
	if (i != count - 1)
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}

int open_infile(t_iofile *infiles)
{
    int         fd;
    int         error;
    int         count;
    int         i;
    t_iofile    *current;

    fd = -1;
    error = 0;
    count = 0;
    current = infiles;
    
    if (!infiles)
        return (STDIN_FILENO);
    while (current)
    {
        count++;
        current = current->next;
    }   
    current = infiles;
    i = 0;
    while (i < count)
    {
        fd = aux_open_infile(current, i, count, &error);
        current = current->next;
        i++;
    }  
    if (error == 1 && fd > 0)
    {
        close(fd);
        fd = -1;
    }
    return (fd);
}
