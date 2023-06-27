#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct
{
    int numCamiseta;
    char nombre[30];
    char equipo[30];
    int edad;
} jugadorScaloneta;


int cargarMatrizChar (char matriz[][100],int filas,int col);
void cargarJugadores(char Scaloneta[]);
void verarchi(char Scaloneta[]);
void mostrarEquipos(char Scaloneta[], char nombreEquipos[]);
int cantid(char Scaloneta[]);
void buscajugador(char Scaloneta[], int dato);
int pasaje(char Scaloneta[], jugadorScaloneta edad[], int edada);
jugadorScaloneta Menordedad(char Scaloneta[]);
//void mostrarmenor (jugadorScaloneta a[],int val);

int main()
{
    int num;
    int ca;
    char yes;
    int col= 3;
    int fila= 3;
    int palabra;
    char matriz[fila][100];
    char arre[30];
    char equipos[30];
    int datazo;

    jugadorScaloneta edad[30];

    FILE *archi;
    strcpy(arre, "Scaloneta.bin");
    archi = fopen("Scaloneta.bin", "ab");

    do
    {
        printf("HOLA , ESTA ES LA PRACTICA DEL PARCIAL SELECIONES EL EJERCIO : ");
        fflush(stdin);
        scanf("%i", &num);
        switch(num)
        {
        case 1:
            palabra= cargarMatrizChar(matriz,fila,col);
            printf("Se han cargado %d palabras en la matriz.\n" , palabra);
            break;

        case 2:
            cargarJugadores(arre);
            verarchi(arre);

            break;
        case 3:
            printf("Ingrese el nombre del equipo: ");
            scanf("%s", equipos);
            mostrarEquipos(arre, equipos);

            break;
        case 4:
            verarchi(arre);
            ca = cantid(arre);
            printf("\n\nLa cantidad de regsitros en el archivo es de: %i", ca);
            break;
        case 5:
            verarchi(arre);
            printf("\nseleccione el numero de la pocision del jugador a buscar: ");
            fflush(stdin);
            scanf("%i", &ca);
            buscajugador(arre,ca);
            break;
        case 6:
            verarchi(arre);
            printf("\nseleccione la edad que desea ingresar: ");
            fflush(stdin);
            scanf("%i", &ca);
            ca = pasaje(arre,edad,ca);
            printf("\n\nLa cantidad de personas cargadas ak arreglo es de: %i ", ca);

            break;
        case 7:
         {
            jugadorScaloneta Menor = Menordedad(arre);
            printf("\nJugador de menor edad:");
            printf("\n--------------------------------------------------\n");
            printf("Numero de camiseta: %d\n", Menor.numCamiseta);
            printf("Nombre del jugador: %s\n", Menor.nombre);
            printf("Equipo: %s\n", Menor.equipo);
            printf("Edad: %d\n", Menor.edad);
            printf("--------------------------------------------------\n");
        }
            break;
        case 8:
            verarchi(arre);
            printf("\nIngrese el numero de camiseta que desea buscar: ");
            scanf("%i",&datazo);
            ca=buscaname(arre,datazo);
            if (ca==-1)
            {
                printf("\n El numero de camiseta NO se encontro en el archivo ");
            }
            else
            {
                printf("\nEl numero de camiseta se encontro en el archivo ");
            }
            break;
        }
        printf("Desea ver otro ejercicio? presione s para si ");
        fflush(stdin);
        scanf("%c", &yes);
    }
    while(yes=='s'|| yes=='S');


    return 0;
}
//////////////////////////////////////////////////// 1 ///////////////////////////////////////////////////////////
int cargarMatrizChar (char matriz[][100],int filas,int col)
{
    int contador = 0;
    int i, j;

    for(i=0;i<filas;i++)
    {
        for(j=0;j<col;j++)
        {
            printf("Ingrese la palabra que quiera: ");
            scanf("%s", matriz[i]);
            contador ++;
        }
    }
    return contador;
}
//////////////////////////////////////////////////// 2 ///////////////////////////////////////////////////////////

void cargarJugadores(char Scaloneta[])
{
    FILE *archi;
    archi = fopen(Scaloneta, "ab");
    char yes='s';
    jugadorScaloneta jugador;


    if(archi!=NULL)
    {
        while(yes=='s'||yes=='S')
        {
            printf("Ingrese el numero de camiseta del jugador: ");
        scanf("%d", &jugador.numCamiseta);

        printf("Ingrese el nombre del jugador: ");
        scanf("%s", jugador.nombre);

        printf("Ingrese el equipo del jugador: ");
        scanf("%s", jugador.equipo);

        printf("Ingrese la edad del jugador: ");
        scanf("%d", &jugador.edad);

            fwrite(&jugador, sizeof(jugador),1,archi);

            printf("Desea continuar?");
            fflush(stdin);
            scanf("%c", &yes);

        }
        fclose(archi);
    }
}

