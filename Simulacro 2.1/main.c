#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char modelo[30];
    int anio;
    char marca[30];
    float precio;
} automovil;

int cargarAutomoviles(automovil autos[], int dimension);
void mostrarAutomoviles(automovil autos[], int cantidad);
int cargarMatriz(int matriz[][10], int*fila, int*col);
void guardarAutomovilesCaros(automovil autos[], int cantidad);
void mostrarArchivo(char* autos_gamaAlta );
int contarRegistros(char* autos_gamaAlta);
float calcularPorcentajeMarca(char* autos_gamaAlta, char* marca);


int main()
{
    char yes;
    int option;
    int i=0;
    int cantidadCargada;
    int matriz[30][30];
    int fila,col;
    int cantidadRegistros;
    char marca[30];

    automovil autos[30];

    do
    {
        printf("Bienvenido al SIMULACRO DEL PACIAL 2 version 1.0, por favor, seleccione un ejercicio: ");
        fflush(stdin);
        scanf("%i", &option);
        switch(option)
        {
        case 1:

            cantidadCargada = cargarAutomoviles(autos, 30);
            printf("Se cargaron %d automoviles.\n", cantidadCargada);

            break;
        case 2:
            mostrarAutomoviles(autos, cantidadCargada);
            break;
        case 3:
            cantidadCargada = cargarMatriz(matriz, &fila, &col);
            printf("Se cargaron %d numeros en la matriz \n",cantidadCargada);

            break;
        case 4:
            guardarAutomovilesCaros(autos, cantidadCargada);

            break;
        case 5:
            mostrarArchivo("autos_gamaAlta.bin");

            break;
        case 6:
            cantidadRegistros =contarRegistros("autos_gamaAlta.bin");
            printf("El archivo contiene %d registros.\n", cantidadRegistros);
            break;
        case 7:

            printf("Ingrese la marca a calcular el porcentaje: ");
            fflush(stdin);
            scanf("%s", marca);

            float porcentaje = calcularPorcentajeMarca("autos_gamaAlta.bin", marca);
            printf("El porcentaje de vehiculos de la marca %s es: %.2f%%\n", marca, porcentaje);
            break;

        default:
            printf("\n Porfavor ponga un numero valido \n");
            break;

        }
        printf("Desea realizar otro ejercicio precione 's' para si: ");
        fflush(stdin);
        scanf("%c", &yes);
    }
    while(yes == 'S'|| yes == 's');

    return 0;
}
///////////////////////////////////////////////////////////////////////////1 y 2///////////////////////////////////////////////////////////////////////////////////
int cargarAutomoviles(automovil autos[], int dimension)
{
    int cantidad = 0;
    char opcion;

    do
    {
        printf("Ingrese los datos del automovil %d:\n", cantidad + 1);

        printf("Modelo: ");
        fflush(stdin);
        scanf("%s", autos[cantidad].modelo);

        printf("Anio: ");
        fflush(stdin);
        scanf("%d", &autos[cantidad].anio);

        printf("Marca: ");
        fflush(stdin);
        scanf("%s", autos[cantidad].marca);

        printf("Precio: ");
        fflush(stdin);
        scanf("%f", &autos[cantidad].precio);

        cantidad++;

        printf("¿Desea cargar otro automovil? S/N: ");
        scanf(" %c", &opcion);
    }
    while (opcion == 'S' || opcion == 's');

    return cantidad;
}

