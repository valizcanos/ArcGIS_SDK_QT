#include<stdio.h>

int main(){
	int x[4] = {10,20,30,40};
	
	printf("Valor del segundo elemento %d\n", *(x+1) );
	
	printf("El valor del tercer elemento es %d\n", x[2]);
	
	printf("Por favor asigne el valor del 4to elemento\n");
	
	scanf("%d", x+3);
	
	printf("\nEl valor asignado fue de %d\n", x[3]);
	
	return 0;
}
