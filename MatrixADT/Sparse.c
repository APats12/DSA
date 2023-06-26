//-----------------------------------------------------------------------------
//  Sparse.c
//  Aryan Patel
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Matrix.h"
#include"List.h"

int main(int argc, char * argv[]){
    FILE* input, *output;
    int n, a, b, row, column;
    double value;
    Matrix A, B, C, D, E, F, G, H, I;
   // Check input argument and open input/output file
    if(argc != 3) {
        printf("Invalid number of inputs\n");
        exit(1);
    }
    input = fopen(argv[1], "r");
    if(input == NULL){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    output = fopen(argv[2], "w");
    if( output==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    //Read file input
    int num = fscanf(input, "%d %d %d\n\n", &n, &a, &b);
    if (num == EOF){
        fclose(input);
        fclose(output);
        return (0);
    }
    A = newMatrix(n);
    B = newMatrix(n);
    for(int i = 0; i < a; i++){
        fscanf(input, "%d %d %lf\n", &row, &column, &value);
        changeEntry(A, row, column, value);  
    }
    for(int i = 0; i < b; i++){
        fscanf(input, "%d %d %lf\n", &row, &column, &value);
        changeEntry(B, row, column, value);
    }
    fprintf(output, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(output, A);
    fprintf(output, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(output, B);
    //Matrix operation
    C = scalarMult(1.5, A);
    fprintf(output, "(1.5)*A =\n");
    printMatrix(output, C);
    D = sum(A, B);
    fprintf(output, "A+B =\n");
    printMatrix(output, D);
    E = sum(A, A);
    fprintf(output, "A+A =\n");
    printMatrix(output, E);
    F = diff(B, A);
    fprintf(output, "B-A =\n");
    printMatrix(output, F);
    fprintf(output, "A-A =\n\n");
    G = transpose(A);
    fprintf(output, "Transpose(A) =\n");
    printMatrix(output, G);
    H = product(A, B);
    fprintf(output, "A*B =\n");
    printMatrix(output, H);
    I = product(B, B);
    fprintf(output, "B*B =\n");
    printMatrix(output, I);

    //Close file and free mem
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    fclose(input);
    fclose(output);
    return 0;
}