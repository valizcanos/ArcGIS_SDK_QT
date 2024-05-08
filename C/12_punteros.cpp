/*Punteros:
 Un puntero es una caracteristica muy poderosa a en C y C++.
 Los punteros nos permiten trabajar con direcciones de memoria. En otras palabras 
 los punteros almacenan direcciones de memoria en vez de valores.
*/

#include<stdio.h>

int main(){
	int var = 5;
	printf("var = %d\n", var);
	
	printf("La direccion de memoria de var es = %p", &var);
	
	return 0;
}
