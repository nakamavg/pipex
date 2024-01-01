
import os

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


