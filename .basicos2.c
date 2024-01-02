/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicos2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:15:40 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/01 23:14:51 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Ejemplo de como se envia y recibe informacion entre proceso padre e hijo
y manejo de fd */
#include <stdio.h>	//printf
#include <unistd.h>	//pipe, fork, close, read, write
#include <sys/wait.h> //wait
#include <stdlib.h> //exit
#include  "lib/libft/libft.h"

int main()
{
    int fd[2];
    int pid;
    char *hijo = "Hola papa soy el proceso Hijo\n";
    char *padre = "Te recibo hijo soy Papa\n";
    char *error = "Error al crear el proceso hijo\n";
    char buffer[1024];
    
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    printf("fd[0]: %d y fd[1]: %d \n", fd[0], fd[1]);
    pid = fork();
	
	printf("pid: %d\n", pid);
	

    if (pid == -1)
        printf("%s", error);
    else if (pid == 0)
    {
		printf("hijo\n");
		printf("fd[0]: %d y fd[1]: %d \n", fd[0], fd[1]);
        close(fd[0]);
        write(fd[1], hijo, ft_strlen(hijo));
        close(fd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        close(fd[0]);
        printf("%s %s", buffer, padre);
        wait(NULL);
    }
}