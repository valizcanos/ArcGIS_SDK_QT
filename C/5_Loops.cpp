#include<stdio.h>

int main(){
	
	int contador=0;
	
	while(contador<10){
		printf("contador:%d\n ",contador++);
	}
	
	/*
	//hace lo mismo que el loop de arriba
	while(contador<10){
		printf("contador:%d\n ",contador);
		//contador++;
	}
	*/
	
	return 0;
}
