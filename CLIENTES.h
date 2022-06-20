#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

typedef struct{
    int id;
    int nroCliente;
    char nombre[30];
    char apellido[30];
    char dni[10];
    char email[30];
    char domicilio[45];
    char movil[12];
    int eliminado;
}stClientes;

stClientes altaCliente(int ultimoid);
void cargaArchivoClientes(char nombreArchivo[],int id);
void muestraArchivoCliente(char nombreArchivo[]);
void muestraUnCliente(stClientes cl);
int validacionClienteXDni(FILE *clientes, char dni[]);
int busquedaClienteXDni(char nombreArchivo[], char dni[]);
int buscaUltimoIdClientes(char nombreArchivo[]);
void bajaDeCliente(char nombreArchivo[],char dni[]);
void reactivaCliente(char nombreArchivo[], char dni[]);
void modificaCliente(char nombreArchivo[], char dni[], int opcion);
stClientes cambiaNombre(stClientes cl);
stClientes cambiaApellido(stClientes cl);
stClientes cambiaEmail(stClientes cl);
stClientes cambiaDireccion(stClientes cl);
stClientes cambiaMovil(stClientes cl);
stClientes cambiaDni(stClientes cl);
int cuentaRegistros(char nombreArchivo[]);
int deArchivoAArreglo(char nombreArchivo[], stClientes cli[], int dimension, int validos);
void muestraArregloClientes(stClientes cl[], int validos);
void consultaXDni(char nombreArchivo[], char dni[]);
int consultaXNroCl(char nombreArchivo[], int numCliente);
int buscaMenorNroCliente(stClientes a[], int v, int pos);
void intercambioClientes(stClientes *a, stClientes *b);
void ordenXNroCliente(stClientes e[], int v);
int buscaMenorDni(stClientes e[], int v, int pos);
void ordenaClientePorDni(stClientes e[], int v);
int buscaMenorApellido(stClientes e[], int v, int pos);
void ordenaClientePorApellido(stClientes e[], int v);
int busquedaClienteXCelular(char nombreArchivo[], char celular[]);
int retornaNroClientePorDni(char nombreArchivo[], char dni[]);
int buscaIdCliente(char nombreArchivo[], int id);


#endif // CLIENTES_H_INCLUDED
