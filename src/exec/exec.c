/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadal-g <anadal-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:05:36 by mmendiol          #+#    #+#             */
/*   Updated: 2024/12/03 11:07:07 by anadal-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_childs(int *status, int pid)
{
	int		final_status;
	pid_t	waited;

	final_status = 0;
	while (1)
	{
		waited = waitpid(-1, status, 0);
		if (waited == -1)
			break ;
		if (waited == pid)
			final_status = WEXITSTATUS(*status);
	}
	return (final_status);
}

int env_size(t_env *env)
{
    int size = 0;

    while (env)
    {
        size++;
        env = env->next;
    }
    return size;
}

char	*find_path(char *command, char **envp)
{
	int		i;
	int		env;
	char	**paths;
	char	*path;
	char	*part_path;

	if (ft_strchr(command, '/'))
		return (command);
	env = check_envp(envp, &command);
	paths = ft_split(envp[env] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, command);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

char **env_to_array(t_env *env)
{
    int size;
    char **env_array;
    int i;
    
    size = env_size(env);
    i = 0;
    env_array = malloc((size + 1) * sizeof(char *));
    while (env)
    {
        env_array[i++] = ft_strjoin(env->name, env->value);
        env = env->next;
    }
    env_array[i] = NULL;
    return env_array;
}

void execute_command(t_token *token, t_env **env)
{
    pid_t pid;
    char **cmd_args;
    char *cmd_path;
    char **env_array;

    cmd_args = token->tokens;
    env_array = env_to_array(*env);
    cmd_path = find_path(token->command, env_array);
    if ((pid = fork()) == 0)
    {
        if (execve(cmd_path, cmd_args, env_array) == -1)
        {
            perror("Error al ejecutar el comando");
            exit(EXIT_FAILURE);            
        }
    }
    else if (pid < 0)
        perror_error("Error en fork");
    else
        waitpid(pid, NULL, 0);
    int i = 0;
    while (env_array[i])
    {
        free(env_array[i++]);
        i++;
    }
    free(env_array);
    free(cmd_path);
}

void heredoc(char *args[])
{
    int infile;
    char *line;
    char *delimiter;

    infile = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (infile == -1)
    {
        perror("Error al crear archivo temporal para heredoc");
        return;
    }
    delimiter = ft_strjoin(args[2], "\n");
    line = get_next_line(0);
    while (line != NULL && ft_strcmp(line, delimiter) != 0)
    {
        ft_putstr_fd(line, infile);
        free(line);
        line = get_next_line(0);
    }
    free(delimiter);
    if (line)
        free(line);
    close(infile);
}


// Función para manejar redirecciones de entrada, incluyendo heredoc
void infile_till_last(t_iofile *infiles)
{
    int infile;

    while (infiles)
    {
        if (infiles->type == HEREDOC)
        {
            char *args[] = {NULL, NULL, infiles->name, NULL};
            heredoc(args);
            infile = open(TMP_FILE, O_RDONLY);
        } 
        else if (infiles->type == INFILE)
            infile = open(infiles->name, O_RDONLY);
        if (infiles->next == NULL && infile != -1) {
            if (dup2(infile, STDIN_FILENO) == -1)
            {
                perror("Error en dup2 para infile");
                exit(EXIT_FAILURE);
            }
            close(infile);
        }
        else if (infile != -1)
            close(infile);
        infiles = infiles->next;
    }
}


void outfile_till_last(t_iofile *outfiles)
{
    int outfile;

    while (outfiles)
    {
        if (outfiles->next == NULL)
        {
            if (outfiles->type == APPEND || outfiles->type == TRUNC)
                outfile = open(outfiles->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (outfile == -1)
            {
                perror("Error al abrir archivo de salida");
                continue;
            }
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
        }
        else
        {
            if (outfiles->type == APPEND || outfiles->type == TRUNC)
                outfile = open(outfiles->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (outfile == -1)
            {
                perror("Error al abrir archivo de salida intermedio");
                continue;
            }
            close(outfile);
        }
        outfiles = outfiles->next;
    }
}

// Función principal de ejecución, gestionando pipes, redirecciones, y heredoc
void executor(t_token *tokens, t_env *env)
{
    int fd[2] = {-1, -1};
    pid_t pid;

    while (tokens)
    {
        if (tokens->next && pipe(fd) == -1)
        {
            perror("Error al crear pipe");
            exit(EXIT_FAILURE);
        }
        if ((pid = fork()) == -1)
        {
            perror("Error en fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
            first_child(tokens, env, fd);
        else
        {
            close(fd[1]);
            waitpid(pid, NULL, 0);
            if (tokens->next)
                fd[0] = fd[1];
        }
        tokens = tokens->next;
    }
}

