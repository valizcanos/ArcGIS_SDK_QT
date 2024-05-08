#include<stdio.h>

void cambiarValor(int *n){
	*n = 100;
}


int main(){
	int numero = 5;
	
	printf("El numero antes de la funcion vale, %d\n", numero);
	
	cambiarValor(&numero);
	
	printf("El numero despues de la funcion vale, %d\n", numero);
	
	return 0;
	
}
