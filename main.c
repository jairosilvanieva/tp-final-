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
#define ARCHIVO_CLIENTES "clientes.bin"
#define ARCHIVO_CONSUMOS "consumos.bin"

int main()
{

    gotoxy(15,8);
    color(11);
    printf("\t\t\t Bienvenido a Compania telefonica MoviTur \n");
    gotoxy(35,10);
    color(3);
    hidecursor(0);
    system("\t\t\t pause");

    char opcion=0;

    do{
        system("cls");
        muestraMenu();
        opcion = getch();

        switch(opcion){
            case 49:
                menuClientes();
                break;
            case 50:
                menuConsumos();
                break;
        }

    }while(opcion != ESC);
    printf("\nFin de la ejecucion\n");

    return 0;
}
