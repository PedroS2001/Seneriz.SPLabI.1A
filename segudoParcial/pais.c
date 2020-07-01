#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "pais.h"
#include "LinkedList.h"
#include <string.h>

ePais* pais_new()
{
    ePais* auxiliarP;
    auxiliarP = (ePais*) malloc(sizeof(ePais));
    return auxiliarP;
}

ePais* pais_newParametros(char* id,char* nombre,char* recuperados, char* infectados, char* muertos)
{
    ePais* this;
    this = pais_new();
    if(this != NULL && id != NULL && nombre != NULL && recuperados != NULL && infectados != NULL && muertos != NULL)
    {
        this->id = atoi(id);
        strcpy(this->nombre,nombre);
        this->recuperados = atoi(recuperados);
        this->infectados = atoi(infectados);
        this->muertos = atoi(muertos);
    }
    return this;
}


int controller_loadFromText(char* path, LinkedList* pArray)
{
    int retorno = -1;
    FILE *pArchivo;

    if((pArchivo = fopen(path, "r"))!=NULL)
    {
        retorno = 0;
        parser_paisFromText(pArchivo, pArray);
    }
    else
    {
        printf("No se pudo leer\n");
    }
    return retorno;
}

int parser_paisFromText(FILE* pFile, LinkedList* pArray)
{
    int retorno = -1;
    ePais* auxiliar = pais_new();
    char buffer[5][20];

    if(pFile != NULL && pArray != NULL)
    {
        fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);//para no copiar la cabecera
        do
        {
            if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]) == 5)
            {
                auxiliar = pais_newParametros(buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
                if(auxiliar != NULL)
                {
                    ll_add(pArray,auxiliar);
                }
            }
        }
        while(!feof(pFile));
        retorno = 0;
    }
    else
    {
        printf("No se pudo abrir el archivo\n");
    }

    return retorno;
}

int controller_ListPaises(LinkedList* pArray)
{
    ePais* auxiliar;
    int retorno = -1;
    /*int id;
    char nombre[128];
    int recuperados;
    int infectados;
    int muertos;
    */int tamanio = ll_len(pArray);
    int i;
    if(pArray!=NULL)
    {
        if(tamanio > 0)
        {
            printf("  Id                Nombre   Recuperados Infectados Muertos \n");

            for(i = 0; i < tamanio; i++)
            {
                auxiliar = (ePais*)ll_get(pArray, i);
                /*id = auxiliar->id ;
                strcpy(nombre,auxiliar->nombre);
                recuperados = auxiliar->recuperados;
                infectados = auxiliar->infectados;
                muertos = auxiliar->muertos;

                printf("%4d  %20s %8d    %8d%8d\n",id, nombre, recuperados, infectados, muertos);
*/
               mostrarUnPais(auxiliar);
            }
            retorno = 0;
        }
        else
        {
            printf("No se cargaron los datos\n");
        }
    }
    else
    {
        printf("LISTA VACIA\n");
    }
    return retorno;
}

void mostrarUnPais(ePais* pais)
{
    printf("%4d  %20s   %8d    %8d%  8d\n",pais->id, pais->nombre, pais->recuperados, pais->infectados, pais->muertos);
}


LinkedList* ll_map(LinkedList* lista, void* (pFunc)(void* element)  )
{
    LinkedList* listanueva = ll_newLinkedList();
    int i;
    void* nuevoPais;
    ePais* retorno;
    int tam = ll_len(lista);

    for(i=0; i<tam; i++)
    {
        retorno = ll_get(lista,i);
        nuevoPais = pFunc(retorno);
        ll_add(listanueva,nuevoPais);
    }
    return listanueva;
}

void* cargaDatos(void* element )
{
    ePais* retorno = element;

    if(element != NULL)
    {
        retorno->id = retorno->id;
        strcpy(retorno->nombre,retorno->nombre);
        retorno->infectados = rand()%(1960000)+40000;
        retorno->recuperados = rand()%(50000)+50000;
        retorno->muertos = rand()%(49000)+1000;

    }
    return retorno;
}



LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*))
{
    int i;
    LinkedList* listaFiltrada = NULL;
    if(this != NULL && pFunc != NULL)
    {
        listaFiltrada = ll_newLinkedList();
        if(listaFiltrada != NULL)
        {
            for(i=0; i<ll_len(this); i++)
            {
                if(!pFunc(ll_get(this,i)))
                {
                    ll_add(listaFiltrada,ll_get(this,i));
                }
            }
        }
    }
    return listaFiltrada;
}
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


int controller_saveAsText(char* path, LinkedList* pArray)
{
    int retorno = -1;
    int i;
    FILE* fpArchivo;

    int len = ll_len(pArray);
    ePais* auxiliar;
/*
    int id;
    char nombre[50];
    int recuperados;
    int infectados;
    int muertos;
*/
    if(pArray != NULL && path != NULL)
    {
        fpArchivo = fopen(path,"w");
        if(fpArchivo != NULL)
        {
            fprintf(fpArchivo,"id,nombre,recuperados,infectados,muertos\n"); //para volver a copiar la cabecera
            retorno = 0;
            for (i=0; i<len ; i++)
            {
                auxiliar = ll_get(pArray, i);
                    fprintf(fpArchivo,"%d,%s,%d,%d,%d\n",auxiliar->id,auxiliar->nombre,auxiliar->recuperados,auxiliar->infectados,auxiliar->muertos);
            }
            fclose(fpArchivo);
        }
    }
    return retorno;
}
