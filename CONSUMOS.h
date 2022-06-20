#ifndef CONSUMOS_H_INCLUDED
#define CONSUMOS_H_INCLUDED

typedef struct{
    int id;
    int idCliente;
    int anio;
    int mes;
    int dia;
    int datosConsumidos;
    int baja;
}stConsumos;

stConsumos altaConsumo(int ultimoid);
stConsumos altaConsumoUsuario(int ultimoid);
void muestraUnConsumo(stConsumos co);
int getIdCliente();
int getMes();
int getDiaFebrero();
int getDiaMes30();
int getDia();
int getDatos();
int buscaUltimoIdConsumos(char nombreArchivo[]);
void cargaArchivoConsumos(char nombreArchivo[],int id);
int fechaExisteConsumos(FILE * consu, int idCliente, int anio, int mes, int dia);
void modificaDatosConsumidos(FILE * consu, int datos, int posicion);
void muestraArchivoConsumos(char nombreArchivo[]);
int idExisteConsumos(char nombreArchivo[], int id);
int buscaFechaConsumos(char nombreArchivo[], int anio, int mes, int dia);
int archi2arregloConsumosDeCliente(char nombreArchivo[], stConsumos c[], int dim, int idCliente);
void ordenaArregloPorFecha(stConsumos c[], int v);
int buscaPosMenorFecha(stConsumos c[], int v, int pos);
void intercambioConsumos(stConsumos *a, stConsumos *b);
void muestraArregloConsumos (stConsumos c[], int validos);
int arregloConsumosDeFecha(char nombreArchivo[], stConsumos c[], int dim, int anio, int mes, int dia);
void modificaConsumos(char nombreArchivo[], int id, int opcion);
int cambiaIdCliente();
int cambiaAnio();
int cambiaMes();
stConsumos cambiaDia(stConsumos co);
int cambiaDatosConsumidos();
void consultaConsumoXId(char nombreArchivo[], int id);
int buscaIdClienteConsumos(char nombreArchivo[], int idCliente);
void bajaDeConsumo(char nombreArchivo[],int id);

#endif // CONSUMOS_H_INCLUDED
