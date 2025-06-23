/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:10:05 by anadal-g          #+#    #+#             */
/*   Updated: 2025/06/23 13:58:52 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// DEFINIR la variable global aquí (no solo declararla)
int g_signal_received = 0;

void crtl_c(int sign)
{
    (void)sign;
    g_signal_received = SIGINT;
    rl_replace_line("", 0);
    rl_on_new_line();
    write(1, "\n", 1);
    rl_redisplay();
}

void signal_input(void)
{
    signal(SIGINT, &crtl_c);
    signal(SIGQUIT, SIG_IGN);
}

void handle_signal_in_child(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
