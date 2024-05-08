#include<stdio.h>

int main(){
	//If else condicionales
	
	int numero;
	printf("Por favor ingrese un entero positivo o negativo\n:");
	
	scanf("%d",&numero);
	
	if(numero == 0){
		printf("Usted acaba de asignar 0");
	}else if(numero<0){
		printf("Usted acaba de asignar un entero negativo");
	} else{
		printf("Usted acaba de asignar un entero postivo");
	}
	
	return 0;
}
