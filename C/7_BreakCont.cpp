#include<stdio.h>

/*Especificadores:

"c": caracteres
"f": flotante, 45.0f, .2f dos decimales
"lf": double
"ld": long int
"Lf": long double
"lu": long int sin signo

*/

int main(){
	int f;
	
	printf("Ingresa un numero: ");
	scanf("%d", &f);
	printf("Usted ingreso el numero: %d \n", f);
	
	do{
		
		f--;
		
		if(f<0){
			printf("El proceso se detuvo para evitar un bucle infinito\nPor favor ingrese un numero positivo");
			break;
		}
		
		if(f%2==0){
			continue;
			
		}
		printf("num: %d\n",f);
		
	}while(f>=0);
	
	return 0;
	
	
	
}
