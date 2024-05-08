#include<iostream>

using namespace std;

int main(){
    int puntuacion;
    cout <<"Por favor ingresa la puntuacion que sacaste en el examen: "<<endl;
    cin>> puntuacion;

    switch (puntuacion)
    {
    case 0: cout<< "No acertaste ninguna pregunta"; break;
    case 1: cout<< "Acertaste una pregunta"; break;
    case 2: cout<< "Acertaste dos preguntas"; break;
    case 3: cout<< "Acertaste tres preguntas"; break;
    case 4: cout<< "Acertaste cuatro preguntas"; break;    
    default: cout<< "Acertaste todas las preguntas"; break;
    }

    return 0;
}