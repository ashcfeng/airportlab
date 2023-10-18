#include "slist.h"
#include <stddef.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// Constructor
LinkedList::LinkedList() {
  head = NULL;
  curr = NULL;
  temp = NULL;
}
// Destructor
LinkedList::~LinkedList() {}
// add(value)				//Adds a new value to the end of this
// list.
void LinkedList::add(Airport a) {
  node *n = new node;
  n->next = NULL;
  n->data = a;
  if (head != NULL) {
    curr = head;
    while (curr->next != NULL) {
      curr = curr->next;
    }
    curr->next = n;
  } else {
    head = n;
  }
}
// clear()					//Removes all elements from this
// list.
void LinkedList::clear() {
  curr = head;
  temp = NULL;
  while (curr != NULL) {
    temp = curr->next;
    free(curr);
    curr = temp;
  }
}

// equals(list)				//Returns true if the two lists contain
// the same elements in the same order.
bool LinkedList::equals(LinkedList l) {
  curr = head;
  while (curr != NULL && l.curr != NULL) {
    if (!(curr->data).equals(l.curr->data)) {
      return false;
    }
    curr = curr->next;
    l.curr = l.curr->next;
  }
  return (curr == NULL && l.curr == NULL);
}
// get(index)				//Returns the element at the specified index
// in this list.
Airport LinkedList::get(int index) {
  int i = 0;
  curr = head;
  while (curr != NULL) {
    if (i == index) {
      return curr->data;
    }
    i++;
    curr = curr->next;
  }
}
// insert(index, value)		//Inserts the element into this list before the
// specified index.
void LinkedList::insert(int index, Airport a) {
  curr = head;
  node *n = new node;
  if (head != NULL) {
    if (index == 0) {
      n->data = a;
      n->next = head;
      head = n;
    } else if (index == size()) {
      add(a);
    } else {
      int i = 0;
      while (i < index - 1) {
        curr = curr->next;
        i++;
      }
      n->next = curr->next;
      curr->next = n;
    }
  } else {
    add(a);
  }
}

// exchg(index1, index2)		//Switches the payload data of specified
// indexex.
void LinkedList::exchg(int index1, int index2) {
  node* curr1 = head;
  node* curr2 = head;
  if (index1 == index2) {
    return;
  }
  int i1 = 0;
  while (i1 < index1) {
    curr1 = curr1->next;
    i1++;
  }
  int i2 = 0;
  while (i2 < index2) {
    curr2 = curr2->next;
    i2++;
  }
  Airport temp;
  temp = curr2->data;
  curr2->data = curr1->data;
  curr1->data = temp;
}
// swap(index1,index2)		//Swaps node located at index1 with node at
// index2
void LinkedList::swap(int index1, int index2) {
  if (index1 == index2) {
    return;
  }
  node* prev1 = NULL;
  node* prev2 = NULL;
  node* curr1 = head;
  node* curr2 = head;
  int i1 = 0;
  while (i1 < index1) {
    prev1 = curr1;
    curr1 = curr1->next;
    i1++;
  }
  int i2 = 0;
  while (i2 < index2) {
    prev2 = curr2;
    curr2 = curr2->next;
    i2++;
  }
  if (curr1 == NULL || curr2 == NULL) {
    return;
  } 
  if (prev1 == NULL) {
    head = curr2;
  } else {
    prev1->next = curr2;
  }
  if (prev2 == NULL) {
    head = curr1;
  } else {
    prev2->next = curr1;
  }
  temp = curr2->next;
  curr2->next = curr1->next;
  curr1->next = temp;
}
// isEmpty()				//Returns true if this list contains no
// elements.
bool LinkedList::isEmpty() {
  if (head == NULL) {
    return true;
  }
}
// remove(index)			//Removes the element at the specified index
// from this list.
void LinkedList::remove(int index) {
  curr = head;
  if (head != NULL) {
    if (index == 0) {
      head = head->next;
      curr->next = NULL;
      free(curr);
    } else {
      int i = 0;
      while (i < index - 1) {
        curr = curr->next;
        i++;
      }
      node* del = curr->next;
      curr->next = curr->next->next;
      del->next = NULL;
      free(del);
    }
  }
}
// set(index, value)		//Replaces the element at the specified index in
// this list with a new value.
void LinkedList::set(int index, Airport a) {
  curr = head;
  int i = 0;
  while (curr != NULL && i < index) {
    curr = curr->next;
    i++;
  }
  curr->data = a;
}

// size()					//Returns the number of elements in
// this list.
int LinkedList::size() {
  int length = 0;
  curr = head;
  while (curr != NULL) {
    length++;
    curr = curr->next;
  }
  return length;
}

LinkedList::node* LinkedList::getFirst() {
  return head;
}

LinkedList::node* LinkedList::getLast() {
  temp = head; 
  while (temp != NULL && temp->next != NULL) { 
      temp = temp->next; 
  } 
  return temp; 
}
// DO NOT IMPLEMENT >>> subList(start, length)	//Returns a new list containing
// elements from a sub-range of this list.

// DO NOT IMPLEMENT >>> toString()				//Converts the list to
// a printable string representation.
