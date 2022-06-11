// -------------------------------------------------------------------------------------------
// Ernani Raffo
// List.h
// Header file for List.c
// -------------------------------------------------------------------------------------------

#pragma once

#include <stdbool.h>
#include <stdio.h>

// Exported List Type
typedef struct ListObj* List;

// Constructors-Destructors ------------------------------------------------------------------

// newList()
// Creates and returns a new list
List newList(void);

// freeList()
// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList(List* pL);

// Accessor functions ------------------------------------------------------------------------

// length()
// Returns the number of elements in List L.
int length(List L);

// index()
// Returns index of the cursor element if defined, -1 otherwise.
int index(List L);

// front()
// Returns the front element of List L.
// Pre: length() > 0
int front(List L);

// back()
// Returns the back element of List L.
// Pre: length() > 0
int back(List L);

// get()
// Returns the cursor element of List L.
// Pre: length() > 0, index() >= 0
int get(List L);

// equals()
// Returns true iff A and B are in the same state, and false otherwise.
bool equals(List A, List B);

// Manipulation procedures -------------------------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L);

// set()
// Overwrites the cursor's element data with x.
// Pre: length() > 0, index() >= 0
void set(List L, int x);

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L);

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L);

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L
// ; if cursor is defined and at front, cursor becomes undefined
// ; if cursor is undefined do nothing.
void movePrev(List L);

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L
// ; if cursor is defined and at back, cursor becomes undefined
// ; if cursor is undefined do nothing.
void moveNext(List L);

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x);

// append()
// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int x);

// insertBefore()
// Insert new element before cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L, int x);

// insertAfter()
// Insert new element after cursor.
// Pre: length() > 0, index() >= 0
void insertAfter(List L, int x);

// deleteFront()
// Delete the front element of L
// Pre: length() > 0
void deleteFront(List L);

// deleteBack()
// Delete the back element of L
// PRe: length() > 0
void deleteBack(List L);

// delete()
// Delete the cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L);

// Other operations --------------------------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L);

// copyList()
// Returns a new list representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state of the cursor in L.
// The state of L in unchanged.
List copyList(List L);

// Optional ----------------------------------------------------------------------------------

// concatList()
// Returns a new list which is the concatenation of A and B.
// The cursor in the new List is undefined, regardless of the states
// of the cursors in A and B. The states of A and B are unchanged.
List concatList(List A, List B);
