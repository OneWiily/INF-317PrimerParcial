//NOMBRES: NAVARRO QUISPE WILY RODRIGO, CI: 8420315 

#include <stdio.h>
#include <string.h>
#include <mpi.h>





void textodivide(char *texto, char *palabraimpar, char *palabrapar, int numPalabras) {
    char palabras[numPalabras][1000]; 

    
    char *token = strtok(frase, " ");
    int i = 0;
    while (token != NULL) {
        strcpy(palabras[i], token);
        i++;
        token = strtok(NULL, " ");
    }

  
    for (i = 0; i < numPalabras; ++i) {
        if (i % 2 == 0) {
            
            strcat(palabrapar, palabras[i]);
            strcat(palabrapar, " ");
        } else {
            
            strcat(palabraimpar, palabras[i]);
            strcat(palabraimpar, " ");
        }
    }
}

void main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, numProcs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

    char texto[] = "tres tristes tigres trigaban trigo por culpa del bolivar";
    char palabraimpar[500] = ""; 
    char palabrapar[500] = ""; 

    int numPalabras;
    if (rank == 0) {
        numPalabras = 10; 
    }

    MPI_Bcast(&numPalabras, 1, MPI_INT, 0, MPI_COMM_WORLD);

   
    textodivide(texto, palabraimpar, palabrapar, numPalabras);

    
    char salidatextoimpar[1000 * numProcs];
    char salidatextopar[1000 * numProcs];

    MPI_Gather(palabraimpar, 1000, MPI_CHAR, salidatextoimpar, 1000, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Gather(palabrapar, 1000, MPI_CHAR, salidatextopar, 1000, MPI_CHAR, 0, MPI_COMM_WORLD);

    MPI_Finalize();

   
    if (rank == 0) {
    	printf("Primera parte del texto: %s\n", salidatextopar);
        printf("Segunda parte del texto: %s\n", salidatextoimpar);
        
    }

}