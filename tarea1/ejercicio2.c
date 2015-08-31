#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PREGUNTAS 3


//Declaracion de Estructuras
typedef struct{
    char *uno;
    char *dos;
    char *tres;
    char *cuatro;
    char *cinco;
    char *seis;
    char *pregunta;
    
}Pregunta;

typedef struct{
    char *nombre;
    int edad;
    int *respuestas;
}Participante;




Pregunta* preguntas( Pregunta *);
Participante* participantes( Participante **, Pregunta *, int *);
void histograma( int *);

int poblacion = 0;
int *resp;

int main(int argc, char** argv) {
    
    int decision = 1;
    
    Pregunta *pr = (Pregunta *) malloc(sizeof( Pregunta));
    pr = (Pregunta *) malloc( sizeof( Pregunta) * 3);
    Participante *par = ( Participante *) malloc(sizeof( Participante));
    par->respuestas = (int *) malloc( sizeof( int) * PREGUNTAS);
    resp = (int *) malloc(sizeof( int) * 300);
    char * menu = (char *) malloc(sizeof( char) * 300);
    strcpy(menu,"\nOpciones: \n1-Ingresar preguntas\n2-Nuevo participante\n3-Histograma\n0-Salir\n");
    while(decision){
        
        printf("%s",menu);
        scanf("%d", &decision);
        switch(decision){
            case 1:
                pr=preguntas(pr);
                break;
            case 2:
                par=participantes(&par, pr, resp);
                break;
            case 3:
                histograma(resp);
                break;
        }
    }
    
    Pregunta * aux;
    for (aux = pr; aux < (pr+poblacion); ++aux) {
        free(pr->pregunta);
        free(pr->dos);
        free(pr->tres);
        free(pr->cuatro);
        free(pr->cinco);
        free(pr->seis);
    }
    
    free(pr);
    free(par);
    free(resp);
    free(menu);
    return 0;
}

Pregunta* preguntas(Pregunta * preguntas){
    int i;
    for(i=0;i<PREGUNTAS;i++){
        
        (preguntas+i)->pregunta = (char * ) malloc(sizeof(char) * 60);
        printf("\nIngresa la pregunta %d \n", i+1);
        scanf("%s",(preguntas+i)->pregunta);
        
        (preguntas+i)->uno = (char * ) malloc(sizeof(char) * 60);
        printf("Ingresa la respuesta 1\n");
        scanf("%s",(preguntas+i)->uno);
        
        (preguntas+i)->dos = (char * ) malloc(sizeof(char) * 60);
        printf("Ingresa la respuesta 2\n");
        scanf("%s",(preguntas+i)->dos);
        
        (preguntas+i)->tres = (char * ) malloc(sizeof(char) * 60);
        printf("Ingresa la respuesta 3\n");
        scanf("%s",(preguntas+i)->tres);
        
        (preguntas+i)->cuatro = (char * ) malloc(sizeof(char) * 60);
        printf("Ingresa la respuesta 4\n");
        scanf("%s",(preguntas+i)->cuatro);
        
        (preguntas+i)->cinco = (char * ) malloc(sizeof(char) * 60);
        printf("Ingresa la respuesta 5\n");
        scanf("%s",(preguntas+i)->cinco);
        
        (preguntas+i)->seis = (char * ) malloc(sizeof(char) * 60);
        printf("Ingresa la respuesta 6\n");
        scanf("%s",(preguntas+i)->seis);
    }
    return preguntas;
}

Participante* participantes(Participante **par, Pregunta *pr, int *resp){
    
    Participante *temp;
    int edad, i, respuesta;
    poblacion++;
    printf("poblacion %d\n", poblacion);
    *par= (Participante *) realloc( *par, sizeof( Participante) * poblacion+1);
    
    
    (*par+poblacion)->nombre = (char * ) malloc(sizeof(char) * 15);
    printf("Ingresa el nombre\n");
    scanf("%s",(*par+poblacion)->nombre);
    
    while( edad < 18 || edad > 120)
    {
        printf("Ingrese la edad\n");
        scanf("%d", &edad);
        if( edad < 18 || edad > 120)
            printf("No puedes participar, edad incorrecta\n");
    }
    (*par+poblacion)->edad = edad;
    
    for( i=0; i<PREGUNTAS; i++){

        printf("Pregunta %d\n%s\n", i+1, (pr+i)->pregunta);
        printf("1) %s\n",(pr+i)->uno);
        printf("2) %s\n",(pr+i)->dos);
        printf("3) %s\n",(pr+i)->tres);
        printf("4) %s\n",(pr+i)->cuatro);
        printf("5) %s\n",(pr+i)->cinco);
        printf("6) %s\n",(pr+i)->seis);
        printf("Respuesta:\n");
        scanf("%d", &respuesta);
        
        if( edad >= 18 && edad <= 25)
                *(resp+( 60*0 )+( i*6 )+ respuesta) +=1;
        if( edad >= 26 && edad <= 35)
                *(resp+( 60*1 )+( i*6 )+ respuesta) +=1;
        if( edad >= 36 && edad <= 45)
                *(resp+( 60*2 )+( i*6 )+ respuesta) +=1;
        if( edad >= 46 && edad <= 65)
                *(resp+( 60*3 )+( i*6 )+ respuesta) +=1;
        if( edad >= 66 && edad <= 120)
                *(resp+( 60*4 )+( i*6 )+ respuesta) +=1;
    }
    
    return *par;
}

void histograma(int *resp){
    int i, j;
    
    for( i=0; i<PREGUNTAS; i++){
        printf("Pregunta %d\n", i+1);
        printf("No. Res\tEdad 18-25\tEdad 26-35\tEdad 36-45\tEdad 56-65\tEdad 66-120\n");
        for(j=1;j<7;j++)
                printf("%d\t%10d\t%10d\t%10d\t%10d\t%10d\n", j, *(resp+(60*0)+(i*6)+j), *(resp+(60*1)+(i*6)+j), *(resp+(60*2)+(i*6)+j), *(resp+(60*3)+(i*6)+j), *(resp+(60*4)+(i*6)+j));
    }
}
