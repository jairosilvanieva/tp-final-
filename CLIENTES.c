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

/** \brief Carga una structura de cliente con intervencion del usuario
 *
 * \param recibe un numero de tipo entero (ultimo id)
 * \return retorna una structura de cliente
 *
 */

stClientes altaCliente(int ultimoid){
    stClientes cl;
    static int id ;

    printf("\n Ingrese los datos\n ");
    printf("\nDNI de cliente........: ");
    fflush(stdin);
    gets(cl.dni);

    id = ultimoid;
    cl.id = id;
    cl.nroCliente = id;

    fflush(stdin);
    printf("Nombre de cliente........: ");
    gets(cl.nombre);

    fflush(stdin);
    printf("Apellido de cliente......: ");
    gets(cl.apellido);

    fflush(stdin);
    printf("Email de cliente.........: ");
    gets(cl.email);

    fflush(stdin);
    printf("Domicilio de cliente.....: ");
    gets(cl.domicilio);

    fflush(stdin);
    printf("Celular de cliente.......: ");
    gets(cl.movil);

    cl.eliminado = 0;

    return cl;
}

/** \brief carga un archivo con structuras de cliente
 *
 * \param recibe un archivo
 * \param recibe un entero (id)
 * \return void
 *
 */

void cargaArchivoClientes(char nombreArchivo[],int id){
    stClientes cl;
    int static ident=0;
    ident = buscaUltimoIdClientes(nombreArchivo);
    char opcion;
    int existe;

    FILE *clientes = fopen(nombreArchivo,"r+b");
    ///lo abrimos con r+b para poder leer y escribir
    if(!clientes){
    ///en caso de que no se haya abierto ya que es la primera vez
    ///lo abrimos en wb que a parte de abrirlo si no existe lo crea
        clientes = fopen(nombreArchivo, "wb");
        fclose(clientes);
    ///y lo volvemos abrir para poder leerlo y escribirlo al archivo
        clientes = fopen(nombreArchivo, "r+b");
    }

    if(clientes){
        do{
            system("cls");

            cl = altaCliente(id);
            existe = validacionClienteXDni(clientes, cl.dni);

            if(existe==1){
              printf("\nError - DNI duplicado\n");
            }
            else{
            ident++;
            cl.id= ident;
            cl.nroCliente= ident;
            fseek(clientes,0, SEEK_END);
            fwrite(&cl, sizeof(stClientes), 1, clientes);
            printf("\n Cliente cargado con exito\n");
            }

            printf("\n ESC para terminar carga de datos");
            opcion = getch();

        }while(opcion != ESC);
        fclose(clientes);
    }
}

/** \brief muestra structuras de clientes cargadas en un archivo
 *
 * \param recibe un archivo
 * \param
 * \return void
 *
 */

void muestraArchivoCliente(char nombreArchivo[]){
    stClientes cl;

    FILE *clientes = fopen(nombreArchivo, "rb");

    if(clientes){
        while (fread(&cl, sizeof (stClientes), 1, clientes)>0){
            muestraUnCliente(cl);
        }
        fclose(clientes);
    }
}

/** \brief muestra una sola structura de cliente
 *
 * \param recibe una structura de clientes
 * \param
 * \return void
 *
 */

void muestraUnCliente(stClientes cl){
    printf("\n");
    printf("Numero .....: %d\n", cl.nroCliente);
    printf("Nombre .....: %s\n", cl.nombre);
    printf("Apellido ...: %s\n", cl.apellido);
    printf("Dni ........: %s\n", cl.dni);
    printf("Email ......: %s\n", cl.email);
    printf("Domicilio ..: %s\n", cl.domicilio);
    printf("Celular ....: %s\n", cl.movil);

    if(cl.eliminado==0){
        printf("\n Estado: Activo\n");
    }else{
        printf("\n Estado: Inactivo\n");
    }
    replicachar('=', 70);
}

/** \brief verifica si un DNI esta cargado en el archivo o no
 *
 * \param recibe un archivo por puntero
 * \param recibe un string (el dni)
 * \return int. retorna 1 si existe. 0 si no existe
 *
 */

int validacionClienteXDni(FILE *clientes, char dni[]){
    int flag = 0;
    stClientes cl;
    rewind(clientes);
    ///usamos el rewind para recorrer el archivo desde el principio,
    ///funciona en conjunto con la carga de un cliente en el archivo
    if(clientes){
        while(flag==0 && fread(&cl, sizeof(stClientes), 1, clientes)>0){
            if(strcmp(cl.dni, dni)== 0){
                flag=1;
            }
        }
    }
    return flag;
}

