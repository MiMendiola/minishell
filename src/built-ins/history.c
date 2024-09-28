/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmntrix <lmntrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:05:02 by mmendiol          #+#    #+#             */
/*   Updated: 2024/09/28 14:12:32 by lmntrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	show_history(void)
{
	HIST_ENTRY	**history;
	int			width;
	int			i;

	width = 6;
	history = history_list();
	if (history)
	{
		i = -1;
		while (history[++i])
			ft_printf("%*d  %s\n", width, i + history_base, history[i]->line);
	}
}
