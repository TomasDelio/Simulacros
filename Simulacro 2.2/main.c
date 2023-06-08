#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int idSocio;
    char nombreYapellido[30];
    int categoria; //puede tomar los valores 1,2,3 o 4
    int edad;
} socio;


int cargarMatriz(int matriz[][10], int*fila, int*col);
float MatrizProm(int matriz[][10], int fila, int col);
void cargarArchivoSocios();
float calcularEdadPromedioCategoria(int categoria);
int contarRegistros();
void mostrarSocioEnPosicion(const char *nombreArchivo, int numeroRegistro);
int copiarSociosPorCategoria(const char *nombreArchivo, int categoria, socio *arregloSocios);
void mostrarArregloSocios(socio *arregloSocios, int cantidadSocios);
void copiarYMostrarSociosPorCategoria(const char *nombreArchivo, int categoria);
int buscarSocioPorNombre(const char *nombreArchivo, const char *nombreBuscado);


    int main()
{
    char yes;
    int option;
    int fila, col;
    int matriz[30][30];
    float promedio;
    int categoria;
    int cantidadRegistros;
    const char *nombreArchivo = "socios.bin";
    int numeroRegistro;
    char nombreBuscado[30];
    int idEncontrado;
    do
    {
        printf("Bienvenido al SIMULACRO DEL PACIAL 2 version 2.2, por favor, seleccione un ejercicio: ");
        fflush(stdin);
        scanf("%i", &option);
        switch(option)
        {
        case 1:
            cargarMatriz(matriz, &fila, &col);
            promedio= MatrizProm(matriz, fila, col);
            printf("El promedio de los elementos de la matriz es: %.2f\n", promedio);

            break;

        case 2:
            cargarArchivoSocios();
            break;
        case 3:
            printf("Ingrese la categoría para calcular la edad promedio de los socios: ");
            scanf("%d", &categoria);

            promedio=calcularEdadPromedioCategoria(categoria);
            printf("La edad promedio de los socios de la categoria %d es: %.2f\n", categoria, promedio);
            break;
        case 4:

            cantidadRegistros = contarRegistros("socios.bin");
            printf("La cantidad de registros en el archivo de socios es: %d\n", cantidadRegistros);
            break;
        case 5:
            printf("Ingrese el numero de registro a mostrar: ");
            scanf("%d", &numeroRegistro);
            mostrarSocioEnPosicion("socios.bin", numeroRegistro);
            break;
        case 6:
            printf("ignorar ,Va junto con el caso 7 asi que saltea al siguiente que esta todo junto jijos");
            break;
        case 7:
            printf("Ingrese la categoría de socios a copiar: ");
            scanf("%d", &categoria);
            copiarYMostrarSociosPorCategoria("socios.bin", categoria);

            break;
        case 8:

            printf("Ingrese el nombre del socio a buscar: ");
            fflush(stdin);
            scanf(" %[^\n]s", nombreBuscado);

            idEncontrado = buscarSocioPorNombre("socios.bin", nombreBuscado);
            if (idEncontrado != -1)
            {
                printf("El socio '%s' fue encontrado. ID: %d\n", nombreBuscado, idEncontrado);
            }
            else
            {
                printf("El socio '%s' no fue encontrado.\n", nombreBuscado);
            }
            break;
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
////////////////////////////////////////////////////////////////////////////////  1  /////////////////////////////////////////////////////////////////////
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

float MatrizProm(int matriz[][10], int fila, int col)
{
    int suma = 0;
    int total = fila * col;

    for (int i = 0; i < fila; i++)
    {
        for (int j = 0; j < col; j++)
        {
            suma += matriz[i][j];
        }
    }

    float prom = (float)suma / total;
    return prom;
}
////////////////////////////////////////////////////////////////////////////////  2  /////////////////////////////////////////////////////////////////////
void cargarArchivoSocios()
{
    FILE *archi;
    socio nuevoSocio;

    // Verificar si el archivo existe
    if ((archi = fopen("socios.bin", "rb")) != NULL)
    {
        fclose(archi);
        archi = fopen("socios.bin", "ab"); // Abrir el archivo en modo "append" para agregar registros al final
    }
    else
    {
        archi = fopen("socios.bin", "wb");  // Si el archivo no existe, crear uno nuevo
    }

    if (archi != NULL)
    {
        char yes= 's';
        while(yes == 'S'|| yes == 's')
        {

            printf("Ingrese el ID del socio: ");
            fflush(stdin);
            scanf("%d", &nuevoSocio.idSocio);

            printf("Ingrese el nombre y apellido del socio: ");
            fflush(stdin);
            scanf(" %[^\n]s", nuevoSocio.nombreYapellido);

            printf("Ingrese la categoría del socio: ");
            fflush(stdin);
            scanf("%d", &nuevoSocio.categoria);

            printf("Ingrese la edad del socio: ");
            fflush(stdin);
            scanf("%d", &nuevoSocio.edad);

            // Escribir el nuevo socio en el archivo
            fprintf(archi, "%d;%s;%d;%d\n", nuevoSocio.idSocio, nuevoSocio.nombreYapellido, nuevoSocio.categoria, nuevoSocio.edad);


            printf("¿Desea cargar otro socio? (s/n): ");
            scanf(" %c", &yes);
        }
    }
    fclose(archi);
    printf("Registros cargados exitosamente en el archivo socios.txt.\n");

    return;
}
////////////////////////////////////////////////////////////////////////////////  3  /////////////////////////////////////////////////////////////////////

float calcularEdadPromedioCategoria(int categoria)
{
    FILE *archi;
    socio socioActual;

    int sumaEdades = 0;
    int cantidadSocios = 0;
    float prom;

    archi = fopen("socios.bin", "rb");
    if (archi != NULL)
    {
        while (fscanf(archi, "%d;%[^;];%d;%d\n", &socioActual.idSocio, socioActual.nombreYapellido, &socioActual.categoria, &socioActual.edad) == 4)
        {
            if (socioActual.categoria == categoria)
            {
                sumaEdades += socioActual.edad;
                cantidadSocios++;
            }
        }
        fclose(archi);

        if (cantidadSocios > 0)
        {
            prom = (float) sumaEdades / cantidadSocios;
            return prom;
        }
        else
        {
            printf("No se encontraron socios en la categoría especificada.\n");
            return 0.0;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////  4  /////////////////////////////////////////////////////////////////////
int contarRegistros(const char *nombreArchivo)
{
    FILE *archi;
    int cantidadRegistros = 0;

    archi = fopen(nombreArchivo, "rb");
    if (archi != NULL)
    {
        fseek(archi, 0, SEEK_END);  // Mover el puntero de archivo al final del archivo
        long fileSize = ftell(archi);  // Obtener la posición actual del puntero (tamaño total del archivo en bytes)
        fclose(archi);

        int registroSize = sizeof(socio);  // Tamaño de cada registro en bytes
        cantidadRegistros = fileSize / registroSize;  // Calcular la cantidad de registros

        return cantidadRegistros;
    }
    else
    {
        return 0;
    }
}
////////////////////////////////////////////////////////////////////////////////  5  /////////////////////////////////////////////////////////////////////
void mostrarSocioEnPosicion(const char *nombreArchivo, int numeroRegistro)
{
    int cantidadRegistros = contarRegistros(nombreArchivo);

    if (cantidadRegistros > 0 && numeroRegistro >= 1 && numeroRegistro <= cantidadRegistros)
    {
        FILE *archi;
        socio socioActual;
        archi = fopen(nombreArchivo, "rb");

        if (archi != NULL)
        {
            fseek(archi, (numeroRegistro - 1) * sizeof(socio), SEEK_SET);
            fread(&socioActual, sizeof(socio), 1, archi);
            fclose(archi);

            printf("Datos del socio en la posicion %d:\n", numeroRegistro);
            printf("ID: %d\n", socioActual.idSocio);
            printf("Nombre y apellido: %s\n", socioActual.nombreYapellido);
            printf("Categoría: %d\n", socioActual.categoria);
            printf("Edad: %d\n", socioActual.edad);
        }
    }
    else
    {
        printf("No se pudo mostrar el socio en la posicion %d. La cantidad de registros es insuficiente o el numero de registro es invalido.\n", numeroRegistro);
    }
}
////////////////////////////////////////////////////////////////////////////////  6 y 7  /////////////////////////////////////////////////////////////////////

int copiarSociosPorCategoria(const char *nombreArchivo, int categoria, socio *arregloSocios)
{
    FILE *archi;
    int cantidadRegistros = 0;

    archi = fopen(nombreArchivo, "rb");
    if (archi != NULL)
    {
        socio socioActual;

        while (fread(&socioActual, sizeof(socio), 1, archi) == 1)
        {
            if (socioActual.categoria == categoria)
            {
                arregloSocios[cantidadRegistros] = socioActual;
                cantidadRegistros++;
            }
        }
        fclose(archi);
    }
    return cantidadRegistros;
}

void mostrarArregloSocios(socio *arregloSocios, int cantidadSocios)
{
    for (int i = 0; i < cantidadSocios; i++)
    {
        printf("Socio %d:\n", i + 1);
        printf("ID: %d\n", arregloSocios[i].idSocio);
        printf("Nombre y apellido: %s\n", arregloSocios[i].nombreYapellido);
        printf("Categoría: %d\n", arregloSocios[i].categoria);
        printf("Edad: %d\n", arregloSocios[i].edad);
        printf("\n");
    }
}
////////////////////////////////////////////////////////////////////////////////  8  /////////////////////////////////////////////////////////////////////
void copiarYMostrarSociosPorCategoria(const char *nombreArchivo, int categoria)
{
    socio arregloSocios[30]; // Ajusta el tamaño según tus necesidades

    int cantidadCopiados = copiarSociosPorCategoria(nombreArchivo, categoria, arregloSocios);

    printf("Socios de la categoria %d:\n", categoria);
    mostrarArregloSocios(arregloSocios, cantidadCopiados);
}

int buscarSocioPorNombre(const char *nombreArchivo, const char *nombreBuscado)
{
    FILE *archi;
    socio socioActual;

    archi = fopen(nombreArchivo, "rb");
    if (archi != NULL)
    {
        while (fread(&socioActual, sizeof(socio), 1, archi) == 1)
        {
            if (strcmp(socioActual.nombreYapellido, nombreBuscado) == 0)
            {
                fclose(archi);
                return socioActual.idSocio;
            }
        }
        fclose(archi);
    }
    else
    {
        return -1;
    }
}

