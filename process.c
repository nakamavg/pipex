/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 19:18:42 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/02 20:19:00 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

static char *get_cmd(char **paths, char *cmd)
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

void	first_child(t_pipex *pipex, char *argv[], char **envp)
{
	dup2(pipex->tube[1], STDOUT_FILENO);
	close(pipex->tube[0]);
	dup2(pipex->infile, STDIN_FILENO);
	pipex->cmd_args = ft_split(argv[2], ' ');
	pipex->cmd
	
}