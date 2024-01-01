/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 05:06:26 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/01 06:25:44 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>	  //fork y execve
#include <stdio.h>	  //printf
#include <sys/wait.h> //wait

// programa sencillo que crea un proceso hijo y muestra un mensaje diferente para cada proceso
// para demostrar que se ejecutan en paralelo
// el proceso padre espera a que el hijo termine para terminar el programa gracias a wait

int main(void)
{
	int pid = fork(); // crea un proceso hijo y devuelve el id del proceso hijo
	char *hijo = "Soy el proceso hijo\n";
	char *padre = "Soy el proceso padre\n";
	char *error = "Error al crear el proceso hijo\n";

	if (pid == -1) // si el id es -1 es que ha habido un error
		printf("%s", error);
	else if (pid == 0) // Validamos al proceso hijo
		printf("%s", hijo);
	else // Validamos al proceso padre
	{
		wait(NULL); // espera a que el hijo termine
		printf("%s", padre);
	}
}