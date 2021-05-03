#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/////////////////
///ESTRUCTURAS///
/////////////////
#define N 50

typedef struct
{
    int TareaID; //Numerado en ciclo iterativo
    char * Descripcion; //
    int Duracion; // entre 10 y 100
} Tarea ;


//////////////////////////////
///DECLARACION DE FUNCIONES///
//////////////////////////////

int pedirCantidad();
//Constructor del tipo Tarea
Tarea ** nuevaLista(int longitud);
void cargarTareas(Tarea ** lista, int n);
void mostrarTarea(Tarea * tarea);
void listarTareas(Tarea ** lista, int n);
void tareasHechas(Tarea ** toDo, Tarea ** done, int n);
//Busca entre la lista una palabra clave en la descripci�n y devuelve la tarea que la contenga
Tarea * buscarPorPalabra(Tarea ** lista, int n, char palabra[]);
//Busca en la lista el ID ingresado como parametro y devuelve el elemento que lo contenga
Tarea * buscarPorID(Tarea ** lista, int n, int id);
void liberarMemoria(Tarea ** lista, int n);


///////////////////////
///FUNCION PRINCIPAL///
///////////////////////
int main()
{
	//Para que los valores random valuen entre ejecuciones
	srand(time(NULL));
	
	int cantidad;
	char palabra[N];
	int ID;
	Tarea tarea;
	Tarea ** toDo, ** done;
	
	cantidad = pedirCantidad();
	
	toDo = nuevaLista(cantidad);
	done = nuevaLista(cantidad);
	
	
	cargarTareas(toDo, cantidad);
	printf("\n");	
	
	printf("\tBUSCAR UNA TAREA POR PALABRA\n");
	printf("Ingrese la palabra clave de la tarea que quiere buscar: \n");
	scanf(" %s", palabra);
	if(buscarPorPalabra(toDo, cantidad, palabra))
		mostrarTarea(buscarPorPalabra(toDo, cantidad, palabra));
	else
		printf("La palabra ingresada no se encuentra en ninguna descripcion de la lista de tareas.\n");
	printf("\n");

	printf("\tBUSCAR UNA TAREA POR ID\n");
	printf("Ingrese el ID de la tarea que quiere buscar: (entre 1 y %d)\n", cantidad);
	scanf(" %d", &ID);
	if(buscarPorID(toDo, cantidad, ID))
		mostrarTarea(buscarPorID(toDo, cantidad, ID));
	else
		printf("El id ingresado no corresponde con ningun elemento de la lista\n");
	printf("\n");	
	
	printf("\tLISTADO DE TAREAS POR HACER\n");
	listarTareas(toDo, cantidad);
	printf("\n");
	
	printf("\tINDICAR LAS TAREAS REALIZADAS\n");
	tareasHechas(toDo, done, cantidad);
	printf("\n");
	printf("\tTareas terminadas\n");
	listarTareas(done, cantidad);
	printf("\n");
	printf("\tTareas pendientes\n");
	listarTareas(toDo, cantidad);
	
	liberarMemoria(toDo, cantidad);
	liberarMemoria(done, cantidad);

    return 0;
}

///////////////////////////
///FUNCIONES SECUNDARIAS///
///////////////////////////
int pedirCantidad ()
{
	int n;
	
	do{
		printf("Ingrese el numero de tareas a realizar: \n");
		scanf(" %u", &n);
		fflush(stdin);
		if (n < 1)
			printf("Error, ingrese nuevamente.\n");
	} while(n < 1);
	
	return n;
}


Tarea ** nuevaLista(int longitud)
{
	Tarea ** lista = (Tarea **) malloc(sizeof(Tarea *) * longitud);
	
	for(int i = 0 ; i < longitud ; i++)
		lista[i] = NULL;

	return lista;
}

void cargarTareas(Tarea ** lista, int n)
{
	for (int i = 0 ; i < n ; i++)
	{
		printf("\tTarea Nro %d\n", (i + 1));
		lista[i] = (Tarea *) malloc(sizeof(Tarea *));
		(lista[i])->TareaID = i + 1;
		(lista[i])->Duracion = 1 + rand() % 10;
		(lista[i])->Descripcion = (char *) malloc(sizeof(char)*N);
		printf("Ingrese una breve descripci? de la tarea:\n");
		gets((lista[i])->Descripcion);
	}
}

void mostrarTarea(Tarea * tarea)
{
	if(tarea)
	{
		printf("ID: %d\n", tarea->TareaID);
		printf("Descripcion: %s\n", tarea->Descripcion);
		printf("Duracion: %dHs\n", tarea->Duracion);
		printf("\n");		
	}
}

void listarTareas(Tarea ** lista, int n)
{
	for(int i = 0 ; i < n ; i++)
		mostrarTarea(lista[i]);
}

void tareasHechas(Tarea ** toDo, Tarea ** done, int n)
{
	char ask;
	
	for(int i = 0 ; i < n ; i++)
	{
		printf("\tTarea Nro %d\n", (i + 1));
		mostrarTarea(toDo[i]);
		printf("?Ya realizo la tarea? (S/N)\n");
		scanf(" %c", &ask);
		
		if(ask == 's' || ask == 'S')
		{
			done[i] = toDo[i];
			toDo[i] = NULL;
			printf("\t%d\n", (done[i])->TareaID);
		}
	}
}

Tarea * buscarPorPalabra(Tarea ** lista, int n, char * palabra)
{	
	for (int i = 0 ; i < n ; i++)
	    if (strstr((lista[i])->Descripcion, palabra))
	        return lista[i];
	
	return NULL;
}

Tarea * buscarPorID(Tarea ** lista, int n, int id)
{
	if (id > n)
		return NULL;
	else
		return lista[id - 1];
}

void liberarMemoria(Tarea ** lista, int n)
{
	for (int i = 0 ; i < n ; i++)
	{
		if(lista[i])
			free((lista[i])->Descripcion);
		free(lista[i]);
	}
	free(lista);
}
