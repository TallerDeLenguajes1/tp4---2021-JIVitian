#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/////////////////
///ESTRUCTURAS///
/////////////////
#define N 100

typedef struct Tarea
{
    int TareaID; //Numerado en ciclo iterativo
    char * Descripcion; //
    int Duracion; // entre 10 y 100
} Tarea ;

typedef struct Nodo Nodo;

typedef struct Nodo 
{
	Tarea T;
	Nodo * Siguiente;
} Nodo ;


//////////////////////////////
///DECLARACION DE FUNCIONES///
//////////////////////////////

int pedirCantidad();
//Constructor del tipo Tarea
Nodo * nuevaLista();
Tarea CrearTarea(int id);
Nodo * CrearNodo(Tarea tarea);
void InsertarEnLista(Nodo ** Lista, Nodo * nodo);
void mostrarTarea(Nodo * nodo);
void listarTareas(Nodo ** Lista);
void tareasHechas(Nodo ** toDo, Nodo ** done);
//Busca entre la lista una palabra clave en la descripcion y devuelve la tarea que la contenga
Nodo * buscarPorPalabra(Nodo ** lista, char palabra[]);
//Busca en la lista el ID ingresado como parametro y devuelve el elemento que lo contenga
Nodo * buscarPorID(Nodo ** lista, int id);
void liberarMemoria(Nodo ** lista);

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
	Nodo * toDo, * done;
	
	cantidad = pedirCantidad();
	
	toDo = nuevaLista();
	done = nuevaLista();
	
	for (int i = 0 ; i < cantidad ; i++)
	{
		InsertarEnLista(&toDo, CrearNodo(CrearTarea(i + 1)));
		printf("\n");	
	}
	
	printf("\tLISTADO DE TAREAS POR HACER\n");
	listarTareas(&toDo);
	printf("\n");

	printf("\tBUSCAR UNA TAREA POR PALABRA\n");
	printf("Ingrese la palabra clave de la tarea que quiere buscar: \n");
	scanf(" %s", palabra);
	printf("\n");
	if(buscarPorPalabra(&toDo, palabra)){
		printf("\t\tTarea Encontrada:\n");
		mostrarTarea(buscarPorPalabra(&toDo, palabra));
	}
	else
		printf("La palabra ingresada no se encuentra en ninguna descripcion de la lista de tareas.\n");
	printf("\n");

	printf("\tBUSCAR UNA TAREA POR ID\n");
	printf("Ingrese el ID de la tarea que quiere buscar: (entre 1 y %d)\n", cantidad);
	scanf(" %d", &ID);
	printf("\n");
	if(buscarPorID(&toDo, ID)){
		printf("\t\tTarea Encontrada:\n");
		mostrarTarea(buscarPorID(&toDo, ID));
	}		
	else
		printf("El id ingresado no corresponde con ningun elemento de la lista\n");
	printf("\n");
	
	printf("\tINDICAR LAS TAREAS REALIZADAS\n");
	tareasHechas(&toDo, &done);
	printf("\n");
	printf("\tTareas terminadas\n");
	listarTareas(&done);
	printf("\n");
	printf("\tTareas pendientes\n");
	listarTareas(&toDo);

	liberarMemoria(&toDo);
	liberarMemoria(&done);

	getchar();
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

Nodo * nuevaLista()
{	
	return NULL;
}

Tarea CrearTarea(int id)
{
	Tarea tarea;
	
	printf("\tTarea Nro %d\n", id);
	tarea.TareaID = id;
	tarea.Duracion = 1 + rand() % 10;
	tarea.Descripcion = (char *) malloc(sizeof(char)*N);
	printf("Ingrese una breve descripci? de la tarea:\n");
	gets(tarea.Descripcion);
	
	return tarea;
}

Nodo * CrearNodo(Tarea tarea)
{
	Nodo * NNodo = (Nodo *) malloc (sizeof(Nodo));
	NNodo->T = tarea;
	NNodo->Siguiente = NULL;
	
	return NNodo;
}

void InsertarEnLista(Nodo ** Lista, Nodo * nodo)
{
	if (*Lista) 
	{
		Nodo * aux = *Lista;
		while (aux->Siguiente)
			aux = aux->Siguiente;
		aux->Siguiente = nodo;
	}
	else
	{
		*Lista = nodo;	
	}
}

void mostrarTarea(Nodo * nodo)
{
	if(nodo)
	{
		printf("ID: %d\n", nodo->T.TareaID);
		printf("Descripcion: %s\n", nodo->T.Descripcion);
		printf("Duracion: %dHs\n", nodo->T.Duracion);
		printf("\n");		
	}
}

void listarTareas(Nodo ** Lista)
{
	Nodo * aux = *Lista;
	while (aux)
	{
		mostrarTarea(aux);
		aux = aux->Siguiente;
	}
		
}

void tareasHechas(Nodo ** toDo, Nodo ** done)
{
	char ask;
	Nodo * aux = *toDo;
	Nodo * anterior = NULL;
	
	while (aux)
	{
		printf("\tTarea Nro %d\n", aux->T.TareaID);
		mostrarTarea(aux);
		printf("?Ya realizo la tarea? (S/N)\n");
		scanf(" %c", &ask);
		
		if(ask == 's' || ask == 'S')
		{
			//Es el primer elemento
			if(!anterior)
			{
				InsertarEnLista(done, aux);
				*toDo = (*toDo)->Siguiente;
				aux->Siguiente = NULL;
				aux = *toDo;
			}
			//Es un elemento cualquiera
			else
			{
				InsertarEnLista(done, aux);
				anterior->Siguiente = aux->Siguiente;
				aux->Siguiente = NULL;
				aux = anterior->Siguiente;
			}
		}
		else
		{
			anterior = aux;
			aux = aux->Siguiente;
		}
	}
}

Nodo * buscarPorPalabra(Nodo ** lista, char * palabra)
{	
	Nodo * aux = *lista;
	while (aux)
	{
	    if (strstr(aux->T.Descripcion, palabra))
	        return aux;
	    aux = aux->Siguiente;
	}
	
	return NULL;
}

Nodo * buscarPorID(Nodo ** lista, int id)
{
	Nodo * aux = *lista;
	while (aux)
	{
		if (aux->T.TareaID == id)
			return aux;
		aux = aux->Siguiente;
	}
	return NULL;
}

void liberarMemoria(Nodo ** lista)
{
	Nodo * aux;
	
	while (*lista)
	{
		free((*lista)->T.Descripcion);
		aux = *lista;
		*lista = (*lista)->Siguiente;
		free(aux);
	}
}
	