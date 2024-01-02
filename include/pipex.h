/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:16:32 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/02 19:14:53 by dgomez-m         ###   ########.fr       */
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

//list
typedef struct s_pipex
{
	pid_t	pid1; //Pid del hijo 1
	pid_t	pid2;//Pid del hijo 2
	int		tube[2];//Tuberia para comunicar a los hijos
	int		infile; //Fichero de entrada
	int		outfile; //Fichero de salida
	char	*paths;//Variable de entorno PATH
	char	**cmd_paths; //Array de paths para ejecutar los comandos
	char	**cmd_args; //Array de argumentos para ejecutar los comandos
	char	*cmd; //Comando a ejecutar
}t_pipex;

//error 
void	send_error(char *str);
//init
t_pipex	*init_pipex(int argc , char **argv, char **envp);
//utils
char	*create_path(char **envp);

#endif