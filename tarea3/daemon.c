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
	// Indication of fork() failure
	if (process_id < 0)
	{
		printf("fork failed!\n");
		// Return failure in exit status
		exit(1);
	}
	// PARENT PROCESS. Need to kill it.

	if (process_id > 0)
	{
		// return success in exit status
		exit(0);
	}
	//unmask the file mode
	umask(0);
	//set new session
	sid = setsid();
	if(sid < 0)
	{
		// Return failure
		exit(1);
	}
	// Change the current working directory to root.
	chdir("/");
    directorio = opendir("/proc");
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	fp = fopen (PATH, "w+");


    //Empieza el Daemon
	while (1)
	{
		
        fclose(fp);
        fp = fopen(PATH, "w+"); //borrar el archivo
        while((in_file = readdir(directorio)))
        {
            if(atoi(in_file->d_name) > 0)
            {
                fprintf(fp, "PROCESO NUMERO: %s\n", in_file->d_name);
		snprintf(buffer,33, "/proc/%s/status", in_file->d_name);
                leer = fopen(buffer, "r");
		
                do{
                    unChar = fgetc(leer);
                    fputc(unChar, fp);
                }while(unChar!=EOF);
                fclose(leer);
            }
        }
        sleep(minutos * 60);

	}

	fclose(fp);
	return (0);
}
