#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
//#include <cstdlib.h>

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




typedef struct
{
    char * nombre;
    char * apellido;
    int nomina;
    char * nacimiento;
    char * ingreso;
    int salario;
    char * puesto;
} Persona;

typedef struct
{
    int pisos;
    int tipo;
    int* modales;
    int periodo;
    int* dependeTipo;
    char* fecha;
    int autorNomina;
    
} Edificacion;


void freeAll(Cama * , Paciente * , int , int );
void quePacienteEnQueCama(Cama *, int );
void llegaPaciente (Paciente ** , Cama ** , int*, int*);
int cuantosPacientes(Paciente * );
int cuantasCamas(Cama * );

void verPacientes(Paciente * , int );
void contarCamas(Cama * , int );
void agregarPersona(Persona **, int*);
void verPersonas(Persona * , int );
void editarPersona(Persona ** p, int* personas);
void borrarPersona(Persona ** , int , int * );
void borrar(Persona **p, int * personas);
void crearEdificacion(Edificacion ** e, int * edificaciones);
void verMisModelos(Persona * p, Edificacion * e, int personas, int edificaciones);
void reporte(Persona * p, Edificacion * e, int personas, int edificaciones);

main()
{
    printf("%d", strcmp("2000-02-12", "2000-12-12"));
    srand(time(NULL));
    Persona *p;
    Edificacion *e;
    
    int decision = 1;
    

    p=NULL;//(Paciente*)malloc(0);
    e=NULL;
    int personas = 0;
    int edificaciones = 0;
    int pacientes = 0;
    

    while(decision)
    {
        printf("\nSeleccione su opcion: \n1-Agregar persona\n2-Ver Nomina\n3-Editar nomina\n4-Borrar nomina\n5-Crear Edificacion\n6-Buscar por Empleado y Fecha\n7-Generar Reporte(Personas que modelaron entre fechas) \n0-Salir\n");
        
    
        scanf("%d", &decision);
        
        switch(decision)
        {
            case 1:
        
                agregarPersona(&p, &personas);
                break;  
            case 2:
                verPersonas(p, personas);
                break;   

            case 3:
                editarPersona(&p, &personas);
                break;

            case 4:
                borrar(p, &personas);
                break;
            case 5:
                crearEdificacion(&e, &edificaciones);
                break;
            case 6:
                verMisModelos(p, e, personas, edificaciones);
                break;
			case 7:
				reporte(p,e,personas,edificaciones);
				break;
        }
        

    }    
    //freeAll(c, p, pacientes, camas);
    return 0;
}


