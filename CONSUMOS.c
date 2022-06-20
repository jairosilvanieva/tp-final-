#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "CLIENTES.h"
#include "CONSUMOS.h"
#include "MENU.h"

#define ESC 27
#define ARCHIVO_CLIENTES "clientes.bin"
#define ARCHIVO_CONSUMOS "consumos.bin"

/** \brief carga una estructura de consumo de forma random.
 *
 * \param recibe como parametro el ultimo id encontrado.
 * \param
 * \return retorna la estructura de consumo.
 *
 */

stConsumos altaConsumo(int ultimoid){
    stConsumos co;

    static int id;
    id = ultimoid;
    co.id = id;

    co.idCliente = getIdCliente();
    co.anio = 2022;
    co.mes = getMes();

    if(co.mes==2){
        co.dia = getDiaFebrero();
    }else if(co.mes==4 || co.mes==6){
        co.dia = getDiaMes30();
    }else{
        co.dia = getDia();
    }

    co.datosConsumidos = getDatos();
    co.baja = 0;

    return co;
}

/** \brief carga una estructura de consumo con intervencion del usuario.
 *
 * \param recibe como parametro el ultimo id encontrado .
 * \param
 * \return retorna la estructura de un consumo.
 *
 */

stConsumos altaConsumoUsuario(int ultimoid){
    stConsumos co;

    static int id;
    id = ultimoid;
    co.id = id;
    int flag=0;
    int flag1=0;

    do {
        printf("Carga ID de cliente..........: ");
        scanf("%d", &co.idCliente);
        flag = buscaIdCliente(ARCHIVO_CLIENTES, co.idCliente);
        if(flag == 0){
            printf("\n No existe ese cliente. Ingrese otro \n");
        }
    }while(flag==0);

    do{
        printf("Carga Anio...................: ");
        scanf("%d", &co.anio);
        if(co.anio>2022 || co.anio<2014){
            printf("\n Error - Anio invalido\n");
        }
    }while(co.anio>2022 || co.anio<2014);

    do{
        printf("Carga Mes....................: ");
        scanf("%d", &co.mes);
        if(co.mes > 12 || co.mes < 1){
            printf("\n Error - Mes invalido\n");
        }
    }while(co.mes > 12 || co.mes < 1);

    do{
        printf("Carga Dia....................: ");
        scanf("%d", &co.dia);
        flag1=0;

        if(co.mes == 2 && co.dia > 28){
            flag1=1;
        }
        if((co.mes==4 || co.mes==6 || co.mes==9 || co.mes==11) && co.dia > 30){
            flag1=1;
        }
        if(co.dia>31 || co.dia<1){
            flag1=1;
        }
        if(flag1==1){
            printf("\n Error - Dia invalido\n");
        }
    }while(flag1==1);

    do{
        printf("Carga Datos Consumidos.......: ");
        scanf("%d", &co.datosConsumidos);
        if(co.datosConsumidos<0){
            printf(" - Error - \n");
        }
    }while(co.datosConsumidos<0);

    co.baja = 0;

    return co;
}

/** \brief muestra una sola structura de consumo.
 *
 * \param recibe por parametro una structura de consumos.
 * \param
 * \return void.
 *
 */

void muestraUnConsumo(stConsumos co){
    printf("\n ID.....................: %d", co.id);
    printf("\n ID Cliente.............: %d", co.idCliente);
    printf("\n Anio...................: %d", co.anio);
    printf("\n Mes....................: %d", co.mes);
    printf("\n Dia....................: %d", co.dia);
    printf("\n Datos Consumidos.......: %d", co.datosConsumidos);
    printf("\n Baja...................: %d", co.baja);
    printf("\n =============================================== \n");

}

/** \brief genera un id de cliente random.
 *
 * \return int id de cliente
 *
 */

int getIdCliente(){
    int idCliente = (rand()%50) +1;
    return idCliente;
}

/** \brief genera un mes random.
 *
 * \return int mes
 *
 */

int getMes(){
    int mes = (rand()%6) +1;
    return mes;
}

/** \brief genera un dia random para el mes de Febrero
 *
 * \return int dia
 *
 */

int getDiaFebrero(){
    int dia = (rand()%28) +1;
    return dia;
}

/** \brief genera un dia random para los meses de 30 días.
 *
 * \return int dia
 *
 */

int getDiaMes30(){
    int dia = (rand()%30) +1;
    return dia;
}

/** \brief genera un dia random entre el 1 y el 31.
 *
 * \return int dia
 *
 */

int getDia(){
    int dia = (rand()%31) +1;
    return dia;
}

/** \brief genera datos consumidos random.
 *
 * \return int
 *
 */

int getDatos(){
    int datos = (rand()% 950) +50;
    return datos;
}

