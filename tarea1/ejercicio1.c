#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char* nombre;
    char* apellidos;
	int edad;
    char* rol;
} Persona;

typedef struct
{
    char * nombre;
    int eslora;
    int manga;
    int maximo;
    Persona * tripulacion;
    Persona * propietario;
} Barco;

void agregarProp(Persona ** , Barco ** );
void agregarTrip(Persona ** , Barco ** );
void agregarPersona(Persona ** );
void verPersonas(Persona *);
void verBarcos(Barco *);
int cuantosBarcos(Barco * );
void agregarBarco(Barco ** );
void borrar(Persona ** , int );
void freeMemory(Persona * , Barco * );

main()
{
    printf("Seleccione su opcion: \n1-Agregar Barco\n2-Agregar Persona\n3-Agregar Persona a Barco\n4-Mostrar Barcos\n5-Mostrar Personas\n");
    int decision;
    
    scanf("%d", &decision);
    char * nombre; 
    int temp;

    
    Persona *p;
    Barco *b;

    b=NULL;//(Barco*)malloc(sizeof(Barco));
    p=NULL;//(Persona*)malloc(sizeof(Persona));

    while(decision)
    {
        switch(decision)
        {
            case 1:
        
                agregarBarco(&b);
                break;       
            case 2:
                agregarPersona(&p);
                break;

            case 3:
                agregarTrip(&p, &b);
                break;

            case 4:
        
                //printf("Numero de Barcos: %d", cuantosBarcos(b));
                verBarcos(b);
                break;
            case 5:
                verPersonas(p);
                break;
            case 6:
                agregarProp(&p, &b);
                break;
        }
    printf("Seleccione su opcion: \n1-Agregar Barco\n2-Agregar Persona\n3-Agregar Persona a Barco\n4-Mostrar Barcos\n5-Mostrar Personas\n6-Agregar Propietario\n0-Salir\n");
    scanf("%d", &decision);
    }    
 
    freeMemory(p, b);  
    //free(b);  
    return 0;
}




void agregarProp(Persona ** p, Barco ** b)
{
    int persona;
    int barco;

    verPersonas(*p);
    printf("Escoja la persona (numero):\n");
    scanf("%d", &persona);
    verBarcos(*b);
    printf("Escoja el barco (numero)\n");
    scanf("%d", &barco);
    
    Persona ** aux =  (&(*b + barco)->propietario);
    if(!(cuantasPersonas(*aux)))
    {
        *aux = (Persona *)realloc(*aux,(cuantasPersonas(*aux)+1)*sizeof(Persona));

        Persona * aux2 = *aux + cuantasPersonas(*aux)-1;
        //aux2->nombre = malloc(sizeof(char)*10);

        printf("%s\n",(*p+persona)->nombre);
        aux2->nombre = (*p + persona)->nombre;
        printf("%s\n\n",(aux2)->nombre);
    	aux2->apellidos = (*p + persona)->apellidos;
    	aux2->edad = (*p + persona)->edad;
    	aux2->rol = (*p + persona)->rol;
   
        borrar(p,persona);
    }
    else
        printf("Ya existe un propietario!\n");
    
}


void agregarTrip(Persona ** p, Barco ** b)
{
    int persona;
    int barco;

    verPersonas(*p);
    printf("Escoja la persona (numero):\n");
    scanf("%d", &persona);
    verBarcos(*b);
    printf("Escoja el barco (numero)\n");
    scanf("%d", &barco);
    
    Persona ** aux =  (&(*b + barco)->tripulacion);
    if(cuantasPersonas(*aux)<(*b)->maximo)
    {
        *aux = (Persona *)realloc(*aux,(cuantasPersonas(*aux)+1)*sizeof(Persona));

        Persona * aux2 = *aux + cuantasPersonas(*aux)-1;
        //aux2->nombre = malloc(sizeof(char)*10);

        printf("%s\n",(*p+persona)->nombre);
        aux2->nombre = (*p + persona)->nombre;
        printf("%s\n\n",(aux2)->nombre);
    	aux2->apellidos = (*p + persona)->apellidos;
    	aux2->edad = (*p + persona)->edad;
    	aux2->rol = (*p + persona)->rol;
   
        borrar(p,persona);
    }
    else
        printf("La tripulacion se encuentra llena!\n");
    
}
void borrar(Persona ** p, int aBorrar)
{
    Persona * temp = (Persona *)malloc((cuantasPersonas(*p)-1)*sizeof(Persona));
    memmove(temp, *p, (aBorrar)*sizeof(Persona));
    memmove(temp + aBorrar, *p + (aBorrar+1), (cuantasPersonas(*p) - aBorrar - 1)*sizeof(Persona));
    free (*p);
    *p = temp;
    
}
void agregarPersona(Persona ** p)
{
    Persona * aux;
    //if(*p + cuantasPersonas(*p) - 1 != NULL)
        *p = (Persona *)realloc(*p,(cuantasPersonas(*p)+1)*sizeof(Persona));
    aux = *p + cuantasPersonas(*p) - 1;

    (aux)->nombre = malloc(sizeof(char)*10);
    printf("Ingrese el nombre:\n");
    scanf("%s", (aux)->nombre);
    (aux)->apellidos = malloc(sizeof(char)*10);
    printf("Ingrese el apellido:\n");
    scanf("%s", (aux)->apellidos);
    printf("Cual es la edad: \n");
    scanf("%d", &((aux)->edad));
    (aux)->rol = malloc(sizeof(char)*10);
    printf("Ingrese el rol:\n");
    scanf("%s", (aux)->rol);
    
}

