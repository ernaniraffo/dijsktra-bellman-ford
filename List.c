// ---------------------------------------------------------
// Ernani Raffo
// List.c
// Implementation file for List ADT
// ---------------------------------------------------------

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "List.h"

// Structs ------------------------------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj {
    int data;
    Node previous;
    Node next;
} NodeObj;

// private ListObj type
typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int cursor_index;
} ListObj;

// Constructors-Destructors -------------------------------------------------------------------------

// newNode()
// Creates and returns a pointer to a node.
Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->previous = NULL;
    N->next = NULL;
    return N;
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
    return;
}

// newList()
// Creates and returns a reference to a List.
List newList(void) {
    List L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0; // empty list has no length
    L->cursor_index = -1; // undefined cursor (default state)
    return L;
}

// freeList()
// Frees all heap memory associated with *pL, sets *pL to NULL.
void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
    return;
}

// Access functions ---------------------------------------------------------------------------------

// Returns the number of elements in L
int length(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: Calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

// Returns index of cursor element if defined, -1 otherwise
int index(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: Calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        return L->cursor_index;
    }
    return -1;
}

// Returns front element of L.
// Pre: length() > 0
int front(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: Calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List error: Calling front() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

// Returns back element of L.
// Pre: length() > 0
int back(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: Calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List error: Calling back() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

// Returns cursor element of L.
// Pre: length() > 0, index() >= 0
int get(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: Calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List error: Calling get() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "List error: Calling get() on a List with an undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

// Returns true iff Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B) {
    int eq = 0;
    Node N = NULL;
    Node M = NULL;

    if (A == NULL || B == NULL) {
        fprintf(stderr, "List error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    eq = (A->length == B->length);
    N = A->front;
    M = B->front;
    while (eq && N != NULL) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Manipulation Procedures --------------------------------------------------------------------------

// Resets L to its original empty state
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    while (length(L) > 0) {
        deleteFront(L);
    }
    return;
}

// set()
// Overwrites the cursor element's data with x
// Pre: length() > 0, index() >= 0
void set(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List error: calling set() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "List error: calling set() on a List with an undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    L->cursor->data = x;
    return;
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing
void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) > 0) {
        L->cursor = L->front;
        L->cursor_index = 0;
    }
    return;
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing
void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) > 0) {
        L->cursor = L->back;
        L->cursor_index = L->length - 1;
    }
    return;
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L
// ; if cursor is defined and at front, cursor becomes undefined
// ; if cursor is undefined do nothing
void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if ((index(L) >= 0) && (L->cursor != L->front)) {
        L->cursor = L->cursor->previous;
        L->cursor_index -= 1;
    }
    else if ((index(L) >= 0) && (L->cursor == L->front)) {
        L->cursor = NULL;
        L->cursor_index = -1;
    }
    return;
}

// moveNext()
// If cursor is defined and not at back, move cursor one step toward the back of L
// ; if cursor is defined and at back, cursor becomes undefined
// ; if cursor is undefined do nothing
void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if ((index(L) >= 0) && (L->cursor != L->back)) {
        L->cursor = L->cursor->next;
        L->cursor_index += 1;
    }
    else if ((index(L) >= 0) && (L->cursor == L->back)) {
        L->cursor = NULL;
        L->cursor_index = -1;
    }
    return;
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node N = newNode(x);
    if (length(L) > 0) {
        N->next = L->front;
        L->front->previous = N; // inserts node before front
        L->front = N; // sets the node as new front element
        L->length += 1;
        if (index(L) >= 0) {
            L->cursor_index += 1;
        }
    } else {
        L->front = N;
        L->back = N;
        L->length += 1;
    }
    return;
}