/** \brief busca si existe o no un dni en el archivo
 *
 * \param recibe un archivo
 * \param recibe un string (el dni)
 * \return int. retorna 1 si existe. 0 si no existe
 *
 */

int busquedaClienteXDni(char nombreArchivo[], char dni[]){
    int flag = 0;
    stClientes cl;
    FILE *clientes = fopen(nombreArchivo, "rb");

    if(clientes){
        while(flag==0 && fread(&cl, sizeof(stClientes), 1, clientes)>0){
            if(strcmp(cl.dni, dni)==0){
                flag=1;
            }
        }
        fclose(clientes);
    }
    return flag;
}

/** \brief busca el ultimo id que se cargo en el archivo
 *
 * \param recibe un archivo
 * \param
 * \return retorna el id que se encontro en el archivo
 *
 */

int buscaUltimoIdClientes(char nombreArchivo[]){
    int id=0;
    stClientes cl;
///esta es la que usamos para el id autoincremental
    FILE *clientes = fopen(nombreArchivo, "rb");
    if(clientes){
        fseek(clientes,-1 * sizeof(stClientes), SEEK_END);
        ///nos paramos al final del archivo
        ///y nos movemos una posicion para atras del tamaño de la estructura
        if(fread(&cl, sizeof(stClientes), 1, clientes)> 0){
            ///una vez que leemos en una estructura
            ///tomamos el id con una variable y la devolvemos
            id = cl.id;
        }
        fclose(clientes);
    }
    ///ya sabemos que este es el ultimo id entonces necesitamos
    ///incrementar en uno esta variable que devolvemos
    return id;
}

/** \brief da de baja un cliente pasando eliminado=0 a eliminado=1
 * dejandolo inactivo al cliente sin borralo de la base de datos
 * \param recibe un archivo
 * \param recibe un string (el dni)
 * \return void
 *
 */

void bajaDeCliente(char nombreArchivo[],char dni[]){
    ///pedimos una por parametro un dni para poder buscar el cliente
    int flag = 0 ;
    stClientes cl;
    int eliminado=1;

    FILE *clientes = fopen(nombreArchivo, "r+b");
    if(clientes){
        while (flag==0 && fread(&cl, sizeof(stClientes), 1, clientes)>0){
            if((strcmp(cl.dni, dni)==0) && (cl.eliminado==0)){
                ///una vez encontrado el cliente nos empezamos a mover en el archivo
                fseek(clientes, -1 * sizeof(stClientes), SEEK_CUR);
                cl.eliminado=eliminado;
                fwrite(&cl, sizeof(stClientes), 1, clientes);
                printf("\n El cliente ha sido dado de baja\n ");
                muestraUnCliente(cl);
                system("pause");
                flag=1;
            }
            else if((strcmp(cl.dni, dni)==0) && (cl.eliminado==1)){
                printf("\nEl cliente ya se encuentra dado de baja\n");
                muestraUnCliente(cl);
                system("pause");
                flag=1;
            }
        }
        fclose(clientes);
    }
}

/** \brief si un cliente esta dado de baja esta funcion va a darlo de alta solo ingresando el dni
 *
 * \param recibe un archivo
 * \param recibe un string (el dni)
 * \return void
 *
 */

void reactivaCliente(char nombreArchivo[], char dni[]){
    int flag = 0 ;
    stClientes cl;
    int eliminado=0;

    FILE *clientes = fopen(nombreArchivo, "r+b");

    if(clientes){
        while(flag==0 && fread(&cl, sizeof(stClientes), 1, clientes)>0){
            if((strcmp(cl.dni, dni)==0) && (cl.eliminado==1)){
               cl.eliminado=eliminado;
               fseek(clientes, -1 * sizeof(stClientes), SEEK_CUR);
               fwrite(&cl, sizeof(stClientes), 1, clientes);
               printf("\n El cliente ha sido dado de alta nuevamente \n ");
               muestraUnCliente(cl);
               system("pause");
               flag=1;
            }
            else if((strcmp(cl.dni, dni)==0) && (cl.eliminado==0)){
            printf("\nEl cliente ya se encontraba activo.\n");
            muestraUnCliente(cl);
            system("pause");
            flag=1;
            }
        }
        fclose(clientes);
    }
}

