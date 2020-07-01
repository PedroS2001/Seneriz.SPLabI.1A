#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "pais.h"
#include "LinkedList.h"
#include <string.h>


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
    int tamanio = ll_len(pArray);
    int i;
    if(pArray!=NULL)
    {
        if(tamanio > 0)
        {
            printf("  Id                Nombre   Recuperados Infectados Muertos \n");

            for(i = 0; i < tamanio; i++)
            {
                auxiliar = (ePais*)ll_get(pArray, i);
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