/** \brief busca el ultimo idconsumos que se cargo en el archivo.
 *
 * \param recibe por parametro el archivo en el que se va a buscar ese id.
 * \param
 * \return retorna el ultimo numero de id que se encontro en el archivo.
 *
 */

int buscaUltimoIdConsumos(char nombreArchivo[]){
    int id=0;
    stConsumos co;

    FILE *consu = fopen(nombreArchivo, "rb");
    if(consu){
        fseek(consu,-1 *sizeof (stConsumos), SEEK_END) ;
        if (fread(&co, sizeof (stConsumos), 1, consu)> 0){
            id = co.id;
        }
        fclose(consu);
    }
    return id;
}

/** \brief carga en el archivo la structura que se cargo con la funcion
 * "altaConsumoUsuario" o "altaConsumo"
 * \param  recibe un archivo
 * \param  id para la funcion de altaConsumo
 * \return void
 *
 */

void cargaArchivoConsumos(char nombreArchivo[],int id){
    stConsumos co;
    int static ident = 0;
    ident = buscaUltimoIdConsumos(nombreArchivo);
    char opcion;

    FILE *consu = fopen(nombreArchivo, "r+b");

    if(!consu){
        consu = fopen(nombreArchivo, "wb");
        fclose(consu);
        consu = fopen(nombreArchivo, "r+b");
    }

    if(consu){
        do{
            system("cls");
            ident++;
            co = altaConsumoUsuario(id);
            co.id = ident;

            int posicion = fechaExisteConsumos(consu, co.idCliente, co.anio, co.mes, co.dia);

            if(posicion!= -1){
                modificaDatosConsumidos(consu, co.datosConsumidos, posicion);
            }else{
                fseek(consu, 0, SEEK_END);
                fwrite(&co,sizeof (stConsumos), 1, consu);
            }

            printf("\n Consumo cargado con exito\n");
            printf("\n ESC para terminar carga de datos");
            opcion = getch();


        }while(opcion != ESC);
        fclose(consu);
    }
}

/** \brief busca si un cliente ya tuvo un consumo en cierta fecha dentro del archivo.
 *
 * \param recibe el archivo por puntero
 * \param  recibe id del cliente a comparar
 * \param  recibe el anio a comparar
 * \param  recibe el mes a comparar
 * \param  recibe el dia a comparar
 * \return retorna la posicion de ese consumo. Si retorna -1 no encontro coincidencias.
 *
 */

int fechaExisteConsumos(FILE * consu, int idCliente, int anio, int mes, int dia){
    int posicion = -1;
    stConsumos co;

    rewind(consu);

    if(consu){
        while(posicion == -1 && fread(&co, sizeof (stConsumos), 1, consu)>0){
            if((co.idCliente == idCliente) && (co.anio == anio) && (co.mes == mes) && (co.dia == dia)){
                posicion = ftell(consu) - sizeof(stConsumos);
            }
        }
    }

    return posicion;
}

/** \brief suma los nuevos datos consumidos a una estructura de consumo preexistente
 *
 * \param recibe por puntero un archivo
 * \param recibe la cantidad de datos consumidos
 * \param recibe una posicion para mover el archivo
 * \return void
 *
 */

void modificaDatosConsumidos(FILE * consu, int datos, int posicion){
    stConsumos co;

    fseek(consu, posicion , SEEK_SET);

    fread(&co, sizeof(stConsumos), 1, consu);
    co.datosConsumidos += datos;
    fseek(consu, -1 * sizeof(stConsumos), SEEK_CUR);
    fwrite(&co, sizeof(stConsumos), 1, consu);

}

/** \brief muestra los consumos que hay en un archivo
 *
 * \param recibe el archivo
 * \param
 * \return void
 *
 */

void muestraArchivoConsumos(char nombreArchivo[]){
    stConsumos co;

    FILE *consu = fopen(nombreArchivo, "rb");

    if(consu){
        while(fread(&co, sizeof (stConsumos), 1, consu)>0){
            muestraUnConsumo(co);
        }
        fclose(consu);
    }
}

/** \brief recorre el archivo buscando si existe un id
 *
 * \param recibe el archivo
 * \param recibe un  id para comparar
 * \return retorna un 1 si lo encuentra o 0 si no lo encuentra
 *
 */

int idExisteConsumos(char nombreArchivo[], int id){
    int flag = 0;
    stConsumos co;

    FILE *consu = fopen(nombreArchivo, "rb");

    if(consu){
        while (flag==0 && fread(&co, sizeof (stConsumos), 1, consu)>0){
            if(co.id == id){
                flag=1;
            }
        }
        fclose(consu);
    }
    return flag;
}

/** \brief busca una fecha en el archivo de consumos
 *
 * \param recibe el archivo
 * \param recibe un anio
 * \param recibe un mes
 * \param recibe un dia
 * \return retorna un 1 si la encuentra o un 0 si no la encuentra
 *
 */

