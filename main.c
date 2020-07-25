#include <stdio.h>
#include <stdlib.h>
#include "metodos.h"

void formato(void){
    printf("Formato de entrada:\n");
    printf("   multm [n] [m] archivo1.txt [n] [m] archivo2.txt\n");
    printf("\nDonde n y m son las dimenciones de cada matriz\n");
    printf("y archivo1.txt y archivo2.txt contienen los valores\n");
    printf("de las matrices.\n");
} 
// Como realizar la ejecucion del programa
// gcc main.c metodos.c -o main -Wall -ggdb
// main  3 3 M1.txt 3 3 M2.txt
int main(int argc, char **argv){
    int n1, n2, m1, m2, print;
    char *f1, *f2;
    matrix_t *M1, *M2, *M, *SUMA;

    // Revisamos si hay suficientes entradas desde terminal
    if (argc != 7){
        formato();
        return 0;
    }
    
    // ¿Queremos impresión en pantalla?
    print = 1;

    // Asignamos valores de la entrada a variables
    n1 = atoi(argv[1]);
    m1 = atoi(argv[2]);
    f1 = argv[3];
    n2 = atoi(argv[4]);
    m2 = atoi(argv[5]);
    f2 = argv[6];

    // Se crea la primera matriz
    printf("%s",f1);
    M1 = read_matrix(f1 ,n1, m1);
    if (M1 == NULL){
        printf("Error al crear matríz...\n");
        return 1;
    }

    if(print){
		printf("\tMATRIZ A :\n");
        write_matrix(M1);
        printf("\n");
    }

    //Se crea la segunda matriz
    M2 = read_matrix(f2 ,n2, m2);
    if (M2 == NULL){
        printf("Error al crear matríz\n");
        matrix_free(M1);
        return 1;
    }

    if(print){
        printf("\tMATRIZ B :\n");
        write_matrix(M2);
        printf("\n");
    }
    
    // Realizamos la multiplicación
    M = matrix_mult(M1, M2);
    if(M == NULL){
        matrix_free(M1);
        matrix_free(M2);
        return 1;
    }
    if(print){
        printf("\t--------------------------\n");
        printf("\tMULTIPLICACION DE MATRICES\n");
        printf("\t--------------------------\n");
        write_matrix(M);
        printf("\n");
    }
    
    //Realizamos la adicion
    SUMA = matrix_sum(M1, M2);
    if(SUMA == NULL){
        matrix_free(M1);
        matrix_free(M2);
        return 1;
    }
    if(print){
        printf("\t----------------\n");
        printf("\tSUMA DE MATRICES\n");
        printf("\t----------------\n");
        write_matrix(SUMA);
    }

    // Liberamos memoria
    matrix_free(M1);
    matrix_free(M2);
    matrix_free(M);
 
    return 0;
}
