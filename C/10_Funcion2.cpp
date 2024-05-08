#include<stdio.h>

int sumar(int a, int b){
	int suma;
	
	suma = a+b;
	
	return suma;//Lo empleamos al no usar funciones vacias
}

int main(){
	int A, B;
	
	printf("Ingresa dos numeros enteros separados por una coma para sumar: \n");
	
	scanf("%d,%d", &A,&B);
	
	printf("La suma es: %d", sumar(A,B));
	return 0;
	
}
