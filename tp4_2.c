#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/////////////////
///ESTRUCTURAS///
/////////////////
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
Tarea * buscarTarea(Tarea ** lista, int n, int id);


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
	
	printf("\tBUSCAR UNA TAREA POR ID\n");
	if(buscarTarea(toDo, cantidad, 4))
		mostrarTarea(buscarTarea(toDo, cantidad, 4));
	else
		printf("El id ingresado no corresponde con ningun elemento de la lista\n");
	
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
	{
		lista[i] = NULL;
	}
	
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
		(lista[i])->Descripcion = (char *) malloc(sizeof(char)*50);
		printf("Ingrese una breve descripci�n de la tarea:\n");
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
	{
		mostrarTarea(lista[i]);
	}
}

void tareasHechas(Tarea ** toDo, Tarea ** done, int n)
{
	char ask;
	
	for(int i = 0 ; i < n ; i++)
	{
		printf("\tTarea Nro %d\n", (i + 1));
		mostrarTarea(toDo[i]);
		printf("�Ya realizo la tarea? (S/N)\n");
		scanf(" %c", &ask);
		
		if(ask == 's' || ask == 'S')
		{
			done[i] = toDo[i];
			toDo[i] = NULL;
			printf("\t%d\n", (done[i])->TareaID);
		}
	}
}

Tarea * buscarTarea(Tarea ** lista, int n, int id)
{
	if (id > n)
		return NULL;
	else
		return lista[id - 1];
}