/** \brief modifica un dato de structura cliente dentro de un archivo, segun la opcion que se elija
 *
 * \param recibe un archivo
 * \param recibe un string (el dni)
 * \param recibe un entero que sera la opcion a elegir
 * \return void no tiene retorno
 *
 */

void modificaCliente(char nombreArchivo[], char dni[], int opcion){
    stClientes cl;
    int flag=0;

    FILE *clientes= fopen(nombreArchivo, "r+b");

    if(clientes){
        while(flag==0 && fread(&cl, sizeof(stClientes), 1, clientes)>0){
            if(strcmp(cl.dni, dni)==0){
                ///mostramos el cliente antes de modificarlo para
                ///que sepa que quiere modificar
                muestraUnCliente(cl);
                system("cls");
                fseek(clientes,-1 * sizeof(stClientes), SEEK_CUR);
                ///con el int opcion del prototipado vamos a elegir la opcion
                ///que desea el usuario
                if(opcion==1){
                    cl=cambiaNombre(cl);
                }
                if(opcion==2){
                    cl=cambiaApellido(cl);
                }
                if(opcion==3){
                    cl=cambiaDni(cl);
                }
                if(opcion==4){
                    cl=cambiaEmail(cl);
                }
                if(opcion==5){
                    cl=cambiaDireccion(cl);
                }
                if(opcion==6){
                    cl=cambiaMovil(cl);
                }
                ///escribimos una vez que tengamos la estructura modificada
                fwrite(&cl, sizeof(stClientes), 1, clientes);
                muestraUnCliente(cl);
                flag=1;
                system("pause");
            }
        }
        fclose(clientes);
    }
}

/** \brief cambia el nombre de un cliente
 *
 * \param recibe una structura de cliente
 * \param
 * \return retorna el cliente modificado
 *
 */

stClientes cambiaNombre(stClientes cl){

    printf("Ingrese nuevo nombre: ");
    fflush(stdin);
    gets(cl.nombre);

    return cl;
}

/** \brief cambia el apellido de un cliente
 *
 * \param recibe una structura de cliente
 * \param
 * \return retorna el cliente modificado
 *
 */

stClientes cambiaApellido(stClientes cl){

    printf("Ingrese nuevo apellido: ");
    fflush(stdin);
    gets(cl.apellido);

    return cl;
}

/** \brief cambia el email de un cliente
 *
 * \param recibe una structura de cliente
 * \param
 * \return retorna el cliente modificado
 *
 */

stClientes cambiaEmail(stClientes cl){

    printf("Ingrese nuevo email: ");
    fflush(stdin);
    gets(cl.email);

    return cl;
}

/** \brief cambia la direccion de un cliente
 *
 * \param recibe una structura de cliente
 * \param
 * \return retorna el cliente modificado
 *
 */

stClientes cambiaDireccion(stClientes cl){

    printf("Ingrese nueva direccion: ");
    fflush(stdin);
    gets(cl.domicilio);

    return cl;
}

/** \brief cambia el movil de un cliente
 *
 * \param recibe una structura de cliente
 * \param
 * \return retorna el cliente modificado
 *
 */

stClientes cambiaMovil(stClientes cl){
    int existe;

    do{
        printf("Ingrese nuevo Nro de movil: ");
        fflush(stdin);
        gets(cl.movil);
        existe= busquedaClienteXCelular(ARCHIVO_CLIENTES, cl.movil);
        ///validamos que no haya ingresado el numero de otro cliente
        if(existe==1){
            printf("\nError Nro de movil duplicado. Ingrese otro por favor.\n");
            getch();
        }
        system("cls");

    }while(existe==1);

    return cl;
}

/** \brief cambia el dni de un cliente
 *
 * \param recibe una structura de cliente
 * \param
 * \return retorna el cliente modificado
 *
 */

stClientes cambiaDni(stClientes cl){
    int existe;

    do{
        printf("Ingrese nuevo DNI: ");
        fflush(stdin);
        gets(cl.dni);
        existe= busquedaClienteXDni(ARCHIVO_CLIENTES, cl.dni);
        ///validamos que no ingrese el dni de otro cliente
        if(existe==1){
            printf("\nError DNI duplicado. Ingrese otro por favor.\n");
            getch();
        }
        system("cls");

    }while(existe==1);

    return cl;
}

