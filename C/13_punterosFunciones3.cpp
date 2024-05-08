#include<stdio.h>

int *agregarDiez(int* dato){
	for (int i=0; i<5; i++){
		*(dato +i) = *(dato +i)+10;
	}
	return dato;
}

int main(){
	int data[5] = {1,2,3,4,5};
	int *resultado;
	
	resultado = agregarDiez(data);
	
	for(int i=0; i<5; ++i){
		printf("%d, ", *(resultado + i));
	}
	
	return 0;
}
