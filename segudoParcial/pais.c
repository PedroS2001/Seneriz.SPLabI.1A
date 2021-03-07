#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "pais.h"
#include "LinkedList.h"
#include <string.h>

static int isValidName(char* cadena,int longitud);
/**
 * \brief Verifica si la cadena ingresada es un nombre valido
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
static int isValidName(char* cadena,int longitud)
{
    int i=0;
    int retorno = 1;

    if(cadena != NULL && longitud > 0)
    {
        for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
        {
            if(      (cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' )      )
            {
                if( !(cadena[i] == ' '))
                {
                    retorno = 0;
                }
                break;
            }
        }
    }
    return retorno;
}

ePais* pais_new()
{
    ePais* auxiliarP;
    auxiliarP = (ePais*) malloc(sizeof(ePais));
    return auxiliarP;
}

ePais* pais_newParametros(char* idStr,char* nombreStr,char* recuperadosStr, char* infectadosStr, char* muertosStr)
{
    ePais* this;
    int id;
    char nombre[20];
    int recuperados;
    int infectados;
    int muertos;

    this = pais_new();
    if(this != NULL && idStr != NULL && nombreStr != NULL && recuperadosStr != NULL && infectadosStr != NULL && muertosStr != NULL)
    {
        id = atoi(idStr);
        recuperados = atoi(recuperadosStr);
        infectados = atoi(infectadosStr);
        muertos = atoi(muertosStr);
        strcpy(nombre,nombreStr);

        /*
                this->id = atoi(id);
                strcpy(this->nombre,nombre);
                this->recuperados = atoi(recuperados);
                this->infectados = atoi(infectados);
                this->muertos = atoi(muertos);
        */

        pais_setId(this,id);
        pais_setRecuperados(this,recuperados);
        pais_setInfectados(this,infectados);
        pais_setMuertos(this,muertos);
        pais_setNombre(this,nombre);

    }

    return this;
}


/**SETTERS Y GETTERS*/

int pais_setId(ePais* this,int id)
{
    int retorno = -1;
    if(this != NULL && id >= 0)
    {
        retorno = 0;
        this->id = id;
    }
    return retorno;
}
int pais_setInfectados(ePais* this,int infectados)
{
    int retorno = -1;
    if(this != NULL && infectados >= 0)
    {
        retorno = 0;
        this->infectados = infectados;
    }
    return retorno;
}
int pais_setRecuperados(ePais* this,int recuperados)
{
    int retorno = -1;
    if(this != NULL && recuperados >= 0)
    {
        retorno = 0;
        this->recuperados = recuperados;
    }
    return retorno;
}
int pais_setMuertos(ePais* this,int muertos)
{
    int retorno = -1;
    if(this != NULL && muertos >= 0)
    {
        retorno = 0;
        this->muertos = muertos;
    }
    return retorno;
}

int pais_setNombre(ePais* this,char* nombre)
{
    int retorno = -1;
    if(this != NULL && nombre != NULL)
    {
        if(isValidName(nombre,25))
        {
            retorno = 0;
            strncpy(this->nombre, nombre,25);
        }
    }
    return retorno;
}

int pais_getNombre(ePais* this,char* nombre)
{
    int retorno = -1;
    if(this != NULL && nombre != NULL)
    {
        retorno = 0;
        strcpy(nombre, this->nombre);
    }
    return retorno;
}

int pais_getId(ePais* this,int* id)
{
    int retorno = -1;
    if(this != NULL && id != NULL)
    {
        retorno = 0;
        *id = this->id;
    }
    return retorno;
}
int pais_getInfectados(ePais* this,int* infectados)
{
    int retorno = -1;
    if(this != NULL && infectados != NULL)
    {
        retorno = 0;
        *infectados = this->infectados;
    }
    return retorno;
}
int pais_getRecuperados(ePais* this,int* recuperados)
{
    int retorno = -1;
    if(this != NULL && recuperados != NULL)
    {
        retorno = 0;
        *recuperados = this->recuperados;
    }
    return retorno;
}
int pais_getMuertos(ePais* this,int* muertos)
{
    int retorno = -1;
    if(this != NULL && muertos != NULL)
    {
        retorno = 0;
        *muertos = this->muertos;
    }
    return retorno;
}


/******************************************/



/** \brief muestra los datos de un solo pais
 *
 * \param el pais
 * \param
 * \return
 *
 */

void mostrarUnPais(ePais* pais)
{
    int id;
    char nombre[20];
    int recuperados;
    int infectados;
    int muertos;

    pais_getId(pais,&id);
    pais_getRecuperados(pais,&recuperados);
    pais_getInfectados(pais,&infectados);
    pais_getMuertos(pais,&muertos);
    pais_getNombre(pais,nombre);
    printf("%4d  %20s   %8d    %8d%  8d\n",id, nombre, recuperados, infectados, muertos);
}

/** \brief carga los datos de los elementos con los valores asignados
 *
 * \param elemento al que carga el valor
 */

void* cargaDatos(void* element )
{
    ePais* retorno = element;
    int id;
    char nombre[20];
    int infectados;
    int recuperados;
    int muertos;

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


