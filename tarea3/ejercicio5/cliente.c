#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET "echo_socket"

int main(void)
{
    int servidor, size, length;
    struct sockaddr_un remote;
    char buffer[100];

    servidor = socket(AF_UNIX, SOCK_STREAM, 0);

    printf("Conectandose...\n");

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCKET);
    length = strlen(remote.sun_path) + sizeof(remote.sun_family);
    connect(servidor, (struct sockaddr *)&remote, length);


    printf("Conectado.\n");

    while(printf("> "), fgets(buffer, 100, stdin), !feof(stdin)) {
    
        send(servidor, buffer, strlen(buffer), 0);
        
        if ((size=recv(servidor, buffer, 100, 0)) > 0) {
            printf("Servidor: %s \n", buffer);
        }
        
        else if (!size)
        {
            printf("El servidor ha terminado la conexion\n"); //si recv = 0, el servidor ya no existe
            exit(1);
        }       
    }

    close(servidor);

    return 0;
}
