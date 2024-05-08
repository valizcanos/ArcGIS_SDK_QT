#include <stdio.h>

int main() {
    int matriz[3][3]; // Declara una matriz de 3x3
    int i, j; // Variables para los �ndices de la matriz

    // Llena la matriz con un bucle for anidado
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("Ingrese el valor para la fila %d y la columna %d: ", i+1, j+1);
            scanf("%d", &matriz[i][j]); // Lee el valor del usuario
        }
    }

    // Imprime la matriz con un bucle for anidado
    printf("La matriz ingresada es:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}
