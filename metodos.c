#include <stdio.h>
#include <stdlib.h>
#include "metodos.h"
#define FREE(p)   do { free(p); (p) = NULL; } while(0)

matrix_t *matrix_create(int n, int m){
    int i;
    matrix_t *M;
    
    M = malloc(sizeof(matrix_t));
    if(M == NULL){
        return NULL;
    }

    M->m = m;
    M->n = n;

    M->M = malloc(n * sizeof(double *));
    if(M->M == NULL){
        return NULL;
    }
    for(i = 0; i < n; i++){
        M->M[i] = malloc(m * sizeof(double));
        if(M->M[i] == NULL){
            return NULL;
        }
    }
    return M;
}

matrix_t *read_matrix(char *filename, int n, int m){
    FILE *fp;
    matrix_t *M;
    int ni, mj, i, j;
    char line[100000];
    char num[1000];

    M = matrix_create(n, m);
    if(M == NULL){
        return NULL;
    }
    fp = fopen(filename,"r");
    if(fp == NULL){
        printf("Error al abrir archivo");
        return NULL;
    }

    for(ni = 0; ni < n; ni++){
        fgets(line, 100000, fp); 
        i = 0;
        mj = 0;
        while(mj < m){
            j = 0;

            while(line[i] != ' ' && line[i] != '\n'){
                num[j] = line[i];
                j++;
                i++;
            }

            i++;
            num[j] = '\0';
            M->M[ni][mj] = atof(num);
            mj++;
            j = 0;
        }
    }
                
    fclose(fp);
    return M;
}

void write_matrix(matrix_t *M){
    int n,m;
    printf("\n");
    for(n=0; n < M->n; n++){
        for(m=0; m < M->m; m++){
            printf("\t%.2f", M->M[n][m]);
        }
        printf("\n");
    }
}

matrix_t *matrix_mult(matrix_t *M1, matrix_t *M2){
    int n,m,i;
    matrix_t *M;
    float fsum;
    
    if(M1 == NULL){
        return NULL;
    }
    if(M2 == NULL){
        return NULL;
    }

    if(M1->m != M2->n){
        printf("Las matrices deben ser M1 = N2");
        return NULL;
    }

    M = matrix_create(M1->m, M2->n);
    if(M == NULL){
        return NULL;
    }

    M->m = M1->m;
    M->n = M2->n;

    for(n = 0; n < M->n; n++){
        for(m = 0; m < M->m; m++){
            fsum = 0;
            for(i=0; i<M->m; i++){
                fsum = fsum + M1->M[n][i] * M2->M[i][m];
            }
            M->M[n][m] = fsum;
        }
    }
    
    return M;
}
    
void matrix_free(matrix_t *M){
    int i;
    for(i = 0; i < M->n; i++)
        FREE(M->M[i]);
    FREE(M->M);
    FREE(M);
} 

matrix_t *matrix_sum(matrix_t *M1, matrix_t *M2){
    int n,m;
    matrix_t *M;

    if(M1 == NULL){
        return NULL;
    }
    if(M2 == NULL){
        return NULL;
    }

    if(M1->m != M2->m && M1->n != M2->n){
        printf("Las matrices deben ser de mismas dimensiones...");
        return NULL;
    }

    M = matrix_create(M1->m, M1->n);
    if(M == NULL){
        return NULL;
    }

    M->m = M1->m;
    M->n = M1->n;

    for(n = 0; n < M->n; n++){
        for(m = 0; m < M->m; m++){
            M->M[n][m] = M1->M[n][m] + M2->M[n][m];
        }
    }
    
    return M;
}

