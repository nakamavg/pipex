/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:21:03 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/02 20:32:22 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>


/*
Ejemplo para ver como funciona access
*/


int main()
{
	char *path = "/bin/lss";
	if (access(path, X_OK) == 0)
		printf("existe\n");
	else
		printf("no existe\n");
		
	if (access("/etc/passwd", R_OK) == 0) {
    printf("El archivo se puede leer.\n");
} else {
    printf("El archivo no se puede leer.\n");
}
	if (access("/etc/passwd", W_OK) == 0)
    	printf("El archivo se puede escribir.\n");
	else 
    	printf("El archivo no se puede escribir.\n");

	return (0);
}