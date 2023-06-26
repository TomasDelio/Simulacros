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

int fila=3;
int col=3;

void cargamatrix(int m[fila][col], int dim);
void vermatrix(int m[fila][col], int val);
float promedio(int m[fila][col], int val);

void cargArchi(char thearchies[]);
void verarchi(char thearchies[]);

float edadpromedio(char thearchies[], int categoria);

int cantid(char thearchies[]);

void buscasocio(char thearchies[], int dato);

int pasaje(char thearchies[], socio categorico[], int cate);
void mostrarp(socio a[], int val);

int buscaname(char thearchies[], int dato);





int main()
{
    char yes;
    int option;
    int matrix[fila][col];
    char arre[30];
    float prom;
    int num;
    socio categorico[30];
    char datazo[30];

    FILE *archi;
    strcpy(arre, "the Archies.bin");
    archi = fopen("the Archies.bin", "ab");

    do
    {
        printf("Bienvenido al SIMULACRO DEL PACIAL 2 version 2.2, por favor, seleccione un ejercicio: ");
        fflush(stdin);
        scanf("%i", &option);
        switch(option)
        {

        case 1:

            cargamatrix(matrix, 3);
            vermatrix(matrix, 3);
            prom = promedio(matrix, 3);
            printf("\nEl promedio de los numero agregados a la matriz es de: %.2f .", prom);
            break;

        case 2:
            cargArchi(arre);
            verarchi(arre);
            break;

        case 3:
            cargArchi(arre);
            printf("\n\nCategoria que desea promediar: ");
            fflush(stdin);
            scanf("%i", &num);
            prom = edadpromedio(arre, num);
            printf("\n\nEl promedio de edad del socio de la categoria %i es de %.2f .", num, prom);
            break;

        case 4:

            verarchi(arre);
            num = cantid(arre);
            printf("\n\nLa cantidad de regsitros en el archivo es de: %i", num);
            break;

        case 5:

            verarchi(arre);
            printf("\nseleccione el numero de registro a buscar: ");
            fflush(stdin);
            scanf("%i", &num);
            buscasocio(arre,num);
            break;

        case 6:
            verarchi(arre);
            printf("\nseleccione la categoria que desea ingresar: ");
            fflush(stdin);
            scanf("%i", &num);
            num = pasaje(arre,categorico,num);
            printf("\n\nLa cantidad de personas cargadas ak arreglo es de: %i ", num);
            break;
        case 7:

            verarchi(arre);
            printf("\nseleccione la categoria que desea ingresar: ");
            fflush(stdin);
            scanf("%i", &num);
            num = pasaje(arre,categorico,num);
           //SOLO AÑADIMOS EL MOSTRARP LO OTROS ES IGUAL AL 6
            mostrarp(categorico,num);
            break;
        case 8:
            verarchi(arre);
            printf("\nseleccione el nombre que desea buscar: ");
            fflush(stdin);
            gets(datazo);
            num=buscaname(arre,datazo);
            if(num==-1)
            {
            printf("\n\nEl nombre no se encontro en el arreglo!!!");
            }else
            {
            printf("\n\nLa ID del socio nuscado es: %i", num);

        }


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
void cargamatrix(int m[fila][col], int dim)
{
    int i, j;

    while(i<dim)
    {
        for(i=0; i<dim; i++)
        {
            printf("Columna %i\n", i);

            for(j=0; j<dim; j++)
            {
                printf("Cargue un numero: ");
                fflush(stdin);
                scanf("%i", &m[i][j]);
            }
        }
    }
}

void vermatrix(int m[fila][col], int val)
{
    int i, j;

    printf("\n\n");

    for(i=0; i<val; i++)
    {
        for(j=0; j<val; j++)
        {
            printf("|%i|", m[i][j]);
        }
        printf("\n\n");
    }
}

float promedio(int m[fila][col], int val)
{
    int i, j;
    float cont, total;
    float jota=0;

    printf("\n\n");

    for(i=0; i<val; i++)
    {
        for(j=0; j<val; j++)
        {
            cont=cont+ m[i][j];
            jota++;
        }
    }

    total=cont/jota;

    return total;
}

////////////////////////////////////////////////////////////////////////////////  2  /////////////////////////////////////////////////////////////////////
void cargArchi(char thearchies[])
{
    FILE *archi;
    archi = fopen(thearchies, "ab");
    char yes='s';
    socio nuevo;


    if(archi!=NULL)
    {
        while(yes=='s'||yes=='S')
        {
            printf("Ingrese el numero de id del socio: ");
            fflush(stdin);
            scanf("%i", &nuevo.idSocio);

            printf("Ingrese el nombre y apellido del socio: ");
            fflush(stdin);
            gets(nuevo.nombreYapellido);

            printf("Ingrese la categoria del socio: ");
            fflush(stdin);
            scanf("%i", &nuevo.categoria);

            printf("Ingrese la edad del socio: ");
            fflush(stdin);
            scanf("%i", &nuevo.edad);

            fwrite(&nuevo, sizeof(socio),1,archi);

            printf("Desea continuar?");
            fflush(stdin);
            scanf("%c", &yes);

        }
        fclose(archi);
    }
}

void verarchi(char thearchies[])
{
    FILE *archi;
    archi = fopen(thearchies, "rb");
    socio nuevo;


    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&nuevo, sizeof(socio),1,archi);

            if(!feof(archi))
            {
                printf("\n--------------------------------------------------\n");
                printf("\nId socio: %i", nuevo.idSocio);
                printf("\nNombre y Apellido: %s", nuevo.nombreYapellido);
                printf("\ncategoria: %i", nuevo.categoria);
                printf("\nEdad: %i", nuevo.edad);
                printf("\n--------------------------------------------------");
            }
        }
        fclose(archi);
    }

}
////////////////////////////////////////////////////////////////////////////////  3  /////////////////////////////////////////////////////////////////////
float edadpromedio(char thearchies[], int categoria)
{
    FILE *archi;
    archi = fopen(thearchies, "rb");
    socio capo;
    float edades=0;
    float jota=0;


    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&capo, sizeof(socio),1,archi);
            if(!feof(archi))
            {
                if(capo.categoria==categoria)
                {
                    edades=edades+capo.edad;

                    jota++;

                }
            }
        }
        fclose(archi);
    }


    jota=edades/jota;

    return jota;
}
////////////////////////////////////////////////////////////////////////////////  4  /////////////////////////////////////////////////////////////////////
int cantid(char thearchies[])
{
    FILE *archi;
    archi = fopen(thearchies, "rb");
    int total;

    fseek(archi,0, SEEK_END);

    total=ftell(archi)/sizeof(socio);
    fclose(archi);

    return total;
}

