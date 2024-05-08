#include<stdio.h>

/* Nota:
sizeof(Array_name)Es un operador que devuelve el tamaño de toda la matriz en bytes.
sizeof(Array_name[index]): devuelve el tamaño de un solo elemento en la matriz en bytes
*/
int main(){
	int datos[] = {10,20,30,40,50};
	
	printf("Tenemos una matriz de %d bytes \n", sizeof(datos));
	
	int longitud = sizeof(datos)/sizeof(datos[0]);
	
	printf("Mi matriz tiene %d datos \n", longitud);
	
	for(int i=0; i<longitud;i++){
		printf("El dato %d tiene un tamano de %d bytes \n", i, sizeof(datos[i]));
	}
	
	printf("Te gustaria reemplazar los valores de esa matriz: [s/n] \n");
	
	char reemplazar;
	
	scanf("%c",&reemplazar);
	
	if(reemplazar == 's'){
		printf("Has seleccionado la opcion de reemplazar \n");
		for(int i=0; i<longitud; i++){
			printf("Por favor ingresa el %d valor: \n", i);
			scanf("%d", &datos[i]);
		}
	}else{
		printf("Ha seleccionado la opcion de no reemplazar valores, chao ");
	}
	
	printf("Tu matriz quedo definida como: \n");
	
	for(int i=0; i<longitud; i++){
		printf("[%d]",datos[i]);
	}
	
	return 0;
}