/** \brief cuenta la cantidad de structuras de clientes (clientes) cargados en un archivo
 *
 * \param recibe un archivo
 * \param
 * \return retorna la cantidad de clientes
 *
 */

int cuentaRegistros(char nombreArchivo[]){
    stClientes cl;
    int cant=0;

    FILE *clientes = fopen(nombreArchivo,"rb");

    if(clientes){
        while(fread(&cl, sizeof(stClientes), 1, clientes) > 0){
            cant++;
        }
        ///usamos un contador para contar las cantidad de registro que leemos
        fclose(clientes);
    }
    return cant;
}

/** \brief pasa todos las structuras de clientes cargadas que existen en el archivo a un arreglo
 *
 * \param recibe el archivo
 * \param recibe un arreglo de tipo de structura de clientes
 * \param recibe un entero que sera la dimencion del arreglo
 * \param recibe los validos
 * \return retorna los validos del arreglo
 *
 */

int deArchivoAArreglo(char nombreArchivo[], stClientes cli[], int dimension, int validos){
    stClientes cl;

    FILE *clientes = fopen(nombreArchivo, "rb");

    if(clientes){
        while(fread(&cl, sizeof(stClientes), 1, clientes)>0 && validos<dimension){
            cli[validos]=cl;
            validos++;
            ///pasamos del archivo a un arreglo de estructuras
        }
        fclose(clientes);
    }
    return validos;
}

/** \brief muestra un arreglo de structuras de cliente
 *
 * \param recibe el arreglo
 * \param recibe los validos
 * \return void
 *
 */

void muestraArregloClientes(stClientes cl[], int validos){

    for(int i=0; i<validos; i++){
        muestraUnCliente(cl[i]);
    }
    system("pause");
}

/** \brief muestra un cliente buscado por dni
 *
 * \param recibe un archivo
 * \param recibe un string (el dni)
 * \return void
 *
 */

void consultaXDni(char nombreArchivo[], char dni[]){
    stClientes cl;
    int flag=0;
    int existe;
    existe= busquedaClienteXDni(nombreArchivo, dni);

    FILE *clientes = fopen(nombreArchivo, "rb");

    if(clientes){
        if(existe==1){
            ///corroboramos que exista el dni
            while(flag==0 && fread(&cl, sizeof(stClientes), 1, clientes)>0){
                if(strcmp(dni, cl.dni)==0){
                    muestraUnCliente(cl);
                    system("pause");
                    flag=1;
                }
            }
        }
        else{
            printf("\nNo existe cliente con ese DNI\n");
            getch();
        }
        fclose(clientes);
    }
}

/** \brief muestra un cliente buscado por el numero de cliente
 *
 * \param recibe un archivo
 * \param recibe un entero (el numero de cliente
 * \return retorna entero 1 si lo encuentra o 0 si no lo encuentra
 *
 */

int consultaXNroCl(char nombreArchivo[], int numCliente){
    stClientes cl;
    int flag=0;

    FILE *clientes = fopen(nombreArchivo, "rb");

    if(clientes){
        while(flag==0 && fread(&cl, sizeof(stClientes), 1, clientes)>0){
            if(numCliente==cl.nroCliente){
                muestraUnCliente(cl);
                flag=1;
                system("pause");
            }
        }
        fclose(clientes);
    }
    return flag;
}
/** \brief busca en un arreglo la posicion donde se encuentra el menor numero de cliente
 *
 * \param un arreglo con structura de cliente
 * \param recibe los validos
 * \param recibe un entero  para asignarla a la posicion menor en la funcion
 * \return  retorna la posicion del menor dato
 *
 */

int buscaMenorNroCliente(stClientes a[], int v, int pos){
    int posMenor = pos;
    pos++;

    while(pos<v){
        if(a[pos].nroCliente < a[posMenor].nroCliente){
            posMenor = pos;
        }
        pos++;
    }

    return posMenor;
}

/** \brief intercambia dos datos de structura clientes
 *
 * \param recibe un puntero de structura
 * \param recibe un puntero de structura
 * \return void no tiene retorno
 *
 */

