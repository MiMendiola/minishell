/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:42:16 by mmendiol          #+#    #+#             */
/*   Updated: 2024/07/02 11:40:37 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADDITIONAL_H
# define ADDITIONAL_H

# include "./libft.h"

// FUNCTIONS ADDED LATER
int		free_matrix_bool(char **str);
void	free_matrix(char **matrix);
long	ft_atol(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strchr_bool(const char *s, int c);
int		character_finder(char str, char c);
char	*ft_strcat(char *dest, const char *str);
void	*ft_realloc(void *ptr, size_t original_size, size_t new_size);

#endif