#include<stdio.h>
#include<stdlib.h>
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
<<<<<<< HEAD
Tarea * buscarPorPalabra(Tarea ** lista, int n, char palabra[]);
=======
Tarea * buscarPorIDO(Tarea ** lista, int n, int id);
>>>>>>> BuscaTarea


///////////////////////
///FUNCION PRINCIPAL///
///////////////////////
int main()
{
	//Para que los valores random valuen entre ejecuciones
	srand(time(NULL));
	
	int cantidad;
	Tarea tarea;
	Tarea ** toDo, ** done;
	
	cantidad = pedirCantidad();
	
	toDo = nuevaLista(cantidad);
	done = nuevaLista(cantidad);
	
	
	cargarTareas(toDo, cantidad);
	printf("\n");	
	
<<<<<<< HEAD
	printf("\tBUSCAR UNA TAREA POR PALABRA\n");
	if(buscarPorPalabra(toDo, cantidad, "Comer\0"))
		mostrarTarea(buscarPorPalabra(toDo, cantidad, "Comer\0"));
	else
		printf("La palabra ingresada no se encuentra en ninguna descripcion de la lista de tareas.\n");
	printf("\n");
=======
	printf("\tBUSCAR UNA TAREA POR ID\n");
	if(buscarPorID(toDo, cantidad, 4))
		mostrarTarea(buscarPorID(toDo, cantidad, 4));
	else
		printf("El id ingresado no corresponde con ningun elemento de la lista\n");
>>>>>>> BuscaTarea
	
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

<<<<<<< HEAD
Tarea * buscarPorPalabra(Tarea ** lista, int n, char * palabra)
{	
	for (int i = 0 ; i < n ; i++)
	    if (strstr((lista[i])->Descripcion, palabra))
	        return lista[i];
	
	return NULL;
}

=======
Tarea * buscarPorID(Tarea ** lista, int n, int id)
{
	if (id > n)
		return NULL;
	else
		return lista[id - 1];
}
>>>>>>> BuscaTarea