// append()
// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node N = newNode(x);
    if (length(L) > 0) {
        N->previous = L->back;
        L->back->next = N;
        L->back = N;
        L->length += 1;
    } else {
        L->front = N;
        L->back = N;
        L->length += 1;
    }
    return;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List error: calling insertBefore() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "List error: calling insertBefore() on a List with an undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    Node N = newNode(x);
    N->next = L->cursor;
    N->previous = L->cursor->previous;

    if (L->cursor->previous) {
        L->cursor->previous->next = N;
    } else {
        L->front = N; // if cursor has no previous, it must be at the front.
    }

    L->cursor->previous = N;
    L->length += 1;
    L->cursor_index += 1; // cursor index goes up since element was placed before it
    return;
}

// insertAfter()
// Insert new element after cursor.
// Pre: length() > 0, index() >= 0
void insertAfter(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling insertAfter() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List error: calling insertAfter() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "List error: calling insertAfter() on a List with an undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    Node N = newNode(x);
    N->previous = L->cursor;
    N->next = L->cursor->next;

    if (L->cursor->next) {
        L->cursor->next->previous = N;
    } else {
        L->back = N; // if cursor has no next, it must have been at the back.
    }

    L->cursor->next = N;
    L->length += 1;
    return;
}

// deleteFront()
// Delete the front element.
// Pre: length() > 0
void deleteFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling deleteFront() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List error: calling deleteFront() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    Node N = L->front;
    L->front = L->front->next; // New front element

    if (N == L->cursor) {
        L->cursor = NULL;
        L->cursor_index = -1; // deleting cursor makes index undefined
    } else if (index(L) >= 0) {
        L->cursor_index -= 1;
    }

    if (L->front) {
        L->front->previous = NULL; // front element has no previous Node
    }

    freeNode(&N);
    L->length -= 1;
    return;
}

// deleteBack()
// Delete the back element.
// Pre: length() > 0
void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling deleteBack() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List error: calling deleteBack() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    Node N = L->back;

    L->back = L->back->previous; // new back
    if (L->back) {
        L->back->next = NULL; // back has no next node
    }

    if (N == L->cursor) {
        L->cursor = NULL;
        L->cursor_index = -1; // deleting cursor element means cursor becomes undefined
    }

    freeNode(&N);
    L->length -= 1;
    return;
}

// delete()
// Delete cursor element, making cursor undefined
// Pre: length() > 0, index() >= 0
void delete(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling delete() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        fprintf(stderr, "List error: calling delete() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fprintf(stderr, "List error: calling delete() on a List with an undefined cursor\n");
        exit(EXIT_FAILURE);
    }

    // take cursor out of linked list

    if (L->cursor->next) {
        L->cursor->next->previous = L->cursor->previous;
    } else { // cursor is at the back since it has no next node
        L->back = L->cursor->previous;
    }

    if (L->cursor->previous) {
        L->cursor->previous->next = L->cursor->next;
    } else { // cursor is at the front since it has no previous node
        L->front = L->cursor->next;
    }

    freeNode(&(L->cursor));
    L->cursor_index = -1;
    L->length -= 1;
    return;
}

// Other functions ---------------------------------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting of a space
// separated sequence of integers with front on left
void printList(FILE* out, List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling printList() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    for (Node N = L->front; N != NULL; N = N->next) {
        fprintf(out, "%d ", N->data);
    }
    fprintf(out, "\n");
    return;
}

// copyList()
// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state of the cursor in L.
// The state of L is unchanged.
List copyList(List L) {
    if (L == NULL) {
        fprintf(stderr, "List error: calling copyList() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    List cL = newList();
    for (Node N = L->front; N != NULL; N = N->next) {
        append(cL, N->data);
    }
    return cL;
}

// concatList()
// Returns a new List which is the concatenation of A and B.
// The cursor in the new List is undefined, regardless of the states of the cursors
// in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "List error: calling concatList() on a NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    List C = copyList(A); // first get int sequence from List A

    // append B's int sequence after A's int sequence in List C
    for (Node N = B->front; N != NULL; N = N->next) {
        append(C, N->data);
    }

    return C;
}
