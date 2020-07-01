#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utn.h"
#include "pais.h"
#include "LinkedList.h"
#include "informes.h"
#include "parsers.h"

int menu();


int main()
{
    srand (time(NULL));
    int opcion;
    char nombreArchivo[20];
    int carga = 0;
    LinkedList* listaPaises = ll_newLinkedList();
    LinkedList* listaCargada;
    LinkedList* listaPaisesExitosos;
    LinkedList* listaPaisesEnElHorno;

    do
    {
        opcion = menu();
        switch(opcion)
        {
        case 1:
            if(!carga)
            {
                carga = 1;
                utn_getNombre(nombreArchivo,20,"Ingrese el nombre del archivo .csv(sin extension) que quiere cargar: ","Archivo invalido\n",2);
                if(nombreArchivo != NULL)
                {
                    strcat(nombreArchivo,".csv");
                    if(!controller_loadFromText(nombreArchivo,listaPaises))
                    {
                        printf("\nArchivo cargado con exito\n");
                    }
                    else
                    {
                        printf("Error al cargar el archivo\n");
                    }
                }
            }
            else
            {
                printf("Ya se ha cargado el archivo antes\n");
            }
            break;
        case 2:
            if(!ll_isEmpty(listaPaises))
            {
                controller_ListPaises(listaPaises);
            }
            else
            {
                printf("La lista esta vacia\n");
            }
            break;
        case 3:
            if(!ll_isEmpty(listaPaises))
            {
                listaCargada = ll_map(listaPaises,cargaDatos);
                if(listaCargada!= NULL)
                {
                    printf("\nSe cargaron los datos correctamente\n");
                }
            }
            break;
        case 4:
            if(!ll_isEmpty(listaPaises))
            {
                listaPaisesExitosos = ll_filter(listaPaises,filtrarPaisesExitosos);
                if(listaPaisesExitosos != NULL && !ll_isEmpty(listaPaisesExitosos))
                {
                    if(!controller_saveAsText("exitosos.csv",listaPaisesExitosos))
                    {
                        printf("Se guardaron los datos de paises exitosos en el archivo \"exitosos.csv\"\n");
                    }
                }
            }

            break;
        case 5:
            if(!ll_isEmpty(listaPaises))
            {
                listaPaisesEnElHorno = ll_filter(listaPaises,filtrarPaisesEnElHorno);
                if(listaPaisesEnElHorno != NULL && !ll_isEmpty(listaPaisesEnElHorno))
                {
                    if(!controller_saveAsText("enelhorno.csv",listaPaisesEnElHorno))
                    {
                        printf("Se guardaron los datos de paises en el horno en el archivo \"enelhorno.csv\"\n");
                    }
                }
                else
                {
                    printf("No hay paises en el horno\n");
                }
            }
            break;
        case 6:
            if(!ll_isEmpty(listaPaises) && !ll_sort(listaPaises,ordenarPorNivelDeInfeccion,1))
            {
                printf("\nPaises ordenados por nivel de infeccion\n");
            }
            break;
        case 7:
            if(!ll_isEmpty(listaPaises))
            {
                paisConMayorNumeroDeMuertos(listaPaises,ordenarPorNivelDeMuertes);
            }
            break;
        case 8:
            printf("\nESTA SALIENDO\n\n");
            break;
        }


        system("pause");
        system("cls");
    }
    while(opcion!= 8);



    return 0;
}

int menu()
{
    int respuesta;
    printf("1) Cargar archivo\n");
    printf("2) Imprimir lista\n");
    printf("3) Asignar estadisticas\n");
    printf("4) Filtrar por paises exitosos\n");
    printf("5) Filtrar por paises en el horno\n");
    printf("6) Ordenar por nivel de infeccion\n");
    printf("7) Mostrar pais mas castigado\n");
    printf("8) Salir\n");
    utn_getNumero(&respuesta,"Ingrese opcion: ", "Opcion invalida\n",1,8,2 );

    return respuesta;
}
