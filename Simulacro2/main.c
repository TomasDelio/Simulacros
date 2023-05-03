#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

int carganota (int arr[]);
void verarr(int arr[], int val);
int validacioneitors3000 (int num);
Pila copipila(Pila *a, Pila d, int arr[], int val);
int gerardo(int arr[],int val);
Pila organz(Pila a, Pila *b,Pila *c);
int pilarreglo(Pila *b,int arr[]);
int arrereves (int arr[],int val);


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
    int val;
    int arr[99];
    int i=0;

    do
    {
        printf("ESTO ES UNA SIMULACION O NO? choose your point: ");
        fflush(stdin);
        scanf("%i", &num);
        switch(num)
        {
        case 1:
            val=carganota(arr);
            verarr(arr,val);
            break;
        case 2:
            val=carganota(arr);
            pilita=copipila(&pilota, pilita,arr,val);
            printf("Desaprobados UFA");
            mostrar(&pilota);
            printf("Aprobados yeeei");
            mostrar(&pilita);
            break;
        case 3:
            val=carganota(arr);
            num=gerardo(arr,val);
            printf("\n\nEl numero mas alto es el %i\n\n", num);
            break;
        case 4:
            pilota=organz(pilota,&pilita,&pileta);
            mostrar(&pilota);
            mostrar(&pilita);
            mostrar(&pileta);

            break;
        case 5:
            pilota=organz(pilota,&pilita,&pileta);
            printf("\n\nPILA CARGADA");
            mostrar(&pilita);
            val=pilarreglo(&pilita,arr);
            printf("\n\nPILA DESPUES DE LA FUNCION");
            mostrar(&pilita);
            printf("\n\nARREGLO CARGADO CON NUMEROS ENTRE 4 Y 48 INCLUSIVE");
            verarr(arr, val);
            break;
        case 6:

            do
            {
                printf("increse un numero al arreglo ");
                fflush(stdin);
                scanf("%i", &arr[i]);
                i++;
                printf("DESEA INGRESAR OTRO numerito? Presione S para si: ");
                fflush(stdin);
                scanf("%c", &yes);
            }
            while(yes=='s'||yes=='S');
            num = arrereves(arr, i);
            printf("\n\nEl promedio es %i\n\n", num);

            break;

        }
        printf("DESEA CONTINUAR? Presione S para si: ");
        fflush(stdin);
        scanf("%c", &yes);

    }
    while(yes=='s'||yes=='S');
    return 0;
}

int carganota (int arr[])
{
    int i=0;
    int num=0;
    int claro=0;
    char yes;
    do
    {
        printf("Ingrese la nota: ");
        fflush(stdin);
        scanf("%i", &num);
        claro=validacioneitors3000(num);

        if(claro==0)
        {
            printf("\nNumero invalido, por favor ponga una nota valida master");

        }
        else
        {
            printf("\nNumero es valido ");
            arr[i]=num;
            i++;
        }

        printf("DESEA INGRESAR OTRA NOTITA? Presione S para si: ");
        fflush(stdin);
        scanf("%c", &yes);
    }
    while(yes=='s'||yes=='S');
    return i;
}

int validacioneitors3000(int num)
{
    int val=0;
    if(num>0 && num<11)
    {
        val=1;

    }
    else
    {
        val=0;
    }
    return val;
}

void verarr(int arr[], int val)
{
    int i=0;
    while(i<val)
    {
        printf("|%i|", arr[i]);
        i++;
    }
    printf("\n\n");
}

Pila copipila(Pila *a, Pila d, int arr[], int val)
{
    int i=0;

    while(i<val)
    {
        if(arr[i]>=6)
        {
            apilar(&d, arr[i]);
        }
        else
        {
            apilar(a, arr[i]);
        }
        i++;
    }
    return d;
}

int gerardo(int arr[],int val)
{
    int i=val-1;
    int mayor=arr[i];
    while(i>=0)
    {
        if(mayor>=arr[i])
        {
            i--;
        }
        else
        {
            mayor=arr[i];
            i--;
        }
    }
    return mayor;
}


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

int pilarreglo(Pila *b,int arr[])
{
    int i;
    Pila aux;
    inicpila(&aux);
    Pila aux1;
    inicpila(&aux1);
    while(!pilavacia(b))
    {
        if(tope(b)>4 && tope(b)<=48)
        {
            arr[i]=tope(b);
            i++;
            apilar(&aux1, desapilar(b));
        }
        else
        {
            apilar(&aux, desapilar(b));
        }
    }
    while(!pilavacia(&aux))
    {
        apilar(b, desapilar(&aux));
    }

    return i;

}

int arrereves(int arr[],int val)
{
    int i=0;
    int suma=0;
    int aux=0;

    i=val-1;
    while(i>=0)
    {
        suma=suma+arr[i];
        i=i-2;
        aux++;
    }
    suma=suma/aux;
    return suma;
}














