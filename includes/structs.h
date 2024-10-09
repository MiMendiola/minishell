/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:29:16 by mmendiol          #+#    #+#             */
/*   Updated: 2024/09/25 16:43:38 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token	t_token;
typedef struct s_env	t_env;

typedef enum e_token_type
{
	COMMAND,
	ARGUMENT,
	OPERATOR
}	t_token_type;


struct						s_token
{
	int					id;
	char				*command;
	char				**tokens;
	char				*content;
	t_token				*prev;
	t_token				*next;
	t_token_type		type;
	t_env				*envp;
	char				*outfile;
	char				*infile;
	char				**path;
	char				*shlvl;
};

struct 					s_env
{
	char			*args;
	char			*name;
	int				status;
	char			*value;
	t_env	*next;
	t_env	*last;
	t_env 			*env_list; 
};

typedef struct s_state 
{
    t_env	*envp;
} t_state;

#endif