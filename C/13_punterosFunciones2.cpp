#include<stdio.h>

void intercambiarDigitos(int *n1, int *n2){
	int temporal;
	
	temporal = *n1;
	*n1 = *n2;
	*n2 = temporal;
}

int main(){
	int nume1 = 1, nume2 = 100;
	
	intercambiarDigitos(&nume1,&nume2);
	
	printf("numero 1 %d\n", nume1);
	
	printf("numero 2 %d\n", nume2);
	
	return 0;
}
