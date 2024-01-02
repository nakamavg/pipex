/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicos2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:14:24 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/01 22:13:27 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Ejemplo basico de como funciona execve con comandos pasados por argumento
con padre hijo donde usamos el comando echo para decir soy el hijo y soy el padre

*/

#include <unistd.h> //fork y execlp
#include <stdio.h>	//printf
#include <sys/wait.h> //wait

int main()
{
	int pid = fork(); // crea un proceso hijo y devuelve el id del proceso hijo
	char *hijo = "Soy el proceso hijo\n";
	char *padre = "Soy el proceso padre\n";
	char *error = "Error al crear el proceso hijo\n";

	if (pid == -1) // si el id es -1 es que ha habido un error
		printf("%s", error);
	else if (pid == 0) // Validamos al proceso hijo
	{
		char *argv[] = {"echo", hijo, NULL};
		execve("/bin/echo", argv, NULL);
	}
	else // Validamos al proceso padre
	{
		wait(NULL); // espera a que el hijo termine
		char *argv[] = {"echo", padre, NULL};
		execve("/bin/echo", argv, NULL);
	}
}
