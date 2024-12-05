/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:24:36 by anadal-g          #+#    #+#             */
/*   Updated: 2024/12/05 12:02:13 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	aux_open_infile(t_iofile *infile, int i, int count, int *error)
{
	int		fd;
	char	*name;

	if (infile->type == INFILE)
	{
		fd = open(infile->name, O_RDONLY);
		if (fd < 0)
		{
			perror_error(infile->name);
			*error = 1;
		}
	}
	else
	{
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
	}
	if (i != count - 1)
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}

int	open_infile(t_iofile *infiles)
{
	int			fd;
	int			error;
	int			count;
	t_iofile	*current;

	fd = -1;
	error = 0;
	count = 0;
	fd = -1;
	error = 0;
	count = 0;
	current = infiles;
	while (current)
	{
		count++;
		current = current->next;
	}
	current = infiles;
	for (int i = 0; i < count; i++)
	{
		fd = aux_open_infile(current, i, count, &error);
		current = current->next;
	}
	if (error == 1 && fd > 0)
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}

static int	aux_open_outfile(t_iofile *outfile, int i, int count, int *error)
{
	int	fd;

	fd = -1;
	if (outfile->type == TRUNC)
		fd = open(outfile->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (outfile->type == APPEND)
		fd = open(outfile->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror_error(outfile->name);
		*error = 1;
	}
	if (i != count - 1)
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}

int	open_outfile(t_iofile *outfiles)
{
	int			fd;
	int			error;
	int			count;
	int			index;
	t_iofile	*current;

	fd = -1;
	error = 0;
	count = 0;
	index = 0;
	current = outfiles;
	while (current)
	{
		count++;
		current = current->next;
	}
	current = outfiles;
	while (current)
	{
		fd = aux_open_outfile(current, index, count, &error);
		current = current->next;
		index++;
	}
	if (error == 1 && fd > 0)
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}
