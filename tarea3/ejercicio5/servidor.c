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
    int servidor, cliente, size, length;
    struct sockaddr_un local, remote;
    char buffer[100];

    servidor = socket(AF_UNIX, SOCK_STREAM, 0);
    
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCKET);
    unlink(local.sun_path);
    
    length = strlen(local.sun_path) + sizeof(local.sun_family);
    bind(servidor, (struct sockaddr *)&local, length);
    listen(servidor, 10);

    while (1) {
        int n;
        printf("Esperando una conexion...\n");
        size = sizeof(remote);
        cliente = accept(servidor, (struct sockaddr *)&remote, &size);

        printf("Conectado.\n");
 

        while (n=recv(cliente, buffer, 100, 0)) { //mientras el cliente exista
            printf("\nCliente: %s", buffer);
	        printf("> "), fgets(buffer, 100, stdin), !feof(stdin);
	        send(cliente, buffer, strlen(buffer), 0);
        }

        close(cliente);
    }
    
	return 0;
}
