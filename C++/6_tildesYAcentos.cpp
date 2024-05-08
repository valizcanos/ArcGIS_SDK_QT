#include<iostream>
#include <stdio.h>
#include<clocale> //para incluir acentos

using namespace std;

int main(){
	
	setlocale(LC_ALL, "spanish"); //En categoria poner LC_ALL que elimina las configuraciones de localizacion existentes
	//En idioma poner "spanish" asi podremos incluir tildes. Muestra los caracteres del español correctamente, pero no los recoge desde teclado.

	setlocale(LC_ALL, "es_ES"); //Recoge los caracteres del español correctamente desde teclado, pero no los muestra bien.

	setlocale( LC_ALL, "es_ES.UTF-8" );
	
	cout<< "Hola que más";
	return 0;
}
