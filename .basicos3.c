/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .basicos3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:14:24 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/02 17:48:39 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Ejemplo execve y fork y pipe
*/
#include <stdio.h>
#include <stdlib.h>	//exit
#include <stdio.h>	//printf
#include <unistd.h>	//execve
#include <sys/wait.h>	//wait
#include "include/pipex.h"
int check_numargc(int argc , char **arg)
{
	if (argc < 5)
	{
		ft_printf("wrong arguments\n");
		exit(EXIT_FAILURE);
	}
	while(*arg)
	{
		ft_printf("%s\n", *arg);
		arg++;
	}
return (EXIT_SUCCESS);
}
char *create_path(char *arg)
{
	char *path = "/bin/";
	char *tmp;
	tmp = ft_strjoin(path, arg);
	return (tmp);
}

void execute_command(char *path, char **argv, int *fd, int close_fd, int dup_fd)
{
    char *cmd[] = {argv[0], argv[1], NULL};
    close(fd[close_fd]);
    dup2(fd[dup_fd], dup_fd);
    close(fd[dup_fd]);
    execve(path, cmd, NULL);
}
int main(int argc, char **argv, char **envp )
{
check_numargc(argc, argv);
char *path;
char *path2;
	path=create_path(argv[1]);
	path2=create_path(argv[3]);

//esto es para concatenar el path con el nombre del ejecutable
ft_printf("Ruta del programa 1 : %s\n", path);
ft_printf("Ruta del programa 2 : %s\n", path2);
int pid;
int fd[2];
pipe(fd);
pid = fork();
char *cmd1[] = {argv[1], argv[2], NULL};
char *cmd2[] = {argv[3], argv[4], NULL};
wait(NULL);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(path,cmd1, NULL);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execve(path2, cmd2, NULL);
	}
	
return 0;
}







