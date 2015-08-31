#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define N 0

typedef struct
{
    char* nombre;
    char* apellidos;
    int edad;
    char* telefono;
    int cama;
} Paciente;

typedef struct
{
    Paciente * paciente;
} Cama;

void freeAll(Cama * , Paciente * , int , int );
void quePacienteEnQueCama(Cama *, int );
void llegaPaciente (Paciente ** , Cama ** , int*, int*);
int cuantosPacientes(Paciente * );
int cuantasCamas(Cama * );
void borrar(Paciente ** , int , int * );
void verPacientes(Paciente * , int );
void contarCamas(Cama * , int );

main()
{
    

    Paciente *p;
    Cama *c;
    
    int decision = 1;
    

    p=NULL;//(Paciente*)malloc(0);
    c=(Cama*)malloc(5 * sizeof(Cama));
    int camas = 5;
    int pacientes = 0;

    while(decision)
    {
        printf("\nSeleccione su opcion: \n1-Llega un paciente\n2-Revisar Cama\n3-Dar de alta por cama\n4-Ver todos los pacientes\n5-Contar camas disponibles\n\n");
        
    
        scanf("%d", &decision);
        
        switch(decision)
        {
            case 1:
        
                llegaPaciente(&p, &c, &pacientes, &camas);
                break;  
            case 2:
                quePacienteEnQueCama(c, camas);
                break;     
            case 3:
                darAltaPaciente(&p, &c, &pacientes, &camas);
                break;
            case 4:
                verPacientes(p, pacientes);
                break;
            case 5:
                contarCamas(c,camas);
                break;
        }
        

    }    
    freeAll(c, p, pacientes, camas);
    return 0;
}


void llegaPaciente (Paciente ** p, Cama ** c, int* pacientes, int* camas)
{

    Paciente * aux;;
    *p = (Paciente *)realloc(*p,(*pacientes+1)*sizeof(Paciente));
    *pacientes+=1;

    aux = *p + *pacientes - 1;

    (aux)->nombre = malloc(sizeof(char)*10);
    printf("Ingrese el nombre:\n");
    scanf("%s", (aux)->nombre);
    (aux)->apellidos = malloc(sizeof(char)*10);
    printf("Ingrese el apellido:\n");
    scanf("%s", (aux)->apellidos);
    printf("Cual es la edad: \n");
    scanf("%d", &((aux)->edad));
    (aux)->telefono = malloc(sizeof(char)*10);
    printf("Ingrese el telefono:\n");
    scanf("%s", (aux)->telefono);

    
    while(1)
    {   
        Cama * temp2;
        Cama * temp = *c + *camas;
        for( temp2 = *c; temp2 < temp; temp2++)   
        {
            if(temp2->paciente == NULL)
            {
                temp2->paciente = aux;
                 printf("Se agrego el paciente #%d a la cama #%d\n", (aux - *p), temp2 - *c);
                aux->cama=temp2-*c;
                return;
            }
        }
        
        *c = (Cama *)realloc(*c,(*camas+5)*sizeof(Cama));  
        printf("No hay suficientes camas, agregando 5 mas...\n");   
        *camas+=5;   

    }

}

void borrar(Paciente ** p, int aBorrar, int * pacientes)
{
    Paciente * temp = (Paciente *)malloc((*pacientes-1)*sizeof(Paciente));
    memmove(temp, *p, (aBorrar)*sizeof(Paciente));
    memmove(temp + aBorrar, *p + (aBorrar+1), (*pacientes - aBorrar - 1)*sizeof(Paciente));
    *pacientes = *pacientes - 1;
    free (*p);
    *p = temp;
    
}

void quePacienteEnQueCama(Cama * c, int camas)
{
    int numero;
    printf("Que cama quiere ver?\n");
    scanf("%d", &numero);
    if(camas-numero > 1)
    {
        if((c+numero)->paciente == NULL)
        {
            printf("Esa cama esta vacia\n");
            return;
        }
        printf("El paciente en esta cama es:\nNombre - %s\nApellido - %s\nEdad - %d\nTelefono - %s\n", (c+numero)->paciente->nombre, (c+numero)->paciente->apellidos, (c+numero)->paciente->edad, (c+numero)->paciente->telefono);
    }
    else
        printf("Esa cama no existe\n");
}

void darAltaPaciente(Paciente ** p, Cama ** c, int * pacientes, int * camas)
{
    int numero;
    printf("Que numero de cama desea dar de alta?\n");
    scanf("%d", &numero);
    if(camas-numero>1 & (*c+numero)->paciente != NULL)
    {
        borrar(p, numero, pacientes);
        ((*c)+numero)->paciente = NULL;
    }
    else
        printf("Esa cama no tiene paciente o no existe\n");
}

void verPacientes(Paciente * p, int pacientes)
{
    Paciente * inicio = p;
    Paciente * final = p + pacientes;
    for( ; p < final; p++)
    printf("Paciente #%d\n\nNombre - %s\nApellido - %s\nEdad - %d\nTelefono - %s\nCama - %d\n",p - inicio, p->nombre, p->apellidos, p->edad, p->telefono, p->cama);
}

void contarCamas(Cama * c, int camas)
{
    int disponibles = 0;
    
    Cama* final = c + camas;
    for( ; c < final; c++)
    {
        if(c->paciente == NULL)
            disponibles++;
    }	
    printf("Camas disponibles: %d\nCamas ocupadas: %d\n", disponibles, camas-disponibles);
}

void freeAll(Cama * c, Paciente * p, int pacientes, int camas)
{
    int i;
    /*for (i =0; i<camas; i++)
    {
        printf("hola\n");
        free(((c+i)->paciente)->nombre);
        free(((c+i)->paciente)->apellidos);
        free(((c+i)->paciente)->telefono);
        free((c+i)->paciente);
    }*/
    free(c);

    for(i=0; i<pacientes;i++)
    {
        free((p+i)->nombre);
        free((p+i)->apellidos);
        free((p+i)->telefono);

    }
    free(p);
}
