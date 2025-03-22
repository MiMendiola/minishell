/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:02:15 by anadal-g          #+#    #+#             */
/*   Updated: 2025/03/22 12:19:18 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes(char *input)
{
	char	*src;
	char	exterior_quote;

	if (!input)
		return ;
	src = input;
	exterior_quote = 0;
	while (*src)
	{
        if ((*src == DQUOTES || *src == SQUOTES) && (exterior_quote == 0 || exterior_quote == *src))
		{
            if (exterior_quote == 0)
                exterior_quote = *src;
			else if (exterior_quote == *src)
                exterior_quote = 0;
        }
		else
            *input++ = *src;
		src++;
    }
	*input = '\0';
}

int	dollar_not_between_squotes(char *str)
{
	int single_quotes;
    int double_quotes;

	single_quotes = 0;
	double_quotes = 0;
    while (*str)
    {
        if (*str == '"' && !single_quotes)
            double_quotes = !double_quotes;
        else if (*str == '\'' && !double_quotes)
            single_quotes = !single_quotes;
        else if (*str == '$' && (!single_quotes || double_quotes))
            return 1;
        str++;
    }
    return 0;
}

void	lexerize(t_token **tokens)
{
    int i;
    t_token *aux;

    if (!tokens || !*tokens)
        return ;
    aux = *tokens;
    while (aux)
	{
        i = -1;
        // if (aux->tokens == NULL)
        // {
        //     ft_putstr_fd("Error: tokens->tokens es NULL en lexerize.\n", STDERR_FILENO);
        //     return;
        // }
        while (aux->tokens[++i])
		{
			if (ft_strchr_bool(aux->tokens[i], '$') && dollar_not_between_squotes(aux->tokens[i]))
				expander(aux, aux->tokens[i], i);
        	remove_quotes(aux->tokens[i]);
		}
        aux = aux->next;
    }
}

void    *expand_variables_in_command(char *input, t_env *envp)
{
    char *tmp_str;
    char *found;
    char *env_name;
    
    (void)envp;
    tmp_str = ft_calloc(1, ft_strlen(input) + 1);
    env_name = ft_calloc(1, ft_strlen(input) + 1);
    // Encontramos el primer '$' fuera de comillas simples
    found = found_dollar_not_squotes(input);
    // Copiamos lo que viene antes del primer '$'
    if (found)
        ft_strlcat(tmp_str, input, (found - input) + 1);
    // Expandimos las variables de entorno usando la función expand_variables
    while (found != NULL)
    {
        if (dollar_not_between_squotes(found))
            expand_variables(&tmp_str, &input, &found, env_name);
        found = ft_strchr(found + 1, '$');
    }
    // Redimensionamos la cadena para incluir el resto del comando
    tmp_str = ft_realloc(tmp_str, ft_strlen(tmp_str), ft_strlen(tmp_str) + ft_strlen(input) + 1);
    if (!tmp_str)
    {
        free(env_name);
        return NULL;
    }
    tmp_str = ft_strcat(tmp_str, input);
    free(env_name);
    return tmp_str;

}


void	prepare_command(char **input, t_env *envp, t_token *tokens)
{
    int     i;
    char    *expanded_input;

    i = 0;
    while (tokens->tokens[i])
    {
        expander(tokens, tokens->tokens[i], i);
        i++;
    }
    expanded_input = expand_variables_in_command(*input, envp);
    if (!expanded_input)
    {
        ft_putstr_fd("Error al expandir.\n", STDERR_FILENO);
        return ;
    }
    free(*input);
    *input = expanded_input;
}

int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

void parse_command(char *input, t_token **tokens, t_env *envp)
{
    if (!input || !tokens)
    {
        ft_putstr_fd("Error: Entrada o tokens no válidos.\n", STDERR_FILENO);
        return ;
    }
    // tokens = ft_calloc(1, sizeof(t_token *));
    divide_tokens(input, tokens); //Redirecciones
    if (!tokens[0])
    {
        ft_putstr_fd("Error: No se pudo asignar memoria para tokens.\n", STDERR_FILENO);
        return;
    }
    prepare_command(&input, envp, *tokens);// Expansor
    if (!(*tokens)->tokens)
    {
        ft_putstr_fd("Error: tokens->tokens sigue siendo NULL después de create_tokens.\n", STDERR_FILENO);
        return;
    }
    lexerize(tokens);  // Procesa los tokens
    // TODO
    // EJECUTOR
}

