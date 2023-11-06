//NOMBRE: NAVARRO QUISPE WILY R., CI: 8420315
#include <stdio.h>
#include <string.h>
#include <omp.h>



void textodivide(char *texto, char *palabraimpar, char *palabrapar) {
    int tamano = strlen(texto);
    char palabras[tamano][tamano]; 
    int numPalabras = 0;

    char *token = strtok(texto, " ");
    while (token != NULL) {
        strcpy(palabras[numPalabras], token);
        numPalabras++;
        token = strtok(NULL, " ");
    }
  // División de las palabras en dos secciones par e impar
    #pragma omp parallel for shared(numPalabras, palabras, palabraimpar, palabrapar)
    for (int i = 0; i < numPalabras; ++i) {
        if (i % 2 == 0) {
            strcat(palabrapar, palabras[i]);
            strcat(palabrapar, " ");
        } else {
            strcat(palabraimpar, palabras[i]);
            strcat(palabraimpar, " ");
        }
    }
}

void main() {
    char texto[] = "tres trites tigres trigaban trigo por culpa del bolivar";
    char palabraimpar[500] = ""; 
    char palabrapar[500] = ""; 

    textodivide(texto, palabraimpar, palabrapar);

    printf("Primera parte del texto: %s\n", palabrapar);
    printf("Segunda parte del texto: %s\n", palabraimpar);
}