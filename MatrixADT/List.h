//-----------------------------------------------------------------------------
//  List.h
//  Aryan Patel
//-----------------------------------------------------------------------------

typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void); 
void freeList(List* pL);


// Access functions -----------------------------------------------------------

int length(List L); 
int index(List L); 
void* front(List L); //altered return type 
void* back(List L);  //altered return type
void* get(List L);   //altered return type
//bool equals(List A, List B);

// Manipulation procedures ----------------------------------------------------

void clear(List L); 
void set(List L, void* x); 
void moveFront(List L); 
void moveBack(List L); 
void movePrev(List L); 
void moveNext(List L); 
void prepend(List L, void* x); 
void append(List L, void* x); 
void insertBefore(List L, void* x);
void insertAfter(List L, void* x); 
void deleteFront(List L); 
void deleteBack(List L); 
void delete(List L);

// Other operations -----------------------------------------------------------

//void printList(FILE* out, List L); 
//List copyList(List L); 