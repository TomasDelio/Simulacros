#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

Pila cargarpila (Pila *a);
int copiador (Pila *a,int arr[],int val);
int mayorel (int arr[],int val);
int menorpila (Pila a);
int quitar (Pila *a, int dato);
int promedio (int arr[],int val);
int cargar (int arr[]);
int posicion(int arr[], int val);
void mostrarpos(int arr[], int val);
void mostrarpila(Pila*a);






int main()
{
    int num =0;
    char yes;
    int val=20;
    int arr[100];
    int vali=0;

    Pila pilita;
    inicpila(&pilita);



    do
    {
        printf("SIMULACRO PROG, ingrese el numero del ejercicio que desea ver perfectamente realizado: ");
        fflush(stdin);
        scanf("%i", &num);
        switch(num)
        {
        case 1:

            cargarpila(&pilita);
            mostrar(&pilita);

            break;
        case 2:

            cargarpila(&pilita);
            val= copiador(&pilita,arr,val);
            printf("Los arreglos que se muestran son solo los numeros pares de la pila \n\n");
            mostrador(arr,val);

            break;
        case 3:
            cargarpila(&pilita);
            val= copiador(&pilita,arr,val);
            mostrador(arr,val);
            num =mayorel(arr,val);
            printf("El numero mas grande del arreglo es : %i\n",num);

            break;
        case 4:
            cargarpila(&pilita);
            val= copiador(&pilita,arr,val);
            mostrador(arr,val);
            num =menorpila(pilita);
            quitar(&pilita,num);
            printf("El numero menor del arreglo es : %i\n",num);
            mostrar(&pilita);

            break;
        case 5://NO DA BIEN PERO ANDA
            vali=cargar(arr);
            mostrador(arr,vali);
            num=promedio(arr,vali);
            printf("El Promedio es: %i", num);

            break;
        case 6:
            vali=cargar(arr);
            mostrador(arr, vali);
            mostrarpos(arr, vali);

            break;
        case 7:
            cargar(&pilita);
            printf("Pila cargada: \n");
            mostrarpila(&pilita);
            mostrar(&pilita);
            break;

        }
        printf("Desea ver otro ejercicio? presione s para si ");
        fflush(stdin);
        scanf("%c", &yes);
    }
    while(yes=='s'|| yes=='S');
    return 0;
}

Pila cargarpila(Pila *a)
{
    char yes;

    do
    {
        leer(a);
        printf("Desea ingresar un nuevo numero a la pila??");
        fflush(stdin);
        scanf("%c",&yes);
    }
    while(yes=='s'|| yes=='S');
}

int copiador (Pila *a,int arr[],int val)//PARA COPIAR LOS IMPARES USAMOS EL RESTO DE UNA DIVICION ,4%2 RESTO
{
    int i=0;
    Pila aux;
    inicpila(&aux);
    int top=0;

    while(!pilavacia(a)&& i<val)//VERIFICADOR SI SON PARES O NO
    {
        top=tope(a);
        if(tope(a)%2==0)
        {
            arr[i]=top;
            apilar(&aux, desapilar(a));
            i++;
        }
        else
            apilar(&aux,desapilar(a));
    }
    while(!pilavacia(&aux))
    {
        apilar(a,desapilar(&aux));
    }
    return i;
}

void mostrador (int arr[],int val)//ESENCIAL PARA PODES MOSTRAR LOS ARREGLOS
{
    int i =0;
    while(i<val)
    {
        printf("|%i|",arr[i]);
        i++;
    }
    printf("\n\n\n");
}

int mayorel (int arr[],int val)//BUSCA EL MAYOR DE TODOS LOS NUMEROS
{
    int i=0;
    int tope=0;
    int u=0;

    while(i<val)
    {
        if(arr[u]<arr[i])
        {
            tope=arr[u];
            arr[u]=arr[i];
            arr[i]=tope;
            i++;
        }
        else
        {
            i++;
        }
    }
    return arr[u];
}

int menorpila (Pila a)//BUSCA EL MENOR ELEMENTO DE LAS PILAS
{
    Pila aux;
    inicpila(&aux);
    apilar(&aux, desapilar (&a));
    int dato;

    while(!pilavacia(&a))
    {
        if(tope(&aux)>tope(&a))
        {
            apilar(&aux,desapilar(&a));
        }
        else
        {
            desapilar(&a);
        }
    }
    dato=tope(&aux);
    return dato;
}

int quitar (Pila *a, int dato)//QUITA EL MENOR ELEMENTO JUNTO CON LA OTRA FUNCION
{
    Pila aux;
    inicpila(&aux);
    Pila aux2;
    inicpila(&aux2);

    while(!pilavacia(a))
    {
        if(tope(a)==dato)
        {
            apilar(&aux2,desapilar(a));
        }
        else
        {
            apilar(&aux, desapilar(a));
        }
    }
    while(!pilavacia(&aux))
    {
        apilar(a,desapilar(&aux));
    }
}

int promedio (int arr[],int val)//PRIMEDIA
{
    int i=0;
    int total=0;

    while(i<val)
    {
        total=total +arr[i];//ESTE LO SUMA
        i++;
    }

    total=total/i; //ESTE HACE EL PROMEDIO
    return total;
}
int cargar (int arr[])
{
     int i=0;
    char yes;
    do
    {
        printf("Escriba el numero que quiera ingresar:  ");
        fflush(stdin);
        scanf("i",&arr[i]);
        i++;

        printf("\nDesea agregar alguno mas? presione s para si ");
        fflush(stdin);
        scanf("%c", &yes);

    }
    while(yes=='s'||yes=='S');
        return i;
}

int posicion(int arr[], int val)//POSICION CON VALIDACIONES (OSEA UNO ANTERIOR)
{
    int i=0;
    printf("Elija la posicion del dato de que desea buscar, recuerde elejir una posicion entre 0 y %i: ", val-1);
    fflush(stdin);
    scanf("%i", &i);

    return i;
}

void mostrarpos(int arr[], int val)//MUESTRA LA PSOCION
{
    int i=0;
    i=posicion(arr, val);

    printf("El numero que esta en esa posicion es: %i \n", arr[i]);
}

void mostrarpila(Pila*a)
{
    Pila aux;
    inicpila(&aux);


    printf("Tope\n");
    while(!pilavacia(a))
    {
        printf("|)%i(|\n", tope(a));
        apilar(&aux, desapilar(a));
    }
    printf("Base\n");
    while(!pilavacia(&aux))
    {
        apilar(a, desapilar(&aux));

    }
}
