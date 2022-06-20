#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "CLIENTES.h"
#include "CONSUMOS.h"
#include "MENU.h"
#include "gotoxy.h"
#include "windows.h"

#define ESC 27
#define DIM_CONSUMOS 500
#define DIM_CLIENTES 100
#define ARCHIVO_CLIENTES "clientes.bin"
#define ARCHIVO_CONSUMOS "consumos.bin"

void muestraMenu(){

    system("cls");
    replicachar('-', 30);
    printf("\nMENU PRINCIPAL\n");
    replicachar('-', 30);
    printf("\nElija la opcion que desee:\n");
    printf("\n1-CLIENTES");
    printf("\n2-CONSUMOS");
    printf("\n\nPresione ESC para salir");
}

void menuClientes(){
    char opcion= 0;
    char dni[30];
    int idcl = buscaUltimoIdClientes(ARCHIVO_CLIENTES);

    do{
        system("cls");
        color(3);
        printf("\n CLIENTES \n");
        printf("\n1-Alta");
        printf("\n2-Baja");
        printf("\n3-Modificacion");
        printf("\n4-Consulta");
        printf("\n5-Listado");
        printf("\n\nPresione ESC para volver al menu principal\n");

        opcion = getch();

        switch(opcion){
            case 49:
                system("cls");
                cargaArchivoClientes(ARCHIVO_CLIENTES, idcl);
                break;
            case 50:
                printf("Ingrese el DNI del cliente que desea dar de baja:");
                fflush(stdin);
                gets(dni);
                bajaDeCliente(ARCHIVO_CLIENTES, dni);
                break;
            case 51:
                menuModificacionClientes();
                break;
            case 52:
                menuConsultaClientes();
                break;
            case 53:
                menuListadoClientes();
                break;
        }

    }while(opcion!= ESC);
}

void menuConsumos(){
    char opcion = 0;
    int idco = buscaUltimoIdConsumos(ARCHIVO_CONSUMOS);
    int id;

    do{
        system("cls");
        color(3);
        printf("\n CONSUMOS \n");
        printf("\n1-Alta");
        printf("\n2-Baja");
        printf("\n3-Modificacion");
        printf("\n4-Consulta");
        printf("\n\nPresione ESC para volver al menu principal\n");

        opcion = getch();

        switch(opcion){
            case 49:
                system("cls");
                cargaArchivoConsumos(ARCHIVO_CONSUMOS, idco);
                break;
            case 50:
                system("cls");
                printf("Ingrese el ID del consumo que desea dar de baja:");
                scanf("%d", &id);
                bajaDeConsumo(ARCHIVO_CONSUMOS, id);
                break;
            case 51:
                menuModificacionConsumos();
                break;
            case 52:
                menuConsultaConsumos();
                break;
        }

    }while(opcion!= ESC);
}

void menuModificacionClientes(){
    char opcion2 = 0;
    char dni[10];

    system("cls");
    printf("Ingrese el DNI del cliente que desea modificar:");
    fflush(stdin);
    gets(dni);

    consultaXDni(ARCHIVO_CLIENTES, dni);
    system("pause");

    do{
        system("cls");
        color(3);
        printf("\n MODIFICACION CLIENTES \n");
        printf("\n1-Nombre");
        printf("\n2-Apellido");
        printf("\n3-DNI");
        printf("\n4-Email");
        printf("\n5-Domicilio");
        printf("\n6-Movil");
        printf("\n\nPresione ESC para volver al menu de clientes\n");

        opcion2 = getch();

        switch(opcion2){
            case 49:
                modificaCliente(ARCHIVO_CLIENTES, dni, 1);
                break;
            case 50:
                modificaCliente(ARCHIVO_CLIENTES, dni, 2);
                break;
            case 51:
                modificaCliente(ARCHIVO_CLIENTES, dni, 3);
                break;
            case 52:
                modificaCliente(ARCHIVO_CLIENTES, dni, 4);
                break;
            case 53:
                modificaCliente(ARCHIVO_CLIENTES, dni, 5);
                break;
            case 54:
                modificaCliente(ARCHIVO_CLIENTES, dni, 6);
                break;
        }

    }while(opcion2!= ESC);
}

