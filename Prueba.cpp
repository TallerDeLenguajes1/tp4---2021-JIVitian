#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea{
    int tareaID;
    char *descripcion;
    int duracion;
};

typedef struct Tarea tarea;

void cargarTareas(tarea **array, int tamanio);
void mostrarTares(tarea *array);
void ToDo(tarea **array, tarea **array2, int tamanio);
void busquedaPorID(tarea **array, int tamanio);
void busquedaPorPalabra(tarea **array, int tamanio);

int main(){
    srand(time(NULL));

    tarea **actividades, **realizadas;
    int cantidadAct;

    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cantidadAct);

    actividades = (tarea**)malloc(sizeof(tarea*)*cantidadAct);
    realizadas = (tarea**)malloc(sizeof(tarea*)*cantidadAct);

    printf("\n CARGAR TAREAS \n");
    cargarTareas(actividades, cantidadAct);

   /*for(int i = 0; i < cantidadAct; i++){
        mostrarTares(*(actividades + i));
    }*/

    printf("\n BUSCAR TAREAS POR ID \n");
    busquedaPorID(actividades, cantidadAct);

    printf("\n BUSCAR TAREAS POR PALABRA CLAVE \n");
    fflush(stdin);
    busquedaPorPalabra(actividades, cantidadAct);

    printf("\n ANALIZAR SI SE REALIZARON TAREAS \n");
    ToDo(actividades, realizadas, cantidadAct);

    printf("\n TAREAS REALIZADAS \n");
    for(int i = 0; i < cantidadAct; i++){
        if((*(realizadas + i)) != NULL){
            mostrarTares(*(realizadas + i));
        }
    }

    printf("\n TAREAS PENDIENTES \n");
    for(int i = 0; i < cantidadAct; i++){
        if((*(actividades + i)) != NULL){
            mostrarTares(*(actividades + i));
        }
    }

    return 0;
}

void cargarTareas(tarea **array, int tamanio)
{
    for(int i = 0; i < tamanio; i++){
        printf("-------- TAREA %d-------- \n", i+1);
        *(array + i) = (tarea*)malloc(sizeof(tarea));
        (*(array + i))->tareaID = i + 1;
        (*(array + i))->duracion = rand() % 10 + 1;
        fflush(stdin);
        (*(array + i))->descripcion = (char*)malloc(sizeof(char)*50);
        printf("Descripcion: ");
        gets((*(array + i))->descripcion);
    }
}

void mostrarTares(tarea *tarea)
{
    printf("-------- TAREA %d -------- \n", tarea->tareaID);
    printf("ID: %d \n", tarea->tareaID);
    printf("Duracion: %d hs\n", tarea->duracion);
    printf("Descripcion: %s \n", tarea->descripcion);
}

void ToDo(tarea **array, tarea **array2, int tamanio)
{
    char respuesta[30]; 
    for(int i = 0; i < tamanio; i++){
        mostrarTares(*(array + i));
        fflush(stdin);
        printf("La tarea fue realizada? (Responda S/N) ");
        gets(respuesta);
        
        if(respuesta[0] == 'S' || respuesta[0] == 's'){
            (*(array2 + i)) = (*(array + i)); 
            (*(array + i)) = NULL;
        }else{
            (*(array2 + i)) = NULL;
        }
    }
}

void busquedaPorID(tarea **array, int tamanio)
{
    int id;
    printf("Ingrese el ID de la tarea que desea buscar (ID > 0): ");
    scanf("%d", &id);

    if(id > tamanio){
        printf("El ID ingresado no pertenece a ninguna tarea");
        busquedaPorID(array, tamanio);
    } else{
        printf("\n TAREA BUSCADA POR ID \n");
        mostrarTares(*(array + (id - 1)));
    }
}

void busquedaPorPalabra(tarea **array, int tamanio)
{
    char palabraClave[30];
    char *palabraEncont;
    int coincidencia = 0;

    printf("Ingrese una palabra clave para buscar una tarea: ");
    gets(palabraClave);

    printf("\n TAREA BUSCADA POR PALABRA CLAVE \n");
    for (int i = 0; i < tamanio; i ++){
       
        palabraEncont = strstr((*(array + i))->descripcion, palabraClave);

        if(palabraEncont != NULL){
            mostrarTares((*(array + i)));
            coincidencia++;
        }
    }
    
    if(coincidencia == 0){
        printf("No se encontraron resultados \n");
    }
}
