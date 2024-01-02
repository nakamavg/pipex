/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicopipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 23:28:58 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/02 01:08:35 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "lib/get_next_line/get_next_line.h"
#include "lib/libft/libft.h"
#include <sys/wait.h>

int main()
{
	char *line;
	int fd[2];
	char *str;
	pipe(fd);
	pid_t pid = fork();
	wait(NULL);

	if(pid == -1)
		printf("error\n");
	else if (pid == 0)
	{
		//somos el hijo
		close(fd[0]);
		printf("Hijo escribe\n");
		ft_putstr_fd("hola soy tu hijo\n", fd[1]);
		close(fd[1]);
		printf("Hijo termina\n");
	}
	else
	{
		//somos el padre
		close(fd[1]);
		get_next_line(fd[0], &line);
		printf("Padre lee:\n");
		printf("%s", line);
		printf("te recibo soy tu padre y acabo de esperar al cierre de tu proceso\n");
		close(fd[0]);
	}
}

