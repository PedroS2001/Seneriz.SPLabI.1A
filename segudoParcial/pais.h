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

int pais_setId(ePais* this,int id);
int pais_setInfectados(ePais* this,int infectados);
int pais_setRecuperados(ePais* this,int recuperados);
int pais_setMuertos(ePais* this,int muertos);
int pais_setNombre(ePais* this,char* nombre);
int pais_getId(ePais* this,int* id);
int pais_getInfectados(ePais* this,int* infectados);
int pais_getRecuperados(ePais* this,int* recuperados);
int pais_getMuertos(ePais* this,int* muertos);
int pais_getNombre(ePais* this,char* nombre);

void mostrarUnPais(ePais* pais);

void* cargaDatos(void* element );
