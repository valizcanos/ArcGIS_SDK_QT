#include<stdio.h>
#include<stdlib.h>

int main(){
	int n, *marcas;
	
	printf("Ingrese el numero de estudiantes de su clase: ");
	
	scanf("%d", &n);
	
	//Alojar memoria para n de int
	//int solo almace 2 bytes de memoria
	//es decir 16 bits
	// 2^16 = 65536
	// como los enteros son positivos y negativos +- 65536/2
	// int tomara valores desde -32768 a 32767 (ya que se incluye en cero)
	
	printf("\nEl numero que asigno fue el %d", n);
	printf("\nEse numero tiene %d bytes de almacenamiento", sizeof(n));
	
	marcas = (int*)malloc(n*sizeof(int));
	
	if (marcas == NULL){
		printf("Error! memoria no alojada.");
		return 0;
	}
	
	printf("Ingrese los elementos: ");
	for(int i = 0; i< n; ++i){
		//Usamos el puntero para almacenar valores para el arreglo
		scanf("%d", marcas+i);
	}
	
	printf("Los valores almacenados son: ");
	
	for(int i=0; i<n; ++i){
		printf("%d, ", *(marcas + i));
	}
	
	free(marcas);
	return 0;
}
