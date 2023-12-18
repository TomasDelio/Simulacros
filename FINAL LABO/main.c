#include <stdio.h>
#include <string.h>
#include "pila.h"
typedef struct
{
    int identificador;
    char categoria[20];
    char nombre[10];
    int precio;
} Producto;

void cargarProducto(Producto *productos, int *cant);
void ordenarProductosPorIdentificador(Producto *productos, int cant);
void mostrarProductos(Producto productos[], int cant);
int obtenerCantidadRegistrosEnArchivo(char *nombreArchivo);
int buscarPorRangoDePrecios(const char *nombreArchivo, int rangoInicio, int rangoFin, int *ids, int *precios);

int main()
{
    Producto productos[100];
    int cant = 0;
    char continuar = 's';

    const char *nombreArchivo = "TOLEDO";

    int rangoInicio = 50;
    int rangoFin = 200;

    int ids[39];
    int precios[39];
    int cantidadEncontrada;

    int posicion;

    char matriz[5][20];  // Ejemplo de matriz de 5 filas y 20 columnas, ajusta según tus necesidades
    int filas = 5;       // Número de filas de la matriz
    int columnas = 20;


    do
    {
        printf("\n----- Menú -----\n");
        printf("1. Cargar producto\n");
        printf("2. Ordenar productos por identificador\n");
        printf("3. Buscar por rango de precios\n");
        printf("4. Modificar producto en archivo\n");
        printf("5. Cargar matriz de tipo char\n");
        printf("6. Contar coincidencias en matriz\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf(" %c", &continuar);

        switch (continuar)
        {
        case '1':
            cargarProducto(productos, &cant);
            mostrarProductos(productos, cant);
            break;

        case '2':
            ordenarProductosPorIdentificador(productos, cant);
            printf("\nProductos ordenados por identificador:\n");
            mostrarProductos(productos, cant);
            break;

        case '3':
            cantidadEncontrada = buscarPorRangoDePrecios(nombreArchivo, rangoInicio, rangoFin, ids, precios);
            mostrarResultadosBusqueda(ids, precios, cantidadEncontrada);
            break;
        case '4':
            printf("Ingrese la posición del registro a modificar: ");
            scanf("%d", &posicion);

            modificarProductoEnArchivo(nombreArchivo, posicion);
            break;

        case '5':
            cargarMatrizChar(matriz, filas, columnas);
            printf("Matriz cargada exitosamente.\n");
            break;

        case '6':
            printf("Coincidencias encontradas: %d\n", contarCoincidencias(matriz, filas, columnas, productos, cant));
            break;

        case '0':
            printf("Saliendo del programa.\n");
            break;

        default:
            printf("Opción no válida. Por favor, seleccione una opción válida.\n");
            break;
        }
    }
    while (continuar != '0');

    return 0;

}

void mostrarResultadosBusqueda(int *ids, int *precios, int cantidadEncontrada)
{
    if (cantidadEncontrada > 0)
    {
        printf("Productos encontrados:\n");
        for (int i = 0; i < cantidadEncontrada; i++)
        {
            printf("ID: %d, Precio: %d\n", ids[i], precios[i]);
        }
        printf("Total de productos encontrados: %d\n", cantidadEncontrada);
    }
    else
    {
        printf("No se encontraron productos en el rango de precios especificado.\n");
    }
}

void cargarProducto(Producto *productos, int *cant)
{
    Producto nuevoProducto;
    int i = 0;

    printf("Ingrese el identificador del producto: ");
    scanf("%d", &nuevoProducto.identificador);

    printf("Ingrese la categoría del producto: ");
    scanf("%s", nuevoProducto.categoria);

    do
    {
        printf("Ingrese el nombre del producto: ");
        scanf("%s", nuevoProducto.nombre);

        i = 0;
        while (i < *cant)
        {
            if (strcmp(nuevoProducto.nombre, productos[i].nombre) == 0)
            {
                printf("Ya existe un producto con el mismo nombre. Intente de nuevo.\n");
                i++;
            }
            else
            {
                i++;
            }
        }
    }
    while (i < *cant);

    do
    {
        printf("Ingrese el precio del producto: ");
        scanf("%d", &nuevoProducto.precio);

        if (nuevoProducto.precio < 0 || nuevoProducto.precio > 1000000)
        {
            printf("El precio debe estar en el rango de 0 a 1000000. Intente de nuevo.\n");
        }

    }
    while (nuevoProducto.precio < 0 || nuevoProducto.precio > 1000000);

    productos[*cant] = nuevoProducto;
    (*cant)++;

    printf("Producto cargado exitosamente.\n");
}

void mostrarProductos(Producto productos[], int cant)
{
    int i = 0;

    printf("\n\n");
    printf("\n-----------------Productos cargado-----------------\n");
    while (i < cant)
    {
        printf("\nID: %d", productos[i].identificador);
        printf("\nCategoría: %s", productos[i].categoria);
        printf("\nNombre: %s", productos[i].nombre);
        printf("\nPrecio: %d", productos[i].precio);
        i++;
    }
}

void ordenarProductosPorIdentificador(Producto *productos, int cant)
{
    int i = 0;
    int j = 0;
    int minIndex;
    Producto temp;

    while (i < cant - 1)
    {
        minIndex = i;
        j = i + 1;

        while (j < cant)
        {
            if (productos[j].identificador < productos[minIndex].identificador)
            {
                minIndex = j;
            }
            j++;
        }

        // Intercambiar los elementos
        temp = productos[minIndex];
        productos[minIndex] = productos[i];
        productos[i] = temp;

        i++;
    }
}

int obtenerCantidadRegistrosEnArchivo(char *nombreArchivo)
{
    int i = -1;
    FILE *archivo = fopen(nombreArchivo, "rb");

    if (archivo != NULL)
    {
        fseek(archivo, 0, SEEK_END); // Mover el indicador al final del archivo
        int cantidadRegistros = ftell(archivo) / sizeof(Producto);
        fclose(archivo);

        i = cantidadRegistros;
    }

    // Si no se pudo abrir el archivo
    return i;
}

int buscarPorRangoDePrecios(const char *nombreArchivo, int rangoInicio, int rangoFin, int *ids, int *precios)
{
    int i = 0;
    int cantidadEncontrada = 0;

    FILE *archivo = fopen(nombreArchivo, "rb");

    if (archivo != NULL)
    {
        Producto productos;

        while (fread(&productos, sizeof(Producto), 1, archivo) == 1)
        {
            if (productos.precio >= rangoInicio && productos.precio <= rangoFin)
            {
                ids[cantidadEncontrada] = productos.identificador;
                precios[cantidadEncontrada] = productos.precio;
                cantidadEncontrada++;
            }
        }

        fclose(archivo);
    }
    return cantidadEncontrada;
}


void modificarProductoEnArchivo(const char *nombreArchivo, int posicion)
{
    FILE *archivo = fopen(nombreArchivo, "r+b");

    if (archivo != NULL)
    {
        int cantidadRegistros = obtenerCantidadRegistrosEnArchivo(nombreArchivo);

        if (posicion >= 0 && posicion < cantidadRegistros)
        {
            Producto producto;

            fseek(archivo, posicion * sizeof(Producto), SEEK_SET);// Mover el puntero al registro correspondiente

            fread(&producto, sizeof(Producto), 1, archivo);// Leer el registro existente

            printf("Información actual del producto:\n");
            printf("ID: %d\n", producto.identificador);
            printf("Categoría: %s\n", producto.categoria);
            printf("Nombre: %s\n", producto.nombre);
            printf("Precio: %d\n", producto.precio);

            char opcion;
            printf("¿Qué desea modificar? (P: Precio, C: Categoría, A: Ambos, N: Ninguno): ");
            scanf(" %c", &opcion);

            switch (opcion)
            {
            case 'P':
                printf("Ingrese el nuevo precio: ");
                scanf("%d", &producto.precio);
                break;

            case 'C':
                printf("Ingrese la nueva categoría: ");
                scanf("%s", producto.categoria);
                break;

            case 'A':
                printf("Ingrese el nuevo precio: ");
                scanf("%d", &producto.precio);

                printf("Ingrese la nueva categoría: ");
                scanf("%s", producto.categoria);
                break;

            case 'N':
                // No se realiza ninguna modificación
                break;

            default:
                printf("Opción no valida.\n");
                fclose(archivo);
            }

            fseek(archivo, posicion * sizeof(Producto), SEEK_SET);// Mover el puntero al inicio del registro para sobrescribirlo

            fwrite(&producto, sizeof(Producto), 1, archivo);// Escribir el registro modificado en el archivo

            printf("Producto modificado exitosamente.\n");
        }
        else
        {
            printf("La posición ingresada no es válida.\n");
        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
}

void cargarMatrizChar(char matriz[][20], int filas, int columnas)
{
    for (int i = 0; i < filas; ++i)
    {
        for (int j = 0; j < columnas; ++j)
        {
            printf("Ingrese un valor para la posición (%d, %d): ", i, j);
            scanf("%s", matriz[i]);
        }
    }
}

int contarCoincidencias(char matriz[][20], int filas, int columnas, Producto productos[], int cant)
{
    int contador = 0;

    for (int i = 0; i < filas; ++i)
    {
        for (int j = 0; j < columnas; ++j)
        {
            for (int k = 0; k < cant; ++k)
            {
                if (strcmp(matriz[i], productos[k].nombre) == 0)
                {
                    contador++;

                    break;  // Rompe el bucle interno si se encuentra una coincidencia
                }
            }
        }
    }

    return contador;
}


float calcularPromedioPreciosPorCategoria(const char* nombreArchivo, const char* categoria)
{
    Producto producto;
    Pila pila;
    inicpila(&pila);
    int totalPrecios = 0;
    int cantidadProductos = 0;
    float promedio;
    FILE* archivo = fopen(nombreArchivo, "rb");

    if (archivo != NULL)
    {
        while (fread(&producto, sizeof(Producto), 1, archivo) == 1)
        {
            if (strcmp(producto.categoria, categoria) == 0)
            {
                apilar(&pila, producto.precio);
                totalPrecios += producto.precio;
                cantidadProductos++;
            }
        }
    }

    fclose(archivo);

    if (cantidadProductos != 0)
    {
        promedio = (float)totalPrecios / cantidadProductos;
        desapilar(&pila);
    }
    return promedio;
}

/*1. Hacer una función que permita la carga manual de nuevos productos a un arreglo con las siguientes pautas:
    La función debe permitir cargar de a uno, mientras el usuario lo desee.
    El identificador debe elegirlo el usuario.
    Validar que no se ingresen productos con el mismo nombre.
    Verificar que el precio no sea negativo ni mayor a 1.000.000
    Modularizar el código.
2. Hacer una función que ordene el arreglo de Productos por el método de selección, usando el identificador como criterio de ordenación. Modularizar
3. Realizar una función que devuelva la cantidad de registros cargados en el archivo. NO debe recorrerlo todo para contar los registros.
4. Realizar una función que reciba un rango de precios y busque dentro del archivo los productos cuyo precio esté dentro de ese intervalo. Al localizarlos, pasar su id a un arreglo y su precio a otro, considerando que estos trabajarán como arreglos paralelos. Retornar la cantidad de productos encontrados.
5. Realizar una función que reciba por parámetro una posición (nro de registro) y busqué en un archivo cargado al producto correspondiente. Se deberá verificar que la posición recibida sea menor a la cant de registros que posea el archivo. La función deberá permitir modificar el precio del producto, la categoría o ambos campos (según lo desee el usuario) y luego sobreescribir el registro existente en el archivo. De no encontrar el producto, se deberá notificar al usuario.
6.
    a) Hacer una función que reciba una matriz de tipo char y permite cargarla con valores siempre que el usuario lo desee. (10 Pts)
    b) Hacer una función que reciba una matriz de tipo char previamente cargada y un arreglo de Productos. Deberá retornar la cantidad de veces que en la matriz existan nombres que coincidan con los nombres de los productos del arreglo. (10 Pts)
7. Realizar una función que pase el precio de todos los productos del archivo de una determinada categoría a una Pila para, posteriormente, calcular y retornar un promedio de precios. La categoría debe recibirse por parámetro.
8. Hacer un main () que demuestre un correcto funcionamiento de las funciones.*/
