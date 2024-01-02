# Índice

- [Pipex](#pipex)
- [Diario de a bordo](#diario-de-a-bordo)
	- [Empezando mis investigaciones](#empezando-mis-investigaciones)
		- [`fork()`](#fork)
		- [`wait()`](#wait)
		- [Funcionamiento de `pipe()` en c](#funcionamiento-de-pipe-en-c)
		- [`execve` y `dup`](#execve-y-dup)



# Pipex

Este proyecto es una implementación simple del comando de shell `pipex`, que es similar a la redirección de tuberías en Unix (`|`).

# Diario de a bordo 

## Empezando mis investigaciones

Queria empezar a construir y adquirir conocimientos haciendo unas pequeñas llamadas simples a ver si entendi lo que se explicaba en el manual

### `fork()`

- crea una bifurcacion es decir una copia exacta(hijo) del programa(padre) y nos devuelve el id que podemos guardar en una variable entera en caso de error en la creacion del hijo nos devolvera -1

### `wait()`

- Espera a que el proceso hijo que le pasemos por argumento acabe

- Si le pasamos el argumento `NULL` a wait espera a que cualquier hijo acabe 

- Para demostrar esto tenemos un pequeño main 

![basicos.c](/images/conwait.png)

si quitas el wait y no esperas que el/los procesos hijos terminen 
y el padre acaba antes puede haber problemas en este caso:

![Alt text](/images/sinwait.png)


### Que pasa si tenemos multiples forks?

-En este caso 

```c
int main()
{
	int id =fork();
	fork();
}
```
Se creara una bifurcacion para el proceso hijo y otra para el padre de locos y si lo llamamos otra vez ?
todos tendran un nuevo proceso haciendo un efecto escalera bien chulo
[Volver al índice](#índice)

### Funcionamiento de `pipe()` en c

- Es complicado y esta duro pero antes de ponerse a nada queria entender bien el funcionamiento de la funcion original primero veamos el comportamiento sin fork

```c
int main()
{
#include <unistd.h>
#include <stdio.h>
#include "lib/get_next_line/get_next_line.h"
#include "lib/libft/libft.h"

int main()
{
	char *line;
	int fd[2];
	char *str;
	pipe(fd);
	ft_putstr_fd("hola mundo\n", fd[1]);
	if (get_next_line(fd[0], &str) == EXIT_SUCCESS)
		printf("success\n");
	else
		printf("error\n");
	printf("%s", str);
}
}
```
```bash
nakama@DESKTOP-FIDJ5EI:~/pipex$ ./a.out 
hola mundo
```
- Pipe siempre va a necesitar 2 fd , para crear entrada y salida de datos 0 es entadas lo que hace es duplicar  fd[1](entrada) en fd[0](salida)

1. Pipe enlaza dos fd como entrada y salada
2. Escribimos en el fd de entrada 
3. leemos del fd de salida
4. imprimimos

-Ahora bien si hacemos un fork para tener dos procesos
![forkpipe](/images/forkpipe.png)

- tendremos los fd por duplicado y tanto para el padre como para el hijo tendremos los fd[0] y fd[1]

- En este caso le digo al programa si esta en el proceso hijo cierra el fd[0] ya que no vamos a leer nada , despues de escribir cierro el fd de salida

- si es el caso de estar en el proceso padre cierra el fd de salida , lee lo que hay en el fd de entrada que para el es el [0] imprime lo que conseguimos y cerramos el fd de entrada.

[Volver al índice](#índice)


### `execve` y `dup`

- la funcion execve ejecuta un programa `int execve(const char *pathname, char *const _Nullable argv[],char *const _Nullable envp[])`

	- El primer parametro necesita la ruta en el sistema del programa;

	- En este momento que estoy  aun en plena investigación(02/01/2024 05:08 am) se me ocurrido una pequeña funcion para esto que no sera la difinitiva pero para testear
	```c
	char *create_path(char *arg)
	{
		char *path = "/bin/";
		char *tmp;
		tmp = ft_strjoin(path, arg);
		return (tmp);
	}
	
	```
```bash
		
	nakama@DESKTOP-FIDJ5EI:~/pipex$ ./a.out  ls -l wc -l
			./a.out
			ls
			-l
			wc
			-l
			Ruta del programa 1 : /bin/ls
			Ruta del programa 2 : /bin/wc
```

- como lo que estoy probando esta todo dentro de bin es facil sacar la ruta

- el segundo parametro de execve es el comando y los parametros, siempre debe acabar en null

- el 3 es la variable de entorno

- `dup2(int oldfd, int newfd)`
   Hace que newfd sea la copia de oldfd en nuestro caso nos sirve para redirigir la salida del programa por la pipe
   usando `STDOUT_FILENO` y `STDIN_FILENO` para la entrada o la salida

### Main explicando la información Estudiada hasta ahora

```c
int main(int argc, char **argv, char **envp )
{
check_numargc(argc, argv);
char *path;
char *path2;
	path=create_path(argv[1]);
	path2=create_path(argv[3]);

//esto es para concatenar el path con el nombre del ejecutable
printf("Ruta del programa 1 : %s\n", path);
printf("Ruta del programa 2 : %s\n", path2);
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
```
```bash
nakama@DESKTOP-FIDJ5EI:~/pipex$ ./a.out  ls -l wc -l
./a.out
ls
-l
wc
-l
Ruta del programa 1 : /bin/ls
Ruta del programa 2 : /bin/wc
9
```
[Volver al índice](#índice)
















