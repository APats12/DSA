//-----------------------------------------------------------------------------
//  Lex.c
//  Aryan Patel
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "List.h"
#define MAX_LEN 300

char *strdup (const char *s) {
    char *v = malloc(strlen(s) + 1);
    if (v == NULL) return NULL;
    strcpy(v,s);
    return v;
}

char** read(FILE* inFile, int lines){
    char** inFileArray = calloc(lines, sizeof(char**));
    char line[MAX_LEN];
    for(int x = 0; x < lines; x++){
        fgets(line, MAX_LEN, inFile);
        inFileArray[x] = strdup(line);
    }
    return inFileArray;
}

List insertionSort(char** A, int n){
    List l = newList();
    if(n>0){
        append(l, 0);
    } 
    for(int x=1; x<n; x++){
        char *temp = A[x];
        int i = x - 1;
        moveFront(l);
        while(index(l)!=i ){
            moveNext(l);
        }
        while(i>-1 && strcmp(temp, A[get(l)])<0 ){
            i--;
            movePrev(l);
        }
        if(index(l) == -1){
            prepend(l, x);
        } else {
            insertAfter(l, x);
        }
    }
    return l;
}

int main(int argc, char* argv[]){
    char line[MAX_LEN];
    // check command line for correct number of arguments
    if(argc != 3) {
        printf("Invalid number of inputs");
        exit(1);
    }
    // open files for reading and writing
    FILE* input = fopen(argv[1], "r");
    if(input == NULL){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    FILE* output = fopen(argv[2], "w");
    if( output==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // read each line of input file and sort
    int linect = 0;
    while( fgets(line, MAX_LEN, input) != NULL) {
        linect++;
    }

    fclose(input);

    input = fopen(argv[1], "r");

    char** stringArray = read(input, linect); 

    List L = insertionSort(stringArray, linect);

    moveFront(L);

    for(int x=0; x<linect; x++){
        fprintf(output, "%s", stringArray[get(L)]);
        moveNext(L);
    }
    
    fclose(input);
    fclose(output);
    for(int x=0; x<linect; x++){
        free(stringArray[x]);
    }
    free(stringArray);
    freeList(&L);
    return(0);
}