void verPersonas(Persona *p)
{
    Persona * temp2 = p;
    Persona * temp = p + cuantasPersonas(p);
    for( ; p < temp; p++)
    {
        printf("\n\tPersona #%d\n\tNombre - %s\n\tApellido - %s\n\tEdad - %d\n\tRol - %s\n", p - temp2, p->nombre,p->apellidos,p->edad,p->rol);
    }
    
}

void agregarBarco(Barco ** b)
{
    Barco * aux;
    *b = (Barco *)realloc(*b,(cuantosBarcos(*b)+1)*sizeof(Barco));
    //free (*b);
    aux = *b + cuantosBarcos(*b) - 1;

    (aux)->nombre = malloc(sizeof(char)*10);
    printf("Ingrese el nombre:\n");
    scanf("%s", (aux)->nombre);
    printf("Cual es la eslora: \n");
    scanf("%d", &((aux)->eslora));
    printf("Cual es la manga:\n");
    scanf("%d", &(aux)->manga);
    printf("Cual es el tamano de la tripulacion:\n");
    scanf("%d", &(aux)->maximo);
    //(aux)->tripulacion = NULL;//malloc(sizeof(Persona)*0);//(aux->maximo));
    //(aux)->propietario = malloc(sizeof(Persona));//NULL;
    //free(aux);
}

void verBarcos(Barco *b)
{
    Barco * temp2 = b;
    Barco * temp = b + cuantosBarcos(b);
    for( ; b < temp; b++)
    {
        printf("\n\n-------------------------------------------");
        Persona * aux = b->tripulacion;
        Persona * aux2 = b->propietario;
        printf("\nBARCO #%d\n\tBarco - %s\n\tEslora - %d\n\tManga - %d\n\tMax. Trip - %d\nPlazas Disponibles - %d\n\n\tPROPIETARIO", b- temp2, b->nombre,b->eslora,b->manga,b->maximo, b->maximo - cuantasPersonas(aux));
        verPersonas(aux2);
        
        printf("\n.......................................\n");
        printf("\tTRIPULACION\n\n");
        verPersonas(aux);
        printf(".......................................\n");
        printf("-------------------------------------------\n\n");
        
    }
    
    
}


int cuantosBarcos(Barco * b)
{
    return malloc_usable_size(b)/sizeof(Barco);
}

int cuantasPersonas(Persona * p)
{
    return malloc_usable_size(p)/sizeof(Persona);
}

void freeMemory(Persona * p, Barco * b)
{
    int i;
    int j;
    for(i = 0; i < cuantosBarcos(b); i++)
    {
        free((b+i)->nombre);
       

        Persona * aux =  ((b+i)->tripulacion);
        Persona * aux2 = aux + cuantasPersonas(aux);
        for ( j = 0; j <  cuantasPersonas(aux); j++)
        {
            free((aux+j)->nombre);
            free((aux+j)->apellidos);
            free((aux+j)->rol);
           
        }
        free((b+i)->tripulacion);
        //free((b->propietario)->nombre);
        //free((b->propietario)->apellidos);
        //free((b->propietario)->rol);
        //free((b)->propietario);

        //free((b)->nombre);
        //free(b);
        
    }
    free(b);

    //free(eliminar);
    //free(eliminar->nombre);

    for( i = 0; i < cuantasPersonas(p); i++)
    {
        free((p+i)->nombre);
        free((p+i)->apellidos);
        free((p+i)->rol);
    }
    free(p);
        
}
