#include<stdio.h>
#include<math.h>

float distanciaE (float x1, float y1, float x2, float y2){
	float distancia,difX,difY;
	
	difX = pow(x1-x2,2);
	difY = pow(y1-y2,2);
	
	distancia = sqrt(difX+difY);
	
	return distancia;
}


int main(){
	float d1x,d1y,d2x,d2y;
	printf("Ingresa la longitud 1: \n");
	scanf("%f", d1x);
	
	printf("\nIngresa la latitud 1:");
	scanf("%f", d1y);
	
	printf("\nIngesa la longitud 2:");
	scanf("%f", d2x);
	
	printf("\nIngresa la latitud 2:");
	scanf("%f", d2y);
	
	printf("\nLa distancia es: %f", distanciaE(d1x,d1y,d2x,d2y));
	
	return 0;
	
	
}


