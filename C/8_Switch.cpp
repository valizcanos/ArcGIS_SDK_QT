#include<stdio.h>

int main(){
	char operador;
	int n1=14, n2=5, resultado;
	
	printf("Ingrese un operador: +, -, *, /: ");
	
	scanf("%c", &operador);
	
	switch(operador){
		case '+':
			printf("Resultado = %d", n1+n2);
			break;
		case '-':
			printf("Resultado = %d", n1-n2);
			break;
		case '*':
			printf("Resultado = %d", n1*n2);
			break;
		case '/':
			printf("Resultado = %d", n1/n2);
			break;
		default:
			printf("Operador incorrecto");
	}
	
	return 0;
	
}
