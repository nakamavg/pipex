/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 04:58:24 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/03 05:07:57 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	check_numargc(int argc)
{
	if (argc != 5)
		return (send_error(ERR_INPUT));
}

char	*create_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

static int	open_infile_outfile(char *filename, bool is_outfile)
{
	int	infile;
	int	outfile;

	if (is_outfile)
	{
		outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile < 0)
			send_error(ERR_OUTFILE);
		return (outfile);
	}
	else
	{
		infile = open(filename, O_RDONLY);
		if (infile < 0)
			send_error(ERR_INFILE);
		return (infile);
	}
}

static void	create_pipe(int *tube)
{
	if (pipe(tube) == -1)
		send_error(ERR_PIPE);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	check_numargc(argc);
	pipex.infile = open_infile_outfile(argv[1], false);
	pipex.outfile = open_infile_outfile(argv[argc - 1], true);
	create_pipe(pipex.tube);
	pipex.paths = create_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	create_processes(&pipex, argv, envp);
	close_pipes(&pipex);
	wait_for_children(&pipex);
	dad_free(&pipex);
	return (0);
}