int buscaFechaConsumos(char nombreArchivo[], int anio, int mes, int dia){
    int flag = 0;
    stConsumos co;

    FILE *consu = fopen(nombreArchivo, "rb");

    if(consu){
        while (flag==0 && fread(&co, sizeof (stConsumos), 1, consu)>0){
            if(co.anio == anio && co.mes == mes && co.dia == dia){
                flag = 1;
            }
        }
        fclose(consu);
    }
    return flag;
}

/** \brief pasa los consumos en archivo de determinado cliente a un arreglo
 *
 * \param recibe un archivo
 * \param una structura de tipo arreglo
 * \param recibe la dimencion
 * \param recibe el id del cliente
 * \return retorna los validos del arreglo
 *
 */

int archi2arregloConsumosDeCliente(char nombreArchivo[], stConsumos c[], int dim, int idCliente){
    int v=0;
    stConsumos co;

    FILE * consu = fopen(nombreArchivo, "rb");

    if(consu){
        while(v<dim && fread(&co, sizeof(stConsumos), 1, consu)>0){
            if(idCliente == co.idCliente){
                c[v]= co;
                v++;
            }
        }
        fclose(consu);
    }
    return v;
}

/** \brief ordena un arreglo de structura de consumos por fecha
 *
 * \param recibe un arreglo de structura consumos
 * \param recibe los validos
 * \return void
 *
 */

void ordenaArregloPorFecha(stConsumos c[], int v){
    int posMenor;
    int i=0;

    while(i<v-1){
        posMenor = buscaPosMenorFecha(c, v, i);
        intercambioConsumos(&c[posMenor], &c[i]);
        i++;
    }
}

/** \brief busca la posicion de la menor fecha en un arreglo
 *
 * \param recibe un arreglo de structura consumos
 * \param recibe los validos
 * \param recibe una posicion
 * \return retorna la posicion de la menor fecha
 *
 */

int buscaPosMenorFecha(stConsumos c[], int v, int pos){
    int posMenor = pos;
    pos++;

    while(pos<v){
        if(c[pos].anio < c[posMenor].anio){
            if(c[pos].mes < c[posMenor].mes){
                if(c[pos].dia < c[posMenor].dia){
                    posMenor = pos;
                }
            }
        }
        pos++;
    }
    return posMenor;
}

/** \brief invierte los datos de dos structuras
 *
 * \param recibe dos punteros de structuras
 * \param
 * \return void
 *
 */

