#include<iostream>
#include<vector> //empleamos las libreria vector

using namespace std;

int main(){

    vector<float> ingresos;
    ingresos.push_back(500.5); //este metodo anade el valor a un vector en concreto
    //al no denotar una posicion, se anade a la posicion 0 del vector
    ingresos.push_back(480.8);
    ingresos.push_back(550.1);
    ingresos.push_back(400.9);

    cout<< ingresos[1]<< endl;
    cout<< ingresos.at(2)<< endl;

    return 0;
}