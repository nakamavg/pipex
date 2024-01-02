/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:01:59 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/02 19:18:17 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

 void	check_numargc(int argc)
{
	if (argc != 5)
		return (send_error("Error: number of arguments\n"));
	
}

char	*create_path(char **envp)
{
	while(*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
}
	
 t_pipex	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));//reservamos memoria para la estructura
	if (!pipex)
		send_error("Error: calloc\n");
	pipex->infile = open(argv[1], O_RDONLY);//abrimos el fichero de entrada
	if (pipex->infile < 0)
		send_error("Error: INFILE\n");
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,  0000644);
	if (pipex->outfile < 0)
		send_error("Error OUTFILE\n");
	if (pipe(pipex->tube) == -1)
		send_error("Error: pipe\n"); 
	pipex->paths = create_path(envp);//obtenemos la variable de entorno PATH
	pipex->cmd_paths = ft_split(pipex->paths, ':');//obtenemos los paths
	pipex->pid1 = fork();//creamos el primer hijo
	if (pipex->pid1 == 0)
		first_child(pipex);
	
	
	
		

	return (pipex);
}
int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	
	check_numargc(argc);
	pipex = init_pipex(argc,argv, envp);
	return (0);
}