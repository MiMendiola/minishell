/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:29:16 by mmendiol          #+#    #+#             */
/*   Updated: 2024/05/23 19:56:43 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token		t_token;
typedef struct s_echo_tk	t_echo_tk;

struct						s_token
{
	int						id;
	char					*command;
	char					**tokens;
	char					*infile;
	char					*outfile;
	t_token					*prev;
	t_token					*next;
};

#endif