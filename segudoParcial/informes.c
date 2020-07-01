#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "pais.h"
#include "LinkedList.h"
#include <string.h>


int filtrarPaisesExitosos(void* pais)
{
    int retorno = -1;
    ePais* auxPais;
    if(pais != NULL)
    {
        auxPais = pais;
        if(auxPais->muertos < 5000)
        {
            retorno = 0;
        }
    }
    return retorno;
}

int filtrarPaisesEnElHorno(void* pais)
{
    int retorno = -1;
    ePais* auxPais;
    int infectados;
    if(pais != NULL)
    {
        auxPais = pais;
        infectados = auxPais->infectados;
        infectados = infectados/3;
        if(infectados > auxPais->recuperados)
        {
            retorno = 0;
        }
    }
    return retorno;
}

int ordenarPorNivelDeInfeccion(void* item1, void* item2)
{
    int retorno;
    ePais* pais1;
    ePais* pais2;

        pais1 = item1;
        pais2 = item2;

        if(pais1->infectados > pais2->infectados)
        {
            retorno = 1;
        }
        else if(pais1->infectados < pais2->infectados)
        {
            retorno = -1;
        }
        else
        {
            retorno = 0;
        }

    return retorno;
}

int paisConMayorNumeroDeMuertos(LinkedList* lista,int (*pFunc)(void*,void*))
{
    int retorno = -1;
    if(lista != NULL)
    {
        retorno = 0;
        ePais* masMuertes;
        LinkedList* listaAuxiliar = ll_subList(lista,0,ll_len(lista));
        ll_sort(listaAuxiliar,pFunc,1);
        masMuertes = ll_get(listaAuxiliar,ll_len(listaAuxiliar)-1);
        printf("EL PAIS CON MAYOR NUMERO DE MUERTES ES : \n");
        printf("  Id                Nombre   Recuperados Infectados Muertos \n");
        mostrarUnPais(masMuertes);
    }
    return retorno;
}

int ordenarPorNivelDeMuertes(void* item1, void* item2)
{
    int retorno;
    ePais* pais1;
    ePais* pais2;

        pais1 = item1;
        pais2 = item2;

        if(pais1->muertos > pais2->muertos)
        {
            retorno = 1;
        }
        else if(pais1->muertos < pais2->muertos)
        {
            retorno = -1;
        }
        else
        {
            retorno = 0;
        }

    return retorno;
}
