#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

int carga(int arr[]);
void veraareglo(int arr[],int val);
Pila cargarpila (Pila *a);
void mostrarpila(Pila *a);
int copipila(Pila *a,int arr[]);
int autito(int anio[],float km[]);
void verfloat(float arr[],int val);
Pila organz(Pila a, Pila *b,Pila *c);


int main()
{
    Pila pilita;
    Pila pilota;
    Pila pileta;
    inicpila(&pileta);
    inicpila(&pilita);
    inicpila(&pilota);

    int num=0;
    char yes;
    int arr[50];
    int val;
    int anio[99];
    float km[99];




    do
    {
        printf("Bienvenido al simulador n3 alias el parcial de la comision 6 jijos , elija el ejercio que quiera hacer : ");
        fflush(stdin);
        scanf("%i", &num);
        switch(num)
        {
        case 1:
            val=carga(arr);
            printf("Los numeros dentro del arreglo son :  ");
            veraareglo(arr,val);

            break;
        case 2:
            cargarpila(&pilita);
            printf("La pila cargada: \n");

            break;
        case 3:
            cargarpila(&pilita);
            mostrar(&pilita);
            val=copipila(&pilita,arr);
            if(val==1)
            {
                printf("\nEl total de elementos cargados al arreglo es par\n");
            }
            else
            {
                printf("\nEl total de elementos cargados al arreglo es impar\n");
            }

            break;
        case 4:
            val=autito(anio,km);
            printf("\nLa cantidad de autos ingresados fue de %i\n", val);

            break;
        case 5:
            pilota=organz(pilota,&pilita,&pileta);
            printf("MULTIPLOS DE 10");
            mostrar(&pilota);
            printf("NUMEROS PAR PERO NO MULTIPLOS DE 10");
            mostrar(&pilita);
            printf("IMPARES");
            mostrar(&pileta);

            break;



        }
        printf("Desea continuar?Presione S:  ");
        fflush(stdin);
        scanf("%c",&yes);

    }
    while(yes=='s'||yes=='S');
    return 0;
}
//////////////////////////////////////FUNCIONES TIME/////////////////////////////////////////
//////////////////////////////////////////PUNTO 1////////////////////////////////////////////
int carga(int arr[])
{
    int i=0;
    int num=0;
    char yes;
    int val;
    do
    {
        printf("Ingrese un numero ");
        fflush(stdin);
        scanf("%i",&num);
        if(val<0)
        {
            printf("\nNumero invalido");
        }
        else
        {
            arr[i]=num;
            i++;

        }
        printf("Desea continuar?Presione S:  ");
        fflush(stdin);
        scanf("%c",&yes);

    }
    while(yes=='s' || yes=='S');
    return i;
}


int validacion (int num)
{
    int val=0;
    if(num>0 && num<=50)
    {
        val=1;
    }
    else
    {
        val=0;
    }
    return val;
}


void veraareglo(int arr[],int val)
{
    int i=0;
    while(i<val)
    {
        printf("|%i|",arr[i]);
        i++;
    }
    printf("\n\n\n");
}
//////////////////////////////////////////PUNTO 2////////////////////////////////////////////

Pila cargarpila (Pila *a)
{
    char yes;

    do
    {
        leer(a);
        printf("Quiere ingresar mas elementos a la pila? Presione s : ");
        fflush(stdin);
        scanf("%c",&yes);
    }
    while(yes=='s' || yes=='S');
}


void mostrarpila(Pila *a)
{
    Pila aux;
    inicpila(&aux);

    printf("|TOPE|\n");
    while(!pilavacia(a))
    {
        printf("(|%i|)\n",tope(a));
        apilar(&aux,desapilar(a));
    }
    printf("|Base|\n");
    while(!pilavacia(&aux))
    {
        apilar(a,desapilar(&aux));
    }
}

//////////////////////////////////////////PUNTO 3////////////////////////////////////////////

int copipila(Pila *a,int arr[])
{
    int i=0;
    Pila aux;
    inicpila(&aux);
    int totale=0;
    while(!pilavacia(a))
    {
        if(tope(a)>96 && tope(a)<123)
        {
            arr[i]=tope(a);
            i++;
            apilar(&aux,desapilar(a));

        }
        else
        {
            apilar(&aux,desapilar(a));
        }

    }
    printf("\n\nElementos que se cargaron al arreglo: %i\n\n", i);
    if(i%2==0)
    {
        totale=1;
    }
    else
    {
        totale=0;
    }
    return totale;
}
//////////////////////////////////////////PUNTO 4////////////////////////////////////////////
int autito(int anio[],float km[])
{
    int i=0;
    char yes;

    do
    {
        printf("\n\ningrese el anio de fabricacion de su vehiculo: ");
        fflush(stdin);
        scanf("%i", &anio[i]);

        printf("\n\nIngrese el kilometraje: ");
        fflush(stdin);
        scanf("%f", &km[i]);

        i++;

        printf("\n\nDesea ingresar otro numero? Presione 'S', para si:  ");
        fflush(stdin);
        scanf("%c", &yes);
    }
    while(yes=='s'|| yes=='S' && i<=50);

    return i;
}
void verfloat(float arr[],int val)
{
    int i=0;
    printf("\n\n");
    while(i<val)
    {
        printf("|%.2f|", arr[i]);
        i++;
    }
    printf("\n\n");
}

//////////////////////////////////////////PUNTO 5////////////////////////////////////////////

Pila organz(Pila a, Pila *b,Pila *c)
{
    int i=0;
    int num=0;
    char yes;

    do
    {
        printf("Ingrese un numero en la pila: ");
        fflush(stdin);
        scanf("%i",&num);
        if((num%10)==0)
        {
            apilar(&a,num);
        }
        else if(num%2==0 && num%10!=0)
        {
            apilar(b,num);
        }
        else
        {
            apilar(c,num);
        }

        printf("DESEA INGRESAR OTRO NUMERO A LA PILA? Presione S para si: ");
        fflush(stdin);
        scanf("%c", &yes);
    }
    while(yes=='s'||yes=='S');
    return a;
}


