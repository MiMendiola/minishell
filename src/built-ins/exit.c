/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:59:23 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/25 17:20:43 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_exit(t_token **tokens, char *input)
{
	show_lst(tokens);
	ft_printf("%s\n", EXIT_TXT);
	free_list(tokens);
	free(input);
	exit(EXIT_FAILURE);
}
