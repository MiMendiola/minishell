/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:49:47 by anadal-g          #+#    #+#             */
/*   Updated: 2024/10/17 19:00:18 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/lib/ft_substr.c"
#include "../../libft/lib/ft_strtrim.c"
#include "../../libft/lib/ft_strlen.c"
#include "../../libft/lib/ft_strdup.c"
#include "../../libft/lib/ft_calloc.c"
#include "../../libft/lib/ft_bzero.c"
#include "../../libft/lib/ft_strchr.c"
#include "../../libft/lib/ft_memset.c"
#include "../../libft/additional/free_matrix_bool.c"
#include "../../libft/additional/character_finder.c"
#include "../../libft/additional/jump_character.c"

int	is_operator(char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
		return (2); // Para manejar '<<'
	else if (str[i] == '>' && str[i + 1] == '>')
		return (2); // Para manejar '>>'
	else if (str[i] == '<' || str[i] == '>')
		return (1); // Para manejar '<' o '>'
	return (0);
}

void	jump_cosas(char *input, int *counter, char quote)
{
	// Saltar hasta el final de la secuencia de comillas
	while (input[*counter] && input[*counter] != quote)
		(*counter)++;
}

void	read_hasta_caracter(char *input, int *start, int *counter)
{
	char	quote;

	*start = *counter;
	while (input[*counter])
	{
		// Si encontramos una comilla simple o doble, saltamos hasta la comilla de cierre
		if (input[*counter] == DQUOTES || input[*counter] == SQUOTES)
		{
			quote = input[(*counter)++];
			jump_character(input, counter, quote, TRUE);
		}
		// Si encontramos un operador, detenemos la lectura
		else if (is_operator(input, *counter))
			break ;
		(*counter)++;
	}
}

int	process_operator_or_space(char **r, char *str, int *i, int *commands)
{
    int op_len;

    // Saltar espacios iniciales
    while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'))
        (*i)++;
    if (str[*i] == '\0')
        return (0); // Final de la cadena, no hay nada más que procesar

    // Comprobamos si hay un operador como '<', '<<', '>', '>>'
    op_len = is_operator(str, *i);
    if (op_len)
    {
        printf("Detected operator: %.*s\n", op_len, &str[*i]);  // DEBUG print para ver si se detecta el operador
        r[(*commands)++] = ft_substr(str, *i, op_len);  // Guardamos el operador como token
        *i += op_len;  // Saltamos el operador
        return (1);  // Se procesó un operador
    }

    return (0); // No se encontró un operador, seguimos procesando la cadena
}


int	escribir_command(char **r, char *str)
{
    int		i;
    int		j;
    int		commands;
    char	*tmp_substr;
    char	*tmp_trim;

    i = 0;
    commands = 0;
    while (str[i])
    {
        // Procesamos los espacios y operadores
        if (process_operator_or_space(r, str, &i, &commands))
            continue;  // Si se procesó un operador, pasamos a la siguiente iteración

        // Si no es un operador, leemos hasta encontrar el siguiente operador o fin
        read_hasta_caracter(str, &j, &i);
        tmp_substr = ft_substr(str, j, i - j);  // Copiamos la secuencia de texto
        if (tmp_substr == NULL || *tmp_substr == '\0')
        {
            free(tmp_substr);
            continue;  // Si tmp_substr está vacía, la ignoramos
        }
        tmp_trim = ft_strtrim(tmp_substr, " ");  // Eliminamos espacios sobrantes
        free(tmp_substr);
        if (tmp_trim == NULL)
            return (free_matrix_bool(r));  // Manejo de errores
        r[commands++] = tmp_trim;
    }
    r[commands] = NULL;  // Asegúrate de terminar el array de cadenas con NULL
    return (1);
}

int	command_contador(char *str)
{
	int		i;
	int		commands;
	char	quote;
	int		op_len;

	i = -1;
	commands = 0;
	while (str[++i])
	{
		// Si encontramos comillas, saltamos hasta el final de las comillas
		if (str[i] == DQUOTES || str[i] == SQUOTES)
		{
			quote = str[i++];
			jump_character(str, &i, quote, TRUE);
		}
		// Si encontramos un operador, lo contamos como un token
		op_len = is_operator(str, i);
		if (op_len)
		{
			commands++;
			i += (op_len - 1);  // Saltamos el operador
		}
		// Si encontramos un espacio o el final, contamos el token
		else if (!character_finder(str[i], ' ') && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			commands++;
	}
	return (commands);
}

char	**command_divisor(char const *s)
{
	int		commands;
	char	**list_commands;

	if (!s)
		return (0);
	// Contar el número de tokens (comandos u operadores)
	commands = command_contador((char *)s);
	// Reservar memoria para los tokens
	list_commands = ft_calloc(commands + 1, sizeof(char *));
	if (!list_commands)
		return (NULL);
	// Dividir la cadena en tokens
	if (!escribir_command(list_commands, (char *)s))
		return (NULL);
	return (list_commands);
}


int	main(void)
{
	//char *str = "Hola-mundo-en-un-string-arrayfgddg     -  fdgdfg";
	// char *charset = "-+-";

	// char **split = ft_split(str, charset);

	// int i = 0;
	// while (split[i])
	// {
	// 	printf("%s\n", split[i]);
	// 	i++;
	// }

	// free(split); // Liberamos la memoria asignada
	//printf("%d", cont_words(str, '-'));
	char *str = "hello!>> ze><zzzzzzz";
	char **res;
	int	i = 0;

	res = command_divisor(str);
	while (res[i])
	{
		printf("[%s]\n", res[i]);
		i++;
	}
	free(res);
	return (0);
}