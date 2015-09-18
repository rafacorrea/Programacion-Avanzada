#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#define N 0


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

typedef struct
{
	int numero;
	char* fecha;
}RelacionFechas;

//void freeAll(Cama * , Paciente * , int , int );

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

    srand(time(NULL)); //para generar datos
    Persona *p;
    Edificacion *e;
    
    int decision = 1;
    

    p=NULL;//arreglo de personas
    e=NULL;//arreglo de edificaciones
    int personas = 0;//cuantas personas en el arreglo
    int edificaciones = 0;//cuantas edificaciones en el arreglo
    
    /*MENU*/
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
				reporte(p,e,personas,edificaciones); //GENERAR REPORTE
				break;
        }
        

    }    
	/*FIN MENU*/

    //freeAll(c, p, pacientes, camas);
    return 0;
}




/*void freeAll(Cama * c, Paciente * p, int pacientes, int camas)
{
    int i;
    for (i =0; i<camas; i++)
    {
        printf("hola\n");
        free(((c+i)->paciente)->nombre);
        free(((c+i)->paciente)->apellidos);
        free(((c+i)->paciente)->telefono);
        free((c+i)->paciente);
    }
    free(c);

    for(i=0; i<pacientes;i++)
    {
        free((p+i)->nombre);
        free((p+i)->apellidos);
        free((p+i)->telefono);

    }
    free(p);
}

*/

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

    printf("Ingrese el nombre:\n");
    scanf("%s", (*p+editar)->nombre);
    printf("Ingrese el apellido:\n");
    scanf("%s", (*p+editar)->apellido);
    printf("Cuando nacio: \n");
    scanf("%s", (*p+editar)->nacimiento);
    printf("Cuando se unio: \n");
    scanf("%s", (*p+editar)->ingreso);
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
    
    printf("Ingrese el tipo (1-Edificio, 2-Torre, 3-Nave):\n");
    scanf("%d", &((aux)->tipo));
    temptipo = (aux)->tipo;

    (aux)->periodo = rand()%6;
    (aux)->pisos=rand()%10 + 1;
    (aux)->modales = malloc(sizeof(int)*((aux)->pisos));
    int fin = ((aux)->pisos);
    int i;
    for(i = 0 ; i< fin; i++)
    {
   		*(((aux)->modales) + i) = 5+i;
    }
	switch(rand()%3)
    {
		case 0:
			(aux)->fecha = "2015-09-17";
			break;
		case 1:
			(aux)->fecha = "2015-09-16";
			break;
		case 2:
			(aux)->fecha = "2015-09-15";
			break;
	}	
	
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
    if(fork()==0) //para simular un trabajador activo
    {
		for( ; e < final; e++)
		{

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
    sleep(1); //Para que se vea el menu principal al final... esperar al hijo para poder visualizar bien el menu. No es necesario pero el meno se vuelve confuso si se quita ya que el padre imprime el menu principal primero que el hijo imprime los resultados
}


void reporte(Persona * p, Edificacion * e, int personas, int edificaciones)
{
	char * inicio = malloc(sizeof(char) * 20); //fecha inicio
	char * fin = malloc(sizeof(char) * 20); //fecha fin (rango)
    printf("Ingrese primera fecha (yyyy-mm-dd): ");
    scanf("%s", inicio);
    printf("Ingrese ultima fecha (yyyy-mm-dd): ");
    scanf("%s", fin);
    
	int cuantosDias = 0; //para ver cuantos dias con modelos existen
	RelacionFechas * modPorFecha = NULL; //estructura para relacionar fechas con modelos
	RelacionFechas * inicioF = modPorFecha;
	RelacionFechas * finF;

	Persona * inicioP = p; //inicio de arreglo personas
	Persona * finalP = p + personas; //final

	Edificacion * inicioE = e; //inicio arreglo edificaciones
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
					printf("Persona#%d\n\nNomina -%d\nNombre - %s\nApellido - %s\nNacimiento - %s\nIngreso - %s\nSalario - %d\nPuesto - %s\n\n", p-inicioP, p->nomina, p->nombre, p->apellido, p->nacimiento, p->ingreso, p->salario, p->puesto);
				}
			}
			
			int agregado=0;
			RelacionFechas * aux2 = modPorFecha;
			finF= modPorFecha + cuantosDias; //final del arreglo
			for( ; aux2 < finF; aux2++)
			{

				if(aux2!=NULL && !(strcmp(e->fecha, (aux2)->fecha))) //si se encuentra la fecha en el arreglo, agregar 1 a numero
				{
					(aux2)->numero += 1; 
					agregado = 1;
					//break;
				}	
			}
			if(!agregado) //si no se encontro la fecha en el arreglo...
			{	
				
				modPorFecha = (RelacionFechas *)realloc(modPorFecha,(cuantosDias+1)*sizeof(RelacionFechas));
				RelacionFechas * aux;
				aux = modPorFecha + cuantosDias;
				cuantosDias+=1;
				(aux)->numero = 1;
				(aux)->fecha = malloc(sizeof(char)*20);
				(aux)->fecha = e->fecha;
				agregado=1;
				//modPorFecha-=1;
			}
		}
	}
	//modPorFecha -= cuantosDias;
	//printf("TEST2\n");
	RelacionFechas * finalF = modPorFecha + cuantosDias;
	for ( ; modPorFecha < finalF; modPorFecha++)
	{
		printf("\tFECHA: %s - %d PROYECTOS:\n", modPorFecha->fecha, modPorFecha->numero);
		e = inicioE;
		for( ; e < finalE; e++)
		{
			if(!(strcmp(e->fecha, modPorFecha->fecha)))
			{
				/*IMPRESION DE MODELOS*/
				printf("\n\nPROYECTO\nPisos -%d\nTipo - %d\nPeriodo - %d\nFecha - %s\nAutorNomina - %d\n\n", e->pisos, e->tipo,  e->periodo, e->fecha, e->autorNomina);

				int i;
				int fin = e->pisos; 
                printf("Modales");
            	for (i=0; i<fin; i++)
            	{
					printf("\t %d\n", *((e->modales)+i));
				}
                if(e->tipo==1)
				{
                	if(*((e->dependeTipo)))
						printf("Siemtria: Si\n");
                    else
                    	printf("Simetria: No");
				}
                else if (e->tipo==2)
                {
					fin = 2 * (e->pisos);
					
                    printf("Diametros");
                	for (i=0; i<fin; i++)
        			{
						printf("\t %d\n", *((e->dependeTipo)+i));
					}
				}
                else if (e->tipo==0)
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
					/*FIN DE IMPRESION DE MODELOS*/
				}
			}
		}
	}
}