void intercambioClientes(stClientes *a, stClientes *b){
    stClientes aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

/** \brief ordena un arreglo por numero de cliente
 *
 * \param recibe un arreglo de structura de cliente
 * \param  recibe los validos
 * \return void no tiene retorno
 *
 */

void ordenXNroCliente(stClientes e[], int v){
    int posMenor;
    int i=0;

    while(i<v-1){
        posMenor = buscaMenorNroCliente(e, v, i);
        intercambioClientes(&e[posMenor], &e[i]);
        i++;
    }
}

/** \brief busca el menor dni en un arreglo
 *
 * \param recibe un arreglo de structura de cliente
 * \param recibe los validos
 * \param recibe  un entero  para asignarla a la posicion menor en la funcion
 * \return retorna la posicion donde se encuentra el menor dni
 *
 */

int buscaMenorDni(stClientes e[], int v, int pos){
    int posMenor = pos;
    pos++;

    while(pos<v){
        if(strcmp(e[pos].dni, e[posMenor].dni)<0){
            posMenor = pos;
        }
        pos++;
    }

    return posMenor;
}

/** \brief ordena el arreglo por dni de menor a mayor
 *
 * \param recibe un arreglo de structura de cliente
 * \param recibe los validos
 * \return void no tiene retorno
 *
 */

void ordenaClientePorDni(stClientes e[], int v){
    int posMenor;
    int i=0;

    while(i<v-1){
        posMenor=buscaMenorDni(e, v, i);
        intercambioClientes(&e[posMenor],&e[i]);
        i++;
    }
}

/** \brief busca en  el arreglo la posicion del menor apellido (que empiece con "a"siga con "b" etc.)
 *
 * \param recibe un arreglo de structura de cliente
 * \param recibe los validos
 * \param recibe  un entero  para asignarla a la posicion menor en la funcion
 * \return retorna la posicion donde se encuentra el menor apellido
 *
 */

int buscaMenorApellido(stClientes e[], int v, int pos){
    int posMenor = pos;
    pos++;

    while(pos<v){
        if(strcmp(e[pos].apellido, e[posMenor].apellido)<0){
            posMenor = pos;
        }
        pos++;
    }

    return posMenor;
}

/** \brief ordena el arreglo por apellido de menor a mayor (alfabeticamente)
 *
 * \param recibe un arreglo de structura de cliente
 * \param recibe los validos
 * \return void no tiene retorno
 *
 */

void ordenaClientePorApellido(stClientes e[], int v){
    int posMenor;
    int i=0;

    while(i<v-1){
        posMenor=buscaMenorApellido(e, v, i);
        intercambioClientes(&e[posMenor],&e[i]);
        i++;
    }
}

/** \brief busca en el archivo si ya existe o no un celular ingresado .
 *
 * \param recibe el archivo
 * \param recibe el string (el celular)
 * \return retorna entero 1 si lo encuentra 0 si no existe
 *
 */

int busquedaClienteXCelular(char nombreArchivo[], char celular[]){
    int flag = 0;
    stClientes cl;

    FILE *clientes = fopen(nombreArchivo, "rb");

    if(clientes){
        while(flag==0 && fread(&cl, sizeof(stClientes), 1, clientes)>0){
            if (strcmp(cl.movil, celular)==0){
                flag=1;
            }
        }
        fclose(clientes);
    }
    return flag;
}

/** \brief busca por dni en un archivo el numero de cliente y lo retorna
 *
 * \param recibe el archivo
 * \param recibe un string (el dni)
 * \return retorna el numero de cliente
 *
 */

int retornaNroClientePorDni(char nombreArchivo[], char dni[]){
    int flag = 0;
    int nroCliente;
    stClientes cl;

    FILE *clientes = fopen(nombreArchivo, "rb");

    if(clientes){
        while(flag==0 && fread(&cl, sizeof(stClientes), 1, clientes)>0){
            if (strcmp(cl.dni, dni)==0){
                flag=1;
                nroCliente=cl.nroCliente;
            }
        }
        fclose(clientes);
    }
    return nroCliente;
}

/** \brief busca en un archivo el id del cliente
 *
 * \param recibe un archivo
 * \param recibe un entero (el id a buscar )
 * \return retorna entero 1 si lo encuentra 0 si no lo encuentra
 *
 */

int buscaIdCliente(char nombreArchivo[], int id){
    int flag = 0;
    stClientes cl;

    FILE *clientes = fopen(nombreArchivo, "rb");

    if(clientes){
        while(flag==0 && fread(&cl, sizeof(stClientes), 1, clientes)>0){
            if(cl.id == id){
                flag = 1;
            }
        }
        fclose(clientes);
    }
    return flag;
}
