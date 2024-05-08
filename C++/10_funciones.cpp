#include<iostream>
float calcularIVA(float precio);

using namespace std;

int main(){

    float precioDelAzucar;
    cout << "Ingresa el precio de una lb de azucar"<< endl;
    cin>> precioDelAzucar;

    float iva = calcularIVA(precioDelAzucar);

    cout<<"El IVA del azucar es de: "<< iva<< endl;

    return 0;
}

// tipoDeDatoDeRetorno NombreDeLaFuncion (tipoDelParametro NombreDelParametro,...){}

float calcularIVA(float precio){
    return (precio*0.21);
}