void mostrarAutomoviles(automovil autos[], int cantidad)
{
    printf("\n|||---- Listado de autos ----|||\n");

    for (int i = 0; i < cantidad; i++)
    {
        printf("Automovil %d:\n", i + 1);
        printf("Modelo: %s\n", autos[i].modelo);
        printf("Año: %d\n", autos[i].anio);
        printf("Marca: %s\n", autos[i].marca);
        printf("Precio: %.2f\n\n", autos[i].precio);
    }
}
//////////////////////////////////////////////////////////////////////////   3   //////////////////////////////////////////////////////////////////////////////////
int cargarMatriz(int matriz[][10], int*fila, int*col)
{
    int cantidad= 0;

    printf("Ingrese el numero de filas de la matriz: ");
    fflush(stdin);
    scanf("%d",fila);

    printf("Ingrese el nmuero de Columnas de la matriz: ");
    fflush(stdin);
    scanf("%d",col);

    for (int i = 0; i < *fila; i++)
    {
        for (int j = 0; j < *col; j++)
        {
            printf("Ingrese un numero para la posicion (%d, %d): ", i, j);
            scanf("%d", &matriz[i][j]);
            cantidad++;
        }
    }

    return cantidad;
}
//////////////////////////////////////////////////////////////////////////   4 y 5   //////////////////////////////////////////////////////////////////////////////////

void guardarAutomovilesCaros(automovil autos[], int cantidad)
{
    FILE* archi;
    archi = fopen("autos_gamaAlta.bin", "wb");

    if (archi!= NULL)
    {
        fprintf(archi, "---- Autos con precio superior a $15,000.00 ----\n");

        for (int i = 0; i < cantidad; i++)
        {
            if (autos[i].precio > 15000.0)
            {
                fprintf(archi, "Modelo: %s\n", autos[i].modelo);
                fprintf(archi, "Anio: %d\n", autos[i].anio);
                fprintf(archi, "Marca: %s\n", autos[i].marca);
                fprintf(archi, "Precio: %.2f\n\n", autos[i].precio);
            }
        }

        fclose(archi);

        printf("Se han guardado los autos caros en el archivo.\n");
    }
    else
    {
        printf("Error al abrir el archivo.\n");
        return;
    }
}

void mostrarArchivo(char* autos_gamaAlta )
{
    FILE* archi;
    archi = fopen(autos_gamaAlta,"rb");

    if (archi != NULL)
    {
        automovil autoActual;

        while (fread(&autoActual, sizeof(autoActual),1,archi)==1)
        {
            printf("\n----------------------------------------------\n");

            printf("Modelo: %s\n", autoActual.modelo);
            printf("Anio: %d\n", autoActual.anio);
            printf("Marca: %s\n", autoActual.marca);
            printf("Precio: %.2f\n\n", autoActual.precio);

            printf("\n----------------------------------------------");
        }

        fclose(archi);
    }
    else
    {

        printf("Error al abrir el archivo.\n");
    }
}
//////////////////////////////////////////////////////////////////////////   6   //////////////////////////////////////////////////////////////////////////////////

int contarRegistros(char* autos_gamaAlta)
{
    FILE* archi;
    int tamanoArchivo;
    int tamanoRegistro;
    int cantidadRegistros;

    archi = fopen(autos_gamaAlta, "rb");

    if (archi!= NULL)
    {
        fseek(archi, 0, SEEK_END);
        tamanoArchivo = ftell(archi);

        tamanoRegistro = sizeof(automovil);
        cantidadRegistros = tamanoArchivo / tamanoRegistro;
        fclose(archi);

    }
    else
    {
        printf("Error al abrir el archivo.\n");
        return 0;
    }
    return cantidadRegistros;
}
//////////////////////////////////////////////////////////////////////////   7   //////////////////////////////////////////////////////////////////////////////////

float calcularPorcentajeMarca(char* autos_gamaAlta, char* marca)
{
    int cantidadRegistros = contarRegistros(autos_gamaAlta);
    int cantidadMarca = 0;

    automovil autoActual;

    FILE* archi = fopen(autos_gamaAlta, "rb");

    if (archi!= NULL)
    {
        while (fread(&autoActual, sizeof(automovil), 1, archi) == 1)
        {
            if (strcmp(autoActual.marca, marca) == 0)
            {
                cantidadMarca++;
            }
        }

        fclose(archi);
        float porcentaje = ((float)cantidadMarca / cantidadRegistros) * 100.0;
        return porcentaje;
    }
    else
    {
        printf("Error al abrir el archivo.\n");
        return 0.0;
    }

}

