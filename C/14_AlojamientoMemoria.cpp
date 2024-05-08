#include<stdio.h>
#include<stdlib.h>

//La funcion malloc() es una funcion de alojamiento de memoria
//Esta funcion reserva un bloque de memoria de un especifico numero de bytes

int main(){
	
	int arreglo[6]= {11,3,2,6,7,8};
	
	printf("Hemos creado un arreglo de %d datos\n", sizeof(arreglo)/sizeof(arreglo[0]));
	
	printf("Ahora miremos la funcion malloc\n");
	
	printf("Ingresa un entero \n");
	
	int entero;
	
	scanf("%d", entero);
	
	double *puntero; //Double tiene un tamano de 8 bytes
	
	puntero = (double*) malloc(entero * sizeof(double));//Esto reservará un bloque de memoria del tamaño de un número
	
	//ahora tiene reservado "entero" * 8 bytes
	
	printf("\nMalloc muestra %p",&puntero);
	
	//Para liberar la memoria dinamica anteriormente alojada empleamos la funcion free()
	
	free(puntero);
}
