#include<stdio.h>

int main(){
	int contador=0;
	int digitos;
	printf("Ingresa el numero de digitos a proyectar: ");
	scanf("%d",&digitos);
	
	
	do{
		printf("\nNum: %d", contador++);
	}while(contador <digitos);
	
	return 0;
}
