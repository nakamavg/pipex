/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:18:42 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/03 04:03:48 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	first_cmd(t_pipex pipex, char *argv[], char *envp[])
{
	ft_printf("Estoy en el primer cmd \n");
	dup2(pipex.tube[1], STDOUT_FILENO);// duplicamos la salida estandar en el pipe de escritura
	close(pipex.tube[0]);// cerramos el pipe de lectura
	dup2(pipex.infile, STDIN_FILENO);// duplicamos la entrada estandar en el fichero de entrada
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
		msg_error(ERR_CMD);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	second_cmd(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.tube[0], STDIN_FILENO); 
	close(pipex.tube[1]);
	dup2(pipex.outfile, STDOUT_FILENO);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
		msg_error(ERR_CMD);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void create_processes(t_pipex *pipex, char **argv, char **envp) {
	ft_printf("Estoy en Create_procceses \n");
    pipex->pid1 = fork();
    if (pipex->pid1 == 0)
        first_cmd(*pipex, argv, envp);
    pipex->pid2 = fork();
    if (pipex->pid2 == 0)
		{
        second_cmd(*pipex, argv, envp);
		exit(0);
		}
	else
	{
		close(pipex->tube[0]);
		close(pipex->tube[1]);
	}
}

void wait_for_children(t_pipex *pipex) 
{
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
}

