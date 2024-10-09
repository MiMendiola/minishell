/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:25:12 by mmendiol          #+#    #+#             */
/*   Updated: 2024/03/12 17:35:13 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"


// int ft_strcmp(const char *s1, const char *s2)
// {
//     if (!s1 || !s2)
//     {
//         ft_putstr_fd("Error: Puntero NULL pasado a ft_strcmp.\n", STDERR_FILENO);
//         return -1;  // Devuelve un valor que indique error
//     }

//     while (*s1 && (*s1 == *s2))
//     {
//         s1++;
//         s2++;
//     }

//     return (unsigned char)(*s1) - (unsigned char)(*s2);
// }


int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char str1[] = "-1";
	char str2[] = "1";

	printf("Original: %d\n", strcmp(str1, str2, 5));
	printf("Mia: %d", ft_strcmp(str1, str2, 5));
	return 0;
}
*/