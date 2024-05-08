#include<iostream>
#include<cstring> //cadenas de bajo nivel
#include<string> //cadenas de alto nivel
using namespace std; 

int main(){
	string nombreDeUsuario("Juan");//alto nivel
	int longitud = nombreDeUsuario.length(); //string

	char nombreDeUsuario2[]="Miguel";//bajo nivel
	int longitud2 = strlen(nombreDeUsuario2);// (cstring) Averigua el numero de caracteres que existe en una cadena
	
	cout << longitud<<endl;
	cout<<longitud2<<endl;
	return 0;
}
