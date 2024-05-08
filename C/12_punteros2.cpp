#include<stdio.h>

int main(){
	int *pc,c;
	c = 5;
	
	pc = &c; //Se le agrega la direccion de c a la variable pc
	
	printf("la direccion de memoria de pc es %p\n", pc);
	printf("y pc tiene un valor de %d el cual se tomo de c\n", *pc); //representa lo mismo de la linea anterior
	printf("La direccion de c es %p\n", &c);
	
	c = 10;
	
	printf("El valor de c se cambio a 10, el valor de pc es %d\n\n Tambien se actualizo!", *pc);
	
	*pc = 2;
	
	printf("El valor de pc se actualizo a dos, entonces el valor de c es: %d", c);
	return 0;
}