void llegaPaciente (Paciente ** p, Cama ** c, int* pacientes, int* camas)
{

    Paciente * aux;;
    *p = (Paciente *)realloc(*p,(*pacientes+1)*sizeof(Paciente));
    *pacientes+=1;

    aux = *p + *pacientes - 1;

    (aux)->nombre = malloc(sizeof(char)*20);
    printf("Ingrese el nombre:\n");
    scanf("%s", (aux)->nombre);
    (aux)->apellidos = malloc(sizeof(char)*20);
    printf("Ingrese el apellido:\n");
    scanf("%s", (aux)->apellidos);
    printf("Cual es la edad: \n");
    scanf("%d", &((aux)->edad));
    (aux)->telefono = malloc(sizeof(char)*20);
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

/*void borrar(Paciente ** p, int aBorrar, int * pacientes)
{
    Paciente * temp = (Paciente *)malloc((*pacientes-1)*sizeof(Paciente));
    memmove(temp, *p, (aBorrar)*sizeof(Paciente));
    memmove(temp + aBorrar, *p + (aBorrar+1), (*pacientes - aBorrar - 1)*sizeof(Paciente));
    *pacientes = *pacientes - 1;
    free (*p);
    *p = temp;
    
}
*/

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

/*void darAltaPaciente(Paciente ** p, Cama ** c, int * pacientes, int * camas)
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
}*/

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



void agregarPersona(Persona ** p, int* personas)
{
    Persona * aux;
    *p = (Persona *)realloc(*p,(*personas+1)*sizeof(Persona));
    *personas+=1;

    aux = *p + *personas - 1;

    (aux)->nombre = malloc(sizeof(char)*20);
    printf("Ingrese el nombre:\n");
    scanf("%s", (aux)->nombre);
    (aux)->apellido = malloc(sizeof(char)*20);
    printf("Ingrese el apellido:\n");
    scanf("%s", (aux)->apellido);
    (aux)->nacimiento = malloc(sizeof(char)*20);
    printf("Cuando nacio: \n");
    scanf("%s", (aux)->nacimiento);
    (aux)->ingreso = malloc(sizeof(char)*20);
    printf("Cuando se unio: \n");
    scanf("%s", (aux)->ingreso);
    (aux)->puesto = malloc(sizeof(char)*20);
    printf("Ingrese el puesto:\n");
    scanf("%s", (aux)->puesto);
    printf("Nomina: \n");
    scanf("%d", &((aux)->nomina));
    printf("Salario: \n");
    scanf("%d", &((aux)->salario));
}


void verPersonas(Persona * p, int personas)
{
    Persona * inicio = p;
    Persona * final = p + personas;
    for( ; p < final; p++)
    printf("Persona#%d\n\nNomina -%d\nNombre - %s\nApellido - %s\nNacimiento - %s\nIngreso - %s\nSalario - %d\nPuesto - %s\n\n", p-inicio, p->nomina, p->nombre, p->apellido, p->nacimiento, p->ingreso, p->salario, p->puesto);
}

void editarPersona(Persona ** p, int* personas)
{
    int editar;

    printf("Que persona");
    scanf("%d", &editar);

    //Persona * aux;
    //*p = (Persona *)realloc(*p,(*personas+1)*sizeof(Persona));
    //*personas+=1;

    //aux = *p + *personas - 1;

    //(*p)->nombre = malloc(sizeof(char)*10);
    printf("Ingrese el nombre:\n");
    scanf("%s", (*p+editar)->nombre);
    //(aux)->apellido = malloc(sizeof(char)*10);
    printf("Ingrese el apellido:\n");
    scanf("%s", (*p+editar)->apellido);
    //(aux)->nacimiento = malloc(sizeof(char)*10);
    printf("Cuando nacio: \n");
    scanf("%s", (*p+editar)->nacimiento);
    //(aux)->ingreso = malloc(sizeof(char)*10);
    printf("Cuando se unio: \n");
    scanf("%s", (*p+editar)->ingreso);
    //(aux)->puesto = malloc(sizeof(char)*10);
    printf("Ingrese el puesto:\n");
    scanf("%s", (*p+editar)->puesto);
    printf("Nomina: \n");
    scanf("%d", &((*p+editar)->nomina));
    printf("Salario: \n");
    scanf("%d", &((*p+editar)->salario));      
}

void borrar(Persona **p, int * personas)
{
     int borrar;
     printf("Que persona desea borrar:");
     scanf("%d", &borrar);
     borrarPersona(p, borrar, personas);
}

void borrarPersona(Persona ** p, int aBorrar, int * personas)
{
    Persona * temp = (Persona *)malloc((*personas-1)*sizeof(Persona));
    memmove(temp, *p, (aBorrar)*sizeof(Persona));
    memmove(temp + aBorrar, *p + (aBorrar+1), (*personas - aBorrar - 1)*sizeof(Persona));
    *personas = *personas - 1;
    free (*p);
    *p = temp;
    
}

void crearEdificacion(Edificacion ** e, int * edificaciones)
{
    Edificacion * aux;
    *e = (Edificacion *)realloc(*e,(*edificaciones+1)*sizeof(Edificacion));
    *edificaciones+=1;

    aux = *e + *edificaciones - 1;
    
    int temptipo;
    
    //(aux)->tipo = malloc(sizeof(char)*10);
    printf("Ingrese el tipo (1-Edificio, 2-Torre, 3-Nave):\n");
    scanf("%d", &((aux)->tipo));
    temptipo = (aux)->tipo;

    //(aux)->modales = rand()%5;
    (aux)->periodo = rand()%6;
    (aux)->pisos=rand()%10 + 1;
    (aux)->modales = malloc(sizeof(int)*((aux)->pisos));
    int fin = ((aux)->pisos);
    int i;
    for(i = 0 ; i< fin; i++)
    {
   		*(((aux)->modales) + i) = 5+i;
    }
    (aux)->fecha = "2015-09-17";
    (aux)->autorNomina = rand()%2 + 1;
    switch (temptipo)
    {
        case 1:
        {
           (aux)->dependeTipo = malloc(sizeof(int));
           *(((aux)->dependeTipo)) = rand()%2;
           break;
        }
        case 2:
        {
           (aux)->dependeTipo = malloc(sizeof(int)*(((aux)->pisos) * 2));
           //(aux)->dependeTipo = rand()%100;
           int fin = ((aux)->pisos) * 2;
           
           for(i = 0 ; i< fin; i++)
           {
           		*(((aux)->dependeTipo) + i) = i;
           }
           break;
        }
        case 3:
        {
	   (aux)->dependeTipo = malloc(sizeof(int));
           *(((aux)->dependeTipo)) = rand()%3;
	   break;
        }
           
    }
    printf("\nSe creo la edificacion\n\n");
}

void verMisModelos(Persona * p, Edificacion * e, int personas, int edificaciones)
{
    int nomina;
	char * fecha = malloc(sizeof(char) * 20);
    printf("Dame la nomina\n");
    scanf("%d", &nomina);
	printf("\nDame la fecha\n");
	scanf("%s", fecha);

	int i;
    Edificacion * inicio = e;
    Edificacion * final = e + edificaciones;
    if(fork()==0)
    {
		for( ; e < final; e++)
		{

			//printf("TEST: %d", strncmp(e->fecha, fecha));
			if(e->autorNomina == nomina && !strcmp(e->fecha, fecha))
			{
		             char * tipo;
		             if(e->tipo == 1)
		                 tipo = "Edificio";
		             else if(e->tipo==2)
		                 tipo = "Torre";
		             else
		                 tipo = "Nave";
            	printf("\nEdificacion#%d\n\nPisos -%d\nTipo - %s\nPeriodo - %d\nFecha - %s\nAutorNomina - %d\n\n", e-inicio, e->pisos, tipo,  e->periodo, e->fecha, e->autorNomina);
            	int fin = e->pisos; 
                printf("Modales");
            	for (i=0; i<fin; i++)
            	{
					printf("\t %d\n", *((e->modales)+i));
				}
                if(tipo=="Edificio")
				{
                	if(*((e->dependeTipo)))
						printf("Siemtria: Si\n");
                    else
                    	printf("Simetria: No");
				}
                else if (tipo=="Torre")
                {
					fin = 2 * (e->pisos);
                    printf("Diametros");
                	for (i=0; i<fin; i++)
        			{
						printf("\t %d\n", *((e->dependeTipo)+i));
					}
				}
                else if (tipo=="Nave")
				{
                    switch(*((e->dependeTipo)))
					{
						case 0: 
                        {
							printf("Techo: Monitor\n");
							break;
						}
						case 1: 
                        {
							printf("Techo: Dos Aguas\n");
							break;
						}
						case 2: 
                        {
							printf("Techo: Creciente\n");
							break;
						}
						default: 
                        {
							printf("Techo: No definido\n");
							break;
						}
					}
 
				}
               
                

			} 
		}
        exit(1);
	}
    sleep(1); //Para que se vea el menu principal al final...
}


void reporte(Persona * p, Edificacion * e, int personas, int edificaciones)
{
	//char * inicio;
    //char * fin;
	char * inicio = malloc(sizeof(char) * 20);
	char * fin = malloc(sizeof(char) * 20);
    printf("Ingrese primera fecha (yyyy-mm-dd): ");
    scanf("%s", inicio);
    printf("Ingrese ultima fecha (yyyy-mm-dd): ");
    scanf("%s", fin);
    

	Persona * inicioP = p;
	Persona * finalP = p + personas;
	Edificacion * inicioE = e;
    Edificacion * finalE = e + edificaciones;
	for( ; e < finalE; e++)
	{

		if(strcmp(inicio,e->fecha)<=0 && strcmp(e->fecha,fin)<=0)
		{
			int aux = e->autorNomina;
			for( ; p < finalP; p++)
			{
				if (p->nomina == aux)
				{
					printf("Nomina -%d\nNombre - %s\nApellido - %s\nNacimiento - %s\nIngreso - %s\nSalario - %d\nPuesto - %s\n\n", p->nomina, p->nombre, p->apellido, p->nacimiento, p->ingreso, p->salario, p->puesto);
				}
			}
			

		}
    
	}

}
/*
typedef struct
{
    int pisos;
    int tipo;
    int* modales;
    int periodo;
    int* dependeTipo;
    char* fecha;
    int autorNomina;
    
} Edificacion;
*/
