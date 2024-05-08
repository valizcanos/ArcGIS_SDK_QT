#include<iostream>
#include<vector>

using namespace std;

int main(){

    vector<int> vectores;
    for(int contador=1; contador<=10; contador++){
        vectores.push_back(contador);
        cout << vectores[contador] <<endl;
    }
    return 0;
}