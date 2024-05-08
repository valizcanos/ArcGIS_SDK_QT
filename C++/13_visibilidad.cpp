#include<iostream>
#include<string>

using namespace std;

enum Categoria {A = 300, B=350, C=400, D=0};

class persona {

    public:
    //atributos
        string nombres, apellidos;
        int cedula;
        Categoria bonificacion;
        static float auxilio; //es un palabra reservada que puede ser comun a todos los objetos

        //Constructor predeterminado, va a ser inicializado con un valor entero de la variable cedula
        persona(int id);
        
        int getEdad();
        void setEdad(int edad);
        float getSueldo();
        void setSueldo(float sueldo);

        //Funcion miembro o metodo, declaracion
        float estimacionPagoMensual();
    private:
        int edad;
        float sueldo;
};

int main(){

    int id;
    char CategoriaEmpleado;

    cout<< "Por favor introduzca el id del empleado "<< endl;
    cin>>id;

    persona *Pedro=  new persona(id);

    Pedro->nombres = "Pedro Pablo";
    Pedro->apellidos = "Pedraza Pascal";
    Pedro->setEdad(40);
    //Pedro->cedula=1000000000;
    Pedro->setSueldo(3400000);

    cout<< " A que categoria petenece "<< endl;
    cin>>CategoriaEmpleado;

    switch (CategoriaEmpleado)
    {
    case 'A':Pedro->bonificacion = A; break;
    case 'B':Pedro->bonificacion = B; break;
    case 'C':Pedro->bonificacion = C; break;
    case 'D':Pedro->bonificacion = D; break;  
    default: "No pertenece a ninguna categoria"; break;
    }

    cout<< "Usuario: "<<  Pedro->nombres << Pedro->apellidos << ", de "<< Pedro->getEdad() << " Anios"<<endl;
    cout<< "Identificado con la cedula "<< Pedro->cedula << " tiene un sueldo de  " << Pedro->getSueldo() << endl;
    cout << "Actualmente "<<  Pedro->nombres << " recibe una bonificacion de " << Pedro->bonificacion<< endl;
    return 0;
}

//vamos a implementar la funcion del constructor
persona::persona(int id){   
    this->cedula = id;
}


//implementacion del metodo, definicion

float persona::estimacionPagoMensual(){
    return (sueldo+bonificacion);
}

int persona::getEdad(){
    return edad;
}

void persona::setEdad(int edad){
    this->edad = edad;
}

float persona::getSueldo(){
    return sueldo;
}

void persona::setSueldo(float sueldo){
    this->sueldo=sueldo;
}