void menuModificacionConsumos(){
    char opcion2 = 0;
    int id;

    system("cls");
    printf("Ingrese el ID del consumo que desea modificar:");
    scanf("%d", &id);

    consultaConsumoXId(ARCHIVO_CONSUMOS, id);
    system("pause");

    do{
        system("cls");
        color(3);
        printf("\n MODIFICACION CONSUMOS \n");
        printf("\n1-ID Cliente");
        printf("\n2-Anio");
        printf("\n3-Mes");
        printf("\n4-Dia");
        printf("\n5-Datos Consumidos");
        printf("\n\nPresione ESC para volver al menu de consumos\n");

        opcion2 = getch();

        switch(opcion2){
            case 49:
                modificaConsumos(ARCHIVO_CONSUMOS, id, 1);
                break;
            case 50:
                modificaConsumos(ARCHIVO_CONSUMOS, id, 2);
                break;
            case 51:
                modificaConsumos(ARCHIVO_CONSUMOS, id, 3);
                break;
            case 52:
                modificaConsumos(ARCHIVO_CONSUMOS, id, 4);
                break;
            case 53:
                modificaConsumos(ARCHIVO_CONSUMOS, id, 5);
                break;
        }

    }while(opcion2!= ESC);
}

void menuConsultaConsumos(){
    char opcion2 = 0;
    stConsumos consumosPorCliente [DIM_CONSUMOS];
    stConsumos consumosPorFecha [DIM_CONSUMOS];
    char dni[10];
    int vConsumosCliente;
    int vConsumosFecha;
    int idconsumo;
    int idcliente;
    int anio;
    int mes;
    int dia;

    do{
        system("cls");
        color(3);
        printf("\n CONSULTA DE CONSUMOS \n");
        printf("\n1-Por ID de Consumo");
        printf("\n2-Por ID de Cliente");
        printf("\n3-Por DNI de Cliente");
        printf("\n4-Por Fecha");
        printf("\n5-Todos los Consumos");
        printf("\n\nPresione ESC para volver al menu de consumos\n");

        opcion2 = getch();
        system("cls");

        switch(opcion2){
            case 49:
                printf("Ingrese el ID del consumo:");
                scanf("%d", &idconsumo);
                consultaConsumoXId(ARCHIVO_CONSUMOS, idconsumo);
                system("pause");
                break;
            case 50:
                printf("Ingrese el ID del cliente:");
                scanf("%d", &idcliente);
                vConsumosCliente=0;

                if(buscaIdClienteConsumos(ARCHIVO_CONSUMOS, idcliente)==1){
                    vConsumosCliente=archi2arregloConsumosDeCliente(ARCHIVO_CONSUMOS, consumosPorCliente, DIM_CONSUMOS, idcliente);
                    ordenaArregloPorFecha(consumosPorCliente, vConsumosCliente);
                    muestraArregloConsumos(consumosPorCliente, vConsumosCliente);
                }else{
                    printf("\nEl cliente no tiene consumos\n\n");
                }

                system("pause");

                break;
            case 51:
                printf("Ingrese el DNI del cliente:");
                fflush(stdin);
                gets(dni);
                idcliente = retornaNroClientePorDni(ARCHIVO_CLIENTES, dni);
                vConsumosCliente=0;

                if(buscaIdClienteConsumos(ARCHIVO_CONSUMOS, idcliente)==1){
                    vConsumosCliente=archi2arregloConsumosDeCliente(ARCHIVO_CONSUMOS, consumosPorCliente, DIM_CONSUMOS, idcliente);
                    ordenaArregloPorFecha(consumosPorCliente, vConsumosCliente);
                    muestraArregloConsumos(consumosPorCliente, vConsumosCliente);
                }else{
                    printf("\nEl cliente no tiene consumos\n");
                }

                system("pause");

                break;
            case 52:
                printf("Ingrese el anio:");
                scanf("%d", &anio);
                printf("Ingrese el mes:");
                scanf("%d", &mes);
                printf("Ingrese el dia:");
                scanf("%d", &dia);
                vConsumosFecha=0;

                if(buscaFechaConsumos(ARCHIVO_CONSUMOS, anio, mes, dia)==1){
                    vConsumosFecha=arregloConsumosDeFecha(ARCHIVO_CONSUMOS, consumosPorFecha, DIM_CONSUMOS, anio, mes, dia);
                    muestraArregloConsumos(consumosPorFecha, vConsumosFecha);
                }else{
                    printf("\nNo hay consumos de esa fecha\n");
                }
                system("pause");

                break;
            case 53:
                muestraArchivoConsumos(ARCHIVO_CONSUMOS);
                system("pause");
                break;

        }
    }while(opcion2!= ESC);
}

