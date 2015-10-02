#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

#define PATH "/Log.txt" //para escribir en raiz necesita sudo, puede cambiarse

int main(int argc, char* argv[])
{
    int minutos;
    DIR * directorio;
    struct dirent* in_file;
    int numero;
    FILE *leer=NULL;
    char unChar;
	FILE *fp= NULL;
	pid_t process_id = 0;
	pid_t sid = 0;
	char buffer[33];
	int i =0;
    if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        

            printf( "usage: %s cuantosMinutos(int)\n", argv[0] );
            return 0;

    }
    else
    {
        if (atoi(argv[1]) > 0)
            minutos = atoi(argv[1]);
        else
        {
            printf("Ingrese un numero como parametro\n");
            return 0;
        }
    }
	process_id = fork();

	if (process_id < 0)
	{
		printf("fork failed!\n");
		exit(1);
	}

	if (process_id > 0)
	{
		// MATAR PROCESO PADRE
		exit(0);
	}
	umask(0); //mascara para archivos
	sid = setsid(); //ya es demonio
	if(sid < 0)
	{
		exit(1);
	}
	
	// cambiar a root (ya que es el unico directorio siempre presente en UNIX)
	chdir("/");
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	fp = fopen (PATH, "w+"); //abrir PATH que se definio en el define (si esta en root requiere SUDO/permisos)


    //Empieza el Daemon
	while (1)
	{
		
        fclose(fp);
        fp = fopen(PATH, "w+"); //borrar el archivo
        directorio = opendir("/proc"); //volver a abrir el directorio
        while((in_file = readdir(directorio)))
        {
            if(atoi(in_file->d_name) > 0) //si es un numero ie. es un proceso
            {
                fprintf(fp, "PROCESO NUMERO: %s\n", in_file->d_name);
		        snprintf(buffer,33, "/proc/%s/status", in_file->d_name); 
                leer = fopen(buffer, "r"); //abrir en modo solo lectura
		
                do{
                    unChar = fgetc(leer);
                    fputc(unChar, fp);
                }while(unChar!=EOF); //para copiar los contenidos del archivo
                
                fclose(leer); //cerrar el archivo de status
            }
        }
        sleep(minutos * 60); //ciclo en minutos

	}
    //Termina Daemon
	return (0);
}
