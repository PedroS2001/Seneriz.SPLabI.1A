#ifndef INFORMES_H_INCLUDED
#define INFORMES_H_INCLUDED



#endif // INFORMES_H_INCLUDED


int filtrarPaisesExitosos(void* pais);
int filtrarPaisesEnElHorno(void* pais);

int ordenarPorNivelDeInfeccion(void* item1, void* item2);
int ordenarPorNivelDeMuertes(void* item1, void* item2);
int paisConMayorNumeroDeMuertos(LinkedList* lista,int (*pFunc)(void*,void*));
