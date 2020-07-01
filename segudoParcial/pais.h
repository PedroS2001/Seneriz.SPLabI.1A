#ifndef PAIS_H_INCLUDED
#define PAIS_H_INCLUDED
#include "LinkedList.h"


typedef struct
{
    int id;
    char nombre[20];
    int recuperados;
    int infectados;
    int muertos;
}ePais;


#endif // PAIS_H_INCLUDED


ePais* pais_new();
ePais* pais_newParametros(char* id,char* nombre,char* recuperados, char* infectados, char* muertos);
int controller_loadFromText(char* path, LinkedList* pArray);
int parser_paisFromText(FILE* pFile, LinkedList* pArray);
int controller_ListPaises(LinkedList* pArray);
void mostrarUnPais(ePais* pais);

LinkedList* ll_map(LinkedList* lista, void* (pFunc)(void* element));
LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*));

int controller_saveAsText(char* path, LinkedList* pArray);

void* cargaDatos(void* element );

int filtrarPaisesExitosos(void* pais);
int filtrarPaisesEnElHorno(void* pais);

int ordenarPorNivelDeInfeccion(void* item1, void* item2);
int ordenarPorNivelDeMuertes(void* item1, void* item2);
int paisConMayorNumeroDeMuertos(LinkedList* lista,int (*pFunc)(void*,void*));