void verarchi(char Scaloneta[])
{
    FILE *archi;
    archi = fopen(Scaloneta, "rb");
    jugadorScaloneta jugador;


    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&jugador, sizeof(jugador),1,archi);

            if(!feof(archi))
            {
                printf("\n--------------------------------------------------\n");
                printf("\nNumero de camiseta : %d", jugador.numCamiseta);
                printf("\nNombre del jugador: %s", jugador.nombre);
                printf("\nEquipo: %s", jugador.equipo);
                printf("\nEdad: %i", jugador.edad);
                printf("\n--------------------------------------------------");
            }
        }
        fclose(archi);
    }

}
//////////////////////////////////////////////////// 3 ///////////////////////////////////////////////////////////

void mostrarEquipos(char Scaloneta[], char nombreEquipos[])
{
     FILE *archi;
    archi = fopen(Scaloneta, "rb");
    jugadorScaloneta jugador;
    if (archi!=NULL)
    {
        while(fread(&jugador,sizeof(jugador),1, archi)==1)
        {
            if(strcmp(jugador.equipo, nombreEquipos)==0)
            {
               printf("\n--------------------------------------------------\n");
                printf("\nNumero de camiseta : %d", jugador.numCamiseta);
                printf("\nNombre del jugador: %s", jugador.nombre);
                printf("\nEquipo: %s", jugador.equipo);
                printf("\nEdad: %i", jugador.edad);
                printf("\n--------------------------------------------------");
            }
        }
    }
    fclose(archi);
}
//////////////////////////////////////////////////// 4 ///////////////////////////////////////////////////////////
int cantid(char Scaloneta[])
{
    FILE *archi;
    archi = fopen(Scaloneta, "rb");
    int total;

    fseek(archi,0, SEEK_END);

    total=ftell(archi)/sizeof(jugadorScaloneta);
    fclose(archi);

    return total;
}
//////////////////////////////////////////////////// 5  ///////////////////////////////////////////////////////////

void buscajugador(char Scaloneta[], int dato)
{
    FILE *archi;
    archi = fopen(Scaloneta, "rb");
    int num=0;
    jugadorScaloneta jugador;
    int val=0;
    val=cantid(Scaloneta );

    if(archi!=NULL)
    {

        if(dato<val)
        {
            fseek(archi,sizeof(jugadorScaloneta)*(dato-1),SEEK_SET);
            fread(&jugador,sizeof(jugadorScaloneta),1,archi);

            num=ftell(archi);


            printf("\n\n\n\n\n\n\n");
            printf("\n--------------------------------------------------\n");
            printf("\nNumero de camiseta : %d", jugador.numCamiseta);
            printf("\nNombre del jugador: %s", jugador.nombre);
            printf("\nEquipo: %s", jugador.equipo);
            printf("\nEdad: %i", jugador.edad);
            printf("\n--------------------------------------------------");


        }
        else
        {
            printf("\n\nEL NUMERO SUPERA LA CANTIDAD DE JUGADORES!!!");
        }
        fclose(archi);
    }
}
//////////////////////////////////////////////////// 6 ///////////////////////////////////////////////////////////

int pasaje(char Scaloneta[], jugadorScaloneta edad[], int edada)
{
    FILE *archi;
    archi= fopen(Scaloneta, "rb");
    jugadorScaloneta jugador;
    int i=0;

    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&jugador,sizeof(jugadorScaloneta),1,archi);
            if(!feof(archi))
            {
                if(edada==jugador.edad)
                {
                    edad[i]=jugador;
                    i++;
                }
            }
        }
        fclose(archi);
    }
    return i;
}
//////////////////////////////////////////////////// 7 ///////////////////////////////////////////////////////////

jugadorScaloneta Menordedad(char Scaloneta[])
{
    FILE *archi;
    archi=fopen(Scaloneta,"rb");
    jugadorScaloneta jugador;
    jugadorScaloneta Menor;
    int menorEdad = 18;

    if(archi!= NULL)
    {
        while(fread(&jugador,sizeof(jugador),1,archi)==1)
        {
            if(jugador.edad < menorEdad)
            {
                menorEdad=jugador.edad;
                Menor=jugador;
            }
        }
        fclose(archi);
    }
    return Menor;
}

//////////////////////////////////////////////////// 8 ///////////////////////////////////////////////////////////
int buscaname(char Scaloneta [], int dato)
{
     FILE *archi;
    archi= fopen(Scaloneta, "rb");
    jugadorScaloneta jugador;

    if(archi!=NULL)
    {
        while(fread(&jugador,sizeof(jugadorScaloneta),1,archi)==1)
        {
            if(jugador.numCamiseta== dato)
            {
                fclose(archi);
                return 1;
            }
        }
        fclose(archi);
    }
   return -1;
}

