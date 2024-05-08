#include<stdio.h>

int main(){
	
	int contador;
	
	printf("Ingrese un numero entero: \n");
	scanf("%d",&contador);
	
	for(int i=0; i<contador; i++){
		printf("Num: %d \n", i);
	}
	
	for(int i=0; i<contador; i--){
		printf("Num: %d \n", i);  //Da un bucle infinito
	}
	
	return 0;
}

