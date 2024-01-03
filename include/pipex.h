/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:16:32 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/03 04:58:09 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
// personal libraries
# include "../lib/libft/libft.h"

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"
# define ERR_PIPE "Pipe"
# define ERR_INPUT "Invalid number of arguments.\n"

//list
typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}t_pipex;

//error 
void	send_error(char *str);

int		msg_error(char *str);
//init
t_pipex	init_pipex(int argc, char **argv, char **envp);
//utils
char	*create_path(char **envp);
//process
void	create_processes(t_pipex *pipex, char **argv, char **envp);
void	wait_for_children(t_pipex *pipex);
//free
void	child_free(t_pipex *pipex);
void	dad_free(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
int		main(int argc, char **argv, char **envp);
#endif