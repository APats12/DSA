//-----------------------------------------------------------------------------
//  List.c
//  Aryan Patel
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// Private Constructor --------------------------------------------------------
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
	void* data; //changed to void for pa4
    Node next;
    Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int len;
	int cursorIndx;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

Node newNode(void* data){
    Node node = malloc(sizeof(NodeObj));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return(node);
}

void freeNode(Node *pN){
    if (pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

List newList(void) { 
    List L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->len = 0;
    L->cursorIndx = -1;
    return L;
}

void freeList(List* pL){
    if( pL != NULL && *pL != NULL ){
        clear(*pL);
    }
    free(*pL);
    *pL = NULL;
}

// Access functions -----------------------------------------------------------

int length(List L) {
    if (L == NULL) {
        printf("List Error: calling length() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    else {
        return L->len;  
    }
}

int index(List L) {
    if (L == NULL) {
        printf("List Error: calling index() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    else if(L->cursorIndx == -1){
        return -1;
    }
    else{
        return L->cursorIndx;  
    }
}

void* front(List L) {
    if (L == NULL) {
        printf("List Error: calling front() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    else if(length(L) == 0){
        printf("List Error: calling front() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    else{
        return L->front->data;
    }     
}

void* back(List L) {
    if (L == NULL) {
        printf("List Error: calling back() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    else if(length(L) == 0){
        printf("List Error: calling back() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    else{
        return L->back->data;
    }     
}

void* get(List L){
	if(L == NULL){
        printf("List Error: calling get() on NULL List\n");
        exit(EXIT_FAILURE);
    }
	else if(length(L) <= 0){
        printf("List Error: calling get() on NULL List\n");
        exit(EXIT_FAILURE);
	}
	else if(index(L) < 0){
        printf("List Error: calling get() on NULL List\n");
        exit(EXIT_FAILURE);
	}
    else{
        return L->cursor->data;
    }
}

// bool equals(List A, List B){
//     if (A == NULL || B == NULL){
//          printf("List Error: calling equals() on NULL List\n");
//          exit(EXIT_FAILURE);
//     }
//     if(length(A) != length(B)){ //checking if they are same length
//         return false;
//     }
//     Node a = NULL; //temp node to compare elements from List A
//     Node b = NULL; //temp node to compare elements from List B

//     moveFront(A);
// 	moveFront(B);

//     a = A->cursor;
// 	b = B->cursor;

//     for (int i = 0; i < length(A); i++){ //looping through List using the length
//         if (a->data != b->data) { //comparing each element 
//             return false;
//         }
//         a = a->next; //incrementing
//         b = b->next; //incrementing 
//     }
//     return true;
// }

// Manipulation procedures ----------------------------------------------------

void clear(List L) {
    if(L == NULL){
        printf("List Error: calling clear() on NULL List\n");
        exit(EXIT_FAILURE);
    }
	while (length(L) > 0){
		deleteBack(L);	
	}
    L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->len = 0;
	L->cursorIndx = -1;
}

void set(List L, void* x){
	if(L == NULL){
		printf("List Error: calling set() on NULL List\n");
		exit(EXIT_FAILURE);
	} 
	if(length(L) <= 0){
        printf("List Error: calling clear() on empty List\n");
        exit(EXIT_FAILURE);
	}
	if(index(L) < 0){
        printf("List Error: calling clear() on negative index\n");
        exit(EXIT_FAILURE);
	}
	L->cursor->data = x;
}

void moveFront(List L){
    if(L == NULL){
        printf("List Error: calling moveFront() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
        return;
    }
    L->cursor = L->front;
	L->cursorIndx = 0;
}

void moveBack(List L){
    if(L == NULL){
        printf("List Error: calling moveBack() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
        return;
    }
    L->cursor = L->back;
	L->cursorIndx = length(L)-1;
}

void movePrev(List L){
	if(L == NULL){
		printf("List Error: calling movePrev() on NULL List\n");
		exit(EXIT_FAILURE);
	}
	
	if(index(L) == -1){
		return;
	}
	if(index(L) == 0){
		L->cursor = NULL;
		L->cursorIndx = -1;
	}
	
	else{
		L->cursor = L->cursor->prev;
		L->cursorIndx = L->cursorIndx - 1;
	}
	
}

void moveNext(List L){
	if(L == NULL){
		printf("List Error: calling moveNext() on NULL List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) == length(L) -1){
		L->cursor = NULL;
		L->cursorIndx = -1;
	}
	else if(index(L) >=0){
		L->cursor = L->cursor->next;
		L->cursorIndx = L->cursorIndx + 1;
	}
	
	else{
		return;
	}		
}

void prepend(List L, void* x){
	if(L == NULL){
		printf("List Error: calling prepend() on NULL List\n");
		exit(EXIT_FAILURE);
	}
	Node n = newNode(x);
    if (L->front == NULL){ //empty list so temp is front and back
		//Node n = newNode(x);
        L->front = n;
        L->back = n;
    }
    else{
	    //Node n = newNode(x);
        L->front->prev = n; 
        n->next = L->front;
        L->front = n;
        L->cursorIndx ++;
    }
    L->len++;
}

void append(List L, void* x){
	if(L == NULL){
		printf("List Error: calling append() on NULL List\n");
		exit(EXIT_FAILURE);
	}
	Node n = newNode(x);
	if(length(L) == 0){
		L->front = n;
		L->back = n;
	}
	else {
		n->prev = L->back;
		L->back->next = n;
		L->back = n;
	}	
	L->len++;
	
}

void insertBefore(List L, void* x){
	if(L->cursor == NULL){
		printf("List Error: calling insertBefore() with  undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0){
		printf("List Error: calling insertBefore() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0){
		printf("List Error: calling insertBefore() on negative index\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor != L->front){
		Node temp = newNode(x);
            temp->next = L->cursor;
            temp->prev = L->cursor->prev;
            L->cursor->prev->next = temp;
            L->cursor->prev = temp;
            L->len++;
            if (L->cursor != NULL){
                L->cursorIndx++;
            }
	}
	else{
		prepend(L, x);
	}
}



void insertAfter(List L, void* x){
    if(L->cursor == NULL){
        printf("List Error: insertAfter() called with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
	if(length(L) <= 0){
        printf("List Error: insertAfter() called on empty list\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor == L->back){
        Node n = newNode(x);
        L->back->next = n;
        n->prev = L->back;
        L->back = n;
    }
    else if(L->cursor != L ->back){
        Node n = newNode(x);
		L->cursor->next->prev = n;
		n->next = L->cursor->next;
		n->prev = L->cursor;
		L->cursor->next = n;
    }
    L->len++;
}


void deleteFront(List L){
	if(L == NULL){
		printf("List Error: calling deleteFront() on NULL List\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0){
		printf("List Error: calling deleteFront() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) == 0){
		movePrev(L);
	}
	if (index(L) > 0){
		L->cursorIndx--;
	}
	if (length(L) == 1){
		freeNode(&L->front);
        L->len -= 1;
		return;
	}
	Node n = L->front->next;
	L->front->next->prev = NULL;
	L->len = length(L) - 1;
	freeNode(&L->front);
	L->front = n;

}

void deleteBack(List L){
	if(L == NULL){
		printf("List Error: calling deleteBack() on NULL List\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0){
		printf("List Error: calling deleteBack() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == L->back) {
		moveNext(L);
	}
	if (length(L) == 1) {
		freeNode(&L->front);
        L->len -= 1;
        return;
    }
	Node n = L->back->prev;
	L->back->prev->next = NULL;
	L->len = length(L) - 1;
	freeNode(&L->back);
	L->back = n;

}

void delete(List L){
    if(L == NULL){
        printf("List Error: calling delete() on NULL List\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) <= 0){
        printf("List Error: calling delete() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("List Error: calling delete() on negative index\n");
        exit(EXIT_FAILURE);
    }
    Node temp = L->cursor;
    Node prev = L->cursor->prev;
    Node next = L->cursor->next;
    if(prev != NULL){
        prev->next = next;
    }
    if(next != NULL) {
        next->prev = prev;
    }
    if(L->cursor == L->front){
        L->front = next;
    }
    if(L->cursor == L->back) {
        L->back = prev;
    }
    L->cursor = NULL;
    L->cursorIndx = -1;
    L->len = length(L) - 1;
    freeNode(&temp);
}

// Other operations -----------------------------------------------------------

// void printList(FILE* out, List L){
// 	if(L == NULL){
// 		printf("List: printList(): List is NULL\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	Node n = L->front;
// 	for(int i=0; i<length(L); i++) {
// 		fprintf(out, "%d ", n->data);
// 		n = n->next;
// 	}
// }

// List copyList(List L){
// 	if(L == NULL){
// 		printf("List: copyList(): List is NULL \n");
// 		exit(EXIT_FAILURE);
// 	}
// 	List l = newList();
// 	moveFront(L);
// 	Node n = L->front;
// 	while(n != NULL){
// 		append(l,n->data);
// 		n = n->next;
// 	}
// 	return l;
// }