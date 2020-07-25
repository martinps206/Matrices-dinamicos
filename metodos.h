#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix{
    int m, n;
    double **M;
} matrix_t;

matrix_t *matrix_create(int, int);
matrix_t *read_matrix(char *, int, int);
void write_matrix(matrix_t *);
matrix_t *matrix_sum(matrix_t *, matrix_t *);
matrix_t *matrix_mult(matrix_t *, matrix_t *);
void matrix_free(matrix_t *);

#endif
