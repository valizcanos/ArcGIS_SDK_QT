#include<stdio.h>


/*void printEdad(int edad1, int edad2){
	printf("%d\n", edad1);
	printf("%d\n", edad2);
	
	int main(){
	int edadArreglo[]={2,8,4,12};
	
	printEdad(edadArreglo[1], edadArreglo[3]);
	return 0;
}
}*/

void printEdad(int edad[]){
	printf("%d\n", edad[0]);
	printf("%d\n", edad[2]);
}

int main(){
	int edadArreglo[]={2,8,4,12};
	
	printEdad(edadArreglo);
	return 10;
}