////////////////////////////////////////////////////////////////////////////////  5  /////////////////////////////////////////////////////////////////////
void buscasocio(char thearchies[], int dato)
{
    FILE *archi;
    archi = fopen(thearchies, "rb");
    int num=0;
    socio nuevo;
    int val=0;
    val=cantid(thearchies);

    if(archi!=NULL)
    {

        if(dato<val)
        {
            fseek(archi,sizeof(socio)*(dato-1),SEEK_SET);
            fread(&nuevo,sizeof(socio),1,archi);

            num=ftell(archi);


            printf("\n\n\n\n\n\n\n");
            printf("\n--------------------------------------------------\n");
            printf("\nId socio: %i", nuevo.idSocio);
            printf("\nNombre y Apellido: %s", nuevo.nombreYapellido);
            printf("\ncategoria: %i", nuevo.categoria);
            printf("\nEdad: %i", nuevo.edad);
            printf("\n--------------------------------------------------");


        }
        else
        {
            printf("\n\nEL NUMERO SUPERA LA CANTIDAD DE SOCIOS!!!");
        }
        fclose(archi);
    }
}
////////////////////////////////////////////////////////////////////////////////  6 y 7  /////////////////////////////////////////////////////////////////////
int pasaje(char thearchies[], socio categorico[], int cate)
{
    FILE *archi;
    archi= fopen(thearchies, "rb");
    socio nuevo;
    int i=0;

    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&nuevo,sizeof(socio),1,archi);
            if(!feof(archi))
            {
                if(cate==nuevo.categoria)
                {
                    categorico[i]=nuevo;
                    i++;
                }
            }
        }
        fclose(archi);
    }
    return i;
}


void mostrarp(socio a[], int val)
{
    int i=0;

    while(i<val)
    {
            printf("\n");
            printf("\n............................................................\n");
            printf("\nId socio: %i", a[i].idSocio);
            printf("\nNombre y Apellido: %s", a[i].nombreYapellido);
            printf("\ncategoria: %i", a[i].categoria);
            printf("\nEdad: %i", a[i].edad);
            printf("\n............................................................\n");
            printf("\n");
            i++;
    }
}

////////////////////////////////////////////////////////////////////////////////  8  /////////////////////////////////////////////////////////////////////
int buscaname(char thearchies[], int dato)
{
     FILE *archi;
    archi= fopen(thearchies, "rb");
    socio nuevo;
    int i=0;
    int num;

    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&nuevo,sizeof(socio),1,archi);
            if(!feof(archi))
            {
                if(strcmpi(nuevo.nombreYapellido,dato)==0)
                {
                    num=nuevo.idSocio;
                    i++;
                }
            }
        }
        fclose(archi);
    }

    if(num==0)
    {
        num=num-1;
    }
    return num;
}

