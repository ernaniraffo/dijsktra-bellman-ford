// ---------------------------------------------------------
// Ernani Raffo
// ListTest.c
// Testing module for List ADT
// ---------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

int main(int argc, char* argv[]) {

    List A = newList();
    List B = newList();

    for (int i = 0; i < 10; i += 1) {
        append(A, i);
        append(B, i);
    }

    printList(stdout, A);
    printList(stdout, B);
    printf("Equals: %s\n", equals(A, B) ? "true" : "false");
    printf("\n");

    moveFront(A);
    moveBack(B);

    int cA = get(A);
    set(A, get(B));
    set(B, cA);

    printList(stdout, A);
    printList(stdout, B);

    printf("A's cursor: %d\n", get(A));
    printf("B's cursor: %d\n", get(B));
    printf("\n");

    moveBack(B);
    for (moveBack(A); index(A) >= 0; movePrev(A)) {
        set(B, get(A));
        movePrev(B);
    }

    printList(stdout, A);
    printList(stdout, B);
    printf("Equals: %s\n", equals(A, B) ? "true" : "false");
    printf("Length A == Length B: %s\n\n", length(A) == length(B) ? "true": "false");

    printf("New lists...\n");
    clear(A);
    clear(B);
    int new_length = 10;
    for (int i = 0; i < new_length; i += 1) {
        append(A, (2*i) + 1); // odd list
    }

    for (int i = 0; i < new_length; i += 1) {
        append(B, 2*i); // even list
    }

    printList(stdout, A);
    printList(stdout, B);
    printf("\n");

    moveFront(A);
    moveBack(B);
    int dcA = get(A);
    printf("A's cursor (Front element): %d\n", dcA);
    printf("front(A) = %d\n", front(A));
    int dcB = get(B);
    printf("B's cursor (Back element): %d\n", dcB);
    printf("back(B) = %d\n", back(B));
    printf("\n");

    deleteFront(A);
    deleteBack(B);
    printf("Deleting cursors...\n");
    printList(stdout, A);
    printList(stdout, B);
    printf("\n");

    moveFront(A);
    printf("A's new cursor element (front): %d\n", get(A));
    moveBack(B);
    printf("B's new cursor element (back): %d\n", get(B));
    printf("\n");

    insertBefore(A, dcA);
    insertAfter(B, dcB);

    printf("Restoring old elements...\n");
    printf("A and B should be back to their state before deleting cursors\n");
    printList(stdout, A);
    printList(stdout, B);
    printf("\n");

    printf("New List C: The concatenation of A and B\n");
    List C = copyList(A);
    for (moveFront(B); index(B) >= 0; moveNext(B)) {
        append(C, get(B));
    }
    printList(stdout, C);
    printf("\n");

    printf("New List D: The reverse of List C\n");
    List D = newList();
    for (moveFront(C); index(C) >= 0; moveNext(C)) {
        prepend(D, get(C));
    }
    printList(stdout, D);
    printf("\n");

    moveFront(D);
    printf("Deleting D's front element (cursor)...\n");
    delete(D);
    printList(stdout, D);

    freeList(&A);
    freeList(&B);
    freeList(&C);
    freeList(&D);

    return 0;
}


