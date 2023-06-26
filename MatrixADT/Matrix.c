//-----------------------------------------------------------------------------
//  Matrix.c
//  Aryan Patel
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"
#include "List.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj{
    double value;
    int position;
} EntryObj;

typedef struct MatrixObj{
    List* rows;
    int size;
    int non_zero;        
}MatrixObj;

// Constructors-Destructors ---------------------------------------------------

Entry newEntry(double val, int pos){
    Entry ent = malloc(sizeof(EntryObj));
    ent->value = val;
    ent->position = pos;
    return ent;
}

Matrix newMatrix(int n){
    Matrix mat = malloc(sizeof(MatrixObj));
    mat->rows = calloc(n + 1, sizeof(List));
    mat->size = n;
    mat->non_zero = 0;
    for(int i = 0; i <= n; i++){
        mat->rows[i] = newList();
    }
    return mat;
}

void freeEntry(Entry* pE){
    if(pE != NULL && *pE != NULL){
        free(*pE);
        *pE = NULL;
        pE = NULL;
    }
}


void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        int i = 0;
        while (i <= size(*pM)) {
            List row = (*pM)->rows[i];
            moveFront(row);
            while (index(row) >= 0) {
                Entry E = get(row);
                freeEntry(&E);
                moveNext(row);
            }
            freeList(&((*pM)->rows[i]));
            i++;
        }
        free((*pM)->rows);
        free((*pM));
        *pM = NULL;
        pM = NULL;
    }
}

// Access functions -----------------------------------------------------------

int size(Matrix M){
    if (M == NULL){
        printf("Matrix Error: calling size() when M is NULL\n");
        exit(EXIT_FAILURE);
    }
    return M->size;
}

int NNZ(Matrix M){
    if (M == NULL){
        printf("Matrix Error: calling NNZ() when M is NULL\n");
        exit(EXIT_FAILURE);
    }
    return M->non_zero;
}

int equals(Matrix A, Matrix B){
    // Check if sizes and non-zero elements match
    if(A->size != B->size || A->non_zero != B->non_zero){
        return 0;
    }
    // Iterate through each row of both matrices
    for(int i = 0; i <= size(A); i++){
        // Get the lists for the current row of both matrices
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        // Iterate through each entry of the current row
        for(moveFront(rowA), moveFront(rowB); index(rowA) >= 0 && index(rowB) >= 0; moveNext(rowA), moveNext(rowB)){
            Entry E_A = get(rowA);
            Entry E_B = get(rowB);
            // Check if positions and values match
            if(E_A->position != E_B->position || E_A->value != E_B->value){
                return 0;
            }
        }
        // Check if both rows have been fully iterated
        if(index(rowA) >= 0 || index(rowB) >= 0){
            return 0;
        }
    }
    // Matrices are equal
    return 1;
}


// Manipulation procedures ----------------------------------------------------

void makeZero(Matrix M){
    for(int i = 0; i < size(M); i++){
        List row = M->rows[i];
        while(length(row) > 0){
            deleteFront(row);
        }
    }
    M->non_zero = 0;
}

void shiftCursor(List L, int i) {
    moveFront(L);
    while (index(L) >= 0 && ((Entry)get(L))->position != i) {
        if (((Entry)get(L))->position < i) {
            moveNext(L);
        } 
        else {
            movePrev(L);
        }
    }
}

void changeEntry(Matrix M, int i, int j, double x){
    List row = M->rows[i]; // get ith row
    // find Entry in ith row that has column j
    for(moveFront(row); index(row) >= 0; moveNext(row)){
        Entry ent = get(row);
        if(ent->position == j){ // if such Entry is found
            if(x == 0){ // if x is 0, remove the Entry
                shiftCursor(row, j);
                freeEntry(&ent);
                delete(row);
                M->non_zero -= 1;
                return;
            }
            else{ // if x is not 0, change the value of the Entry
                ent->value = x;
                return;
            }
        }
        else if(ent->position > j){ // if the Entry is not found, and a higher column Entry is found, insert a new Entry before the higher column Entry
            if(x == 0){ // if x is 0, no need to add a new Entry
                return;
            }
            else{ // if x is not 0, insert a new Entry before the higher column Entry
            insertBefore(row, newEntry(x, j));
            M->non_zero ++;
            return;
            }
        }
    }
    // if the Entry is not found and no higher column Entry is found, append the new Entry to the end of the row
    if(x == 0){ // if x is 0, no need to add a new Entry
        return;
    }
    else{ // if x is not 0, append the new Entry to the end of the row
        append(row, newEntry(x, j));
        M->non_zero ++;
        return;
    }
}

// Matrix Arithmetic operations ----------------------------------------------------

Matrix copy(Matrix A){
    Matrix A_copy = newMatrix(size(A));
    A_copy->non_zero = NNZ(A);
    int i = 0; // set i to 0 to start iterating over rows of A
    while(i <= size(A)){ // iterate over rows of A until the last row
        List row = A->rows[i]; // get the ith row of A
        moveFront(row); // move cursor of row to the front
        while(index(row) >= 0){ // iterate over entries of row until the last entry
            Entry ent = get(row); // get the current entry of row
            append(A_copy->rows[i], newEntry(ent->value, ent->position)); // append a new entry to the ith row of A_copy with the same value and position as ent
            moveNext(row);
        }
        i++;
    }
    return A_copy;
}

