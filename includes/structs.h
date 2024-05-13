/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:29:16 by mmendiol          #+#    #+#             */
/*   Updated: 2024/05/08 16:50:16 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token	t_token;
typedef struct s_env	t_env;

struct					s_token
{
	int					id;
	char				*str;
	t_token				*prev;
	t_token				*next;
	char	**envp;
	char	*outfile;
	char	*infile;
	char	**path;
	char	*shlvl;
};

struct 					s_env
{
	int	fd[2];
	int	status;
	int	status_final;
};



#endif