#include<iostream>

using namespace std;

int main(){

    int edad;
    int estudio;

    cout<< "Por favor igresa tu edad: "<<endl;
    cin>>edad;

    cout<< "Por favor igresa tus anios de estudio: "<<endl;
    cin>>estudio;

    if(edad <18){
        cout<<"usted es menor de edad"<<endl;
    }else{
        cout << "usted es mayor de edad"<<endl;
    }

    if(estudio <6){
        cout<<"usted solo hizo primaria"<<endl;
    }else if (estudio < 12) {
        cout << "usted hizo primaria y secundaria"<<endl;
    }else if (estudio < 18){
        cout << "usted es primaria, secundaria y universidad"<<endl;
    }else{
        cout<<"usted tiene estudios de posgrado"<<endl;
    }

    return 0;
}