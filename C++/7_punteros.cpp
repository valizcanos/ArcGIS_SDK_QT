#include<iostream>

using namespace std;

/*
Los punteros son variables que permiten almacenar direcciones de memoria
de otras variables 
 */

int main(){
    int id;

    //almacenemos la direccion de memoria de la variable id

    //declaramos el puntero con el nombre p_id y sera de entero ya que id es entero

    int *p_id;

    //inicializamos el puntero

    p_id = &id; // tomamos la direccion de memoria de la variable id

    cout<<"Contenido del id: " <<id<<endl;
    cout<<"Contenido del puntero del id: " <<p_id<<endl;

    //inicializamos el id

    id=10;

    cout<<"Contenido del id: " <<id<<endl;
    cout<<"Contenido del puntero del id: " <<p_id<<endl;

    // vamos acceder a la direccion de memoria de la variable id
    // a traves del puntero y vamos asignar un nuevo valor

    *p_id= 50; //como es un valor en este caso usamos el *

    cout<<"Contenido del id: " <<id<<endl;
    cout<<"Contenido del puntero del id: " <<p_id<<endl;

    return 0;
}