void menuConsultaClientes(){
    int opcion3=0;
    char dni[30];
    int nroCliente;
    int existe;

    do{
        system("cls");
        color(3);
        printf("\n CONSULTA DE CLIENTES\n");
        printf("\n1-Por DNI");
        printf("\n2-Por Nro. de cliente");
        printf("\nPresione ESC para volver al menu de clientes\n");

        opcion3 = getch();
        system("cls");
        switch(opcion3){
            case 49:
                do{
                    printf("Ingrese numero de DNI: ");
                    fflush(stdin);
                    gets(dni);
                    existe=busquedaClienteXDni(ARCHIVO_CLIENTES, dni);
                    consultaXDni(ARCHIVO_CLIENTES, dni);
                    system("cls");
                }while(existe==0);

                break;
            case 50:
                do{
                    printf("Ingrese numero de cliente: ");
                    scanf("%d", &nroCliente);
                    existe=consultaXNroCl(ARCHIVO_CLIENTES, nroCliente);
                if(existe==0){
                    printf("\nNumero de cliente incorrecto.\n");
                    getch();
                }
                system("cls");

                }while(existe==0);

                break;
        }
    }while(opcion3 != ESC);
}

void menuListadoClientes(){
    stClientes clientes[DIM_CLIENTES];
    int validosClientes=0;
    int opcion4=0;

    do{
        system("cls");
        color(3);
        printf("\n LISTADO \n");
        printf("\n1-Ordenar por apellido");
        printf("\n2-Ordenar por DNI");
        printf("\n3-Ordenar por Nro. de cliente");
        printf("\n4-Listado");

        printf("\n\nPresione ESC para volver al menu de clientes\n");
        opcion4 = getch();

        system("cls");
        switch(opcion4){
             case 49:
                 validosClientes=0;
                 validosClientes=deArchivoAArreglo(ARCHIVO_CLIENTES, clientes, DIM_CLIENTES, validosClientes);
                 ordenaClientePorApellido(clientes, validosClientes);
                 muestraArregloClientes(clientes, validosClientes);
                 break;
             case 50:
                 validosClientes=0;
                 validosClientes=deArchivoAArreglo(ARCHIVO_CLIENTES, clientes, DIM_CLIENTES, validosClientes);
                 ordenaClientePorDni(clientes, validosClientes);
                 muestraArregloClientes(clientes, validosClientes);
                 break;
             case 51:
                 validosClientes=0;
                 validosClientes=deArchivoAArreglo(ARCHIVO_CLIENTES, clientes, DIM_CLIENTES, validosClientes);
                 ordenXNroCliente(clientes, validosClientes);
                 muestraArregloClientes(clientes, validosClientes);
                 break;
             case 52:
                 muestraArchivoCliente(ARCHIVO_CLIENTES);
                 system("pause");
                 break;
        }
    }while(opcion4!= ESC);
}

void replicachar(char e, int cant){

    for(int i=0; i<cant; i++){
        printf("%c", e);
    }
    printf("\n");
}