void intercambioConsumos(stConsumos *a, stConsumos *b){
    stConsumos aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

/** \brief muestra un arreglos de structuras consumos
 *
 * \param un arreglo de structura consumos
 * \param validos
 * \return void
 *
 */

void muestraArregloConsumos (stConsumos c[], int validos){

    for (int i=0; i<validos; i++){
        muestraUnConsumo(c[i]);
    }
}

/** \brief pasa de un archivo a un arreglo aquellos consumos que coincidan con determinada fecha
 *
 * \param recibe un archivo
 * \param recibe un arreglo de structura consumos
 * \param recibe la dimension del arreglo
 * \param recibe un anio para comparar
 * \param recibe un mes para comparar
 * \param recibe un dia para comparar
 * \return validos del arreglo cargado
 *
 */

int arregloConsumosDeFecha(char nombreArchivo[], stConsumos c[], int dim, int anio, int mes, int dia){
    int v=0;
    stConsumos co;

    FILE * consu = fopen(nombreArchivo, "rb");
    if(consu){
        while(v<dim && fread(&co, sizeof(stConsumos), 1, consu)>0){
            if(co.anio == anio && co.mes == mes && co.dia == dia){
                c[v]= co;
                v++;
            }
        }
        fclose(consu);
    }
    return v;
}

/** \brief modifica un dato de structura consumo dentro de un archivo, segun la opcion que se elija
 *
 * \param  se recibe un archivo
 * \param  se recibe un id
 * \param  se recibe un numero que designa la opcion a modificar

 * \return void
 *
 */

void modificaConsumos(char nombreArchivo[], int id, int opcion){
    stConsumos co;
    int flag=0;

    FILE * consu = fopen(nombreArchivo, "r+b");

    if(consu){
        while(flag==0 && fread(&co, sizeof(stConsumos), 1, consu)>0){
            if(co.id == id){
                fseek(consu, -1 * sizeof(stConsumos), SEEK_CUR);

                if (opcion == 1){
                    co.idCliente = cambiaIdCliente();
                }
                if (opcion == 2){
                    co.anio = cambiaAnio();
                }
                if (opcion == 3){
                    co.mes = cambiaMes();
                }
                if (opcion == 4){
                    co = cambiaDia(co);
                }
                if (opcion == 5){
                    co.datosConsumidos = cambiaDatosConsumidos();
                }

                fwrite(&co, sizeof(stConsumos), 1, consu);
                muestraUnConsumo(co);
                system("pause");
                flag=1;
            }
        }
        fclose(consu);
    }
}

/** \brief cambia el id de cliente de un consumo
 *
 * \return retorna el nuevo id de cliente
 *
 */

int cambiaIdCliente(){
    int idCliente;

    printf("Ingrese nuevo ID de Cliente: ");
    scanf("%d", &idCliente);

    return idCliente;
}

/** \brief cambia el anio de un consumo
 *
 * \return retorna el nuevo anio
 *
 */

int cambiaAnio(){
    int anio;

    do{
        printf("Ingrese nuevo Anio: ");
        scanf("%d", &anio);
        if(anio>2022 || anio<2014){
            printf("Error - Año Invalido\n");
        }
    }while(anio>2022 || anio<2014);

    return anio;
}

/** \brief cambia el mes de un consumo
 *
 * \return retorna el nuevo mes
 *
 */

int cambiaMes(){
    int mes;

    do{
        printf("Ingrese nuevo Mes: ");
        scanf("%d", &mes);
        if(mes>12 || mes<1){
            printf("Error - Mes Invalido\n");
        }
    }while(mes>12 || mes<1);

    return mes;
}

/** \brief cambia el dia de un consumo
 *
 * \return retorna el nuevo dia
 *
 */

stConsumos cambiaDia(stConsumos co){
    int flag=0;

    do{
    printf("Ingrese nuevo Dia: ");
    scanf("%d", &co.dia);
    if(co.mes == 2 && co.dia > 28){
        flag=1;
    }
    if((co.mes==4 || co.mes==6 || co.mes==9 || co.mes==11) && co.dia > 30){
        flag=1;
    }
    if(co.dia>31 || co.dia<1){
        flag=1;
    }
    if(flag==1){
        printf("Error - Dia invalido\n");
    }
    }while(flag == 1);

    return co;
}

/** \brief modifica los datos consumidos de un consumo
 *
 * \return retorna el nuevo consumo
 *
 */

int cambiaDatosConsumidos(){
    int datosConsumidos;

    do{
        printf("Ingrese nueva cantidad de Datos Consumidos: ");
        scanf("%d", &datosConsumidos);
        if(datosConsumidos<0){
            printf(" - Error - \n");
        }
    }while(datosConsumidos<0);

    return datosConsumidos;
}

/** \brief muestra un consumo correspondiente al id que se manda por parametro
 *
 * \param se recibe un archivo
 * \param se recibe un id
 * \return void
 *
 */

void consultaConsumoXId(char nombreArchivo[], int id){
    stConsumos co;
    int flag=0;
    int existe;
    existe = idExisteConsumos(nombreArchivo, id);

    FILE * consu = fopen(nombreArchivo, "rb");

    if(consu){
        if(existe==1){
            while(flag==0 && fread(&co, sizeof(stConsumos), 1, consu)>0){
                if(co.id == id){
                    flag=1;
                    muestraUnConsumo(co);
                }
            }
        }else{
            printf("\nNo se encontró consumo correspondiente a ese N° de ID\n");
            getch();
        }
        fclose(consu);
    }
}

/** \brief busca en un archivo si hay consumos de determinado cliente
 *
 * \param recibe un archivo
 * \param recibe el id del cliente para comparar
 * \return retorna 1 si hay, retorna 0 si no encuentra coincidencias
 *
 */

int buscaIdClienteConsumos(char nombreArchivo[], int idCliente){
    int flag = 0;
    stConsumos co;

    FILE *consu = fopen(nombreArchivo, "rb");

    if(consu){
        while (flag==0 && fread(&co, sizeof (stConsumos), 1, consu)>0){
            if(co.idCliente == idCliente){
                flag = 1;
            }
        }
        fclose(consu);
    }
    return flag;
}

/** \brief da de baja un consumo, si ya esta dado de baja lo avisa
 *
 * \param recibe un archivo
 * \param recibe el id del consumo a dar de baja
 * \return void
 *
 */

void bajaDeConsumo(char nombreArchivo[],int id){
    int flag = 0 ;
    stConsumos co;

    FILE *consu = fopen(nombreArchivo, "r+b");
    if(consu){
        while (flag==0 && fread(&co, sizeof(stConsumos), 1, consu)>0){
            if(co.id == id){
                fseek(consu, -1 * sizeof (stConsumos), SEEK_CUR);
                if(co.baja==1){
                    printf("\nEl consumo ya se encuentra dado de baja\n");
                }else{
                    co.baja = 1;
                    fwrite(&co, sizeof(stConsumos), 1, consu);

                    printf("\nEl consumo ha sido dado de baja\n ");
                    muestraUnConsumo(co);
                    system("pause");
                    flag=1;
                }
            }
        }
        fclose(consu);
    }
}
