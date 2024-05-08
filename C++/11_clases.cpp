#include<iostream>
#include<string>

using namespace std;

enum Categoria {A = 300, B=350, C=400, D=0};

class persona {

    public:
    //atributos
        string nombres, apellidos;
        int cedula;
        int edad;
        float sueldo;
        Categoria bonificacion;
        static float auxilio; //es un palabra reservada que puede ser comun a todos los objetos
    private:
};

int main(){

    char CategoriaEmpleado;
    persona Pedro;//objeto

    Pedro.nombres = "Pedro Pablo";
    Pedro.apellidos = "Pedraza Pascal";
    Pedro.edad=40;
    Pedro.cedula=1000000000;
    Pedro.sueldo=3400000;

    cout<< " A que categoria petenece "<< endl;
    cin>>CategoriaEmpleado;

    switch (CategoriaEmpleado)
    {
    case 'A':Pedro.bonificacion = A; break;
    case 'B':Pedro.bonificacion = B; break;
    case 'C':Pedro.bonificacion = C; break;
    case 'D':Pedro.bonificacion = D; break;  
    default: "No pertenece a ninguna categoria"; break;
    }

    cout<< "Usuario: "<<  Pedro.nombres << Pedro.apellidos << ", de "<< Pedro.edad << " Anios"<<endl;
    cout<< "Identificado con la cedula "<< Pedro.cedula << " tiene un sueldo de  " << Pedro.sueldo << endl;
    cout << "Actualmente "<<  Pedro.nombres << " recibe una bonificacion de " << Pedro.bonificacion<< endl;
    return 0;
}