Matrix transpose(Matrix A) {
    Matrix A_transposed = newMatrix(size(A));
    A_transposed->non_zero = NNZ(A);
    int i = 0;
    while (i <= size(A)) {
        List row = A->rows[i];
        moveFront(row);
        while (index(row) >= 0) {
            Entry ent = get(row);
            // Add a new Entry to the corresponding row and column in A_transposed with swapped indices
            append(A_transposed->rows[ent->position], newEntry(ent->value, i));
            moveNext(row);
        }
        i++;
    }
    
    return A_transposed;
}


Matrix scalarMult(double x, Matrix A){
    Matrix A_scalar = newMatrix(size(A));
    A_scalar->non_zero = NNZ(A);
    for(int i = 0; i <= size(A); i++){
        List row = A->rows[i];
        for(moveFront(row); index(row) >= 0; moveNext(row)){
            Entry ent = get(row);
            // Compute the scalar product of the value of the entry and x, and add it to the ith row of A_scalar.
            append(A_scalar->rows[i], newEntry(x * ent->value, ent->position));
            // If the scalar product is 0, then decrement the NNZ of A_scalar.
            if(x == 0){
                A_scalar->non_zero -= 1;
            }
        }
    }
    return A_scalar;
}

Matrix sum(Matrix A, Matrix B) {
    if(A == B){
        return(scalarMult(2, A));
    }
    B = copy(B);
    Matrix sum = newMatrix(size(A));
    for (int i = 0; i <= size(A); i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];
        moveFront(rowA);
        moveFront(rowB);
        while(index(rowA)>-1 && index(rowB)>-1){
            Entry entA = get(rowA);
            Entry entB = get(rowB);
            if (entA->position == entB->position) {
                append(sum->rows[i], newEntry(entA->value + entB->value, entA->position));
                if (entA->value + entB->value == 0) {
                    deleteBack(sum->rows[i]);
                    sum->non_zero -= 1;
                }
                moveNext(rowA);
                moveNext(rowB);
            }
            else if (entA->position < entB->position) {
                append(sum->rows[i], newEntry(entA->value, entA->position));
                moveNext(rowA);
            }
            else if (entA->position > entB->position) {
                append(sum->rows[i], newEntry(entB->value, entB->position));
                moveNext(rowB);
            }
            sum->non_zero += 1;
        }
        while (index(rowA) >= 0) {
            Entry entA = get(rowA);
            append(sum->rows[i], newEntry(entA->value, entA->position));
            sum->non_zero += 1;
            moveNext(rowA);
        }
        while (index(rowB) >= 0) {
            Entry entB = get(rowB);
            append(sum->rows[i], newEntry(entB->value, entB->position));
            sum->non_zero += 1;
            moveNext(rowB);
        }
    }
    freeMatrix(&B);
    return sum;
}


Matrix diff(Matrix A, Matrix B) {
    Matrix B_copy = copy(B);
    Matrix neg_Matrix = scalarMult(-1, B_copy);
    Matrix difference = sum(A, neg_Matrix);
    freeMatrix(&B_copy);
    freeMatrix(&neg_Matrix);
    return difference;
}

//helper function that computes the vector dot product of two matrix rows represented by Lists P and Q
double vectorDot(List P, List Q) {
    double result = 0.0;
    moveFront(P);
    moveFront(Q);
    while (index(P) >= 0 && index(Q) >= 0) {
        Entry p = get(P);
        Entry q = get(Q);
        if (p->position == q->position) {
            result += p->value * q->value;
            moveNext(P);
            moveNext(Q);
        } 
        else if (p->position < q->position) {
            moveNext(P);
        } 
        else {
            moveNext(Q);
        }
    }
    return result;
}


Matrix product(Matrix A, Matrix B) {
    // Transpose matrix B for more efficient dot products
    Matrix newB = transpose(B);
    Matrix productAB = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        List rowA = A->rows[i];
        // If the row is empty, continue to the next row
        if (length(rowA) == 0) {
            continue;
        }
        for (int j = 1; j <= size(A); j++) {
            List rowB = newB->rows[j];
            // If the column is empty, continue to the next column
            if (length(rowB) == 0) {
                continue;
            }
            // Calculate the dot product of rowA and rowB
            double product = vectorDot(rowA, rowB);
            // If the dot product is not zero, add an entry to the product matrix
            if (product != 0.0) {
                Entry e = newEntry(product, j);
                append(productAB->rows[i], e);
                productAB->non_zero++;
            }
        }
    }   
    freeMatrix(&newB);
    return productAB;
}

void printMatrix(FILE* out, Matrix M) {
    for (int i = 1; i <= size(M); i++) {
        moveFront(M->rows[i]);
        bool printed = false;
        while (index(M->rows[i]) >= 0) {
            // If the value is non-zero
            if (((Entry)get(M->rows[i]))->value != 0.0) {
                // Print the row index if it hasn't been printed already
                if (!printed) {
                    fprintf(out, "%d: ", i);
                    printed = true;
                }
                // Print the non-zero entry
                Entry E = get(M->rows[i]);
                if (E->value != 0) fprintf(out, "(%d, %.1lf) ", E->position, E->value);
            }
            moveNext(M->rows[i]);
        }
        // Print a newline if any entries were printed for this row
        if (printed) {
            fprintf(out, "\n");
        }
    }
    fprintf(out, "\n");
}

