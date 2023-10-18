#include "airport.h"
class LinkedList {
public:
  struct node {
    node* next;
    Airport data;
    double distance;
  };
  node* head;
  node* curr;
  node* temp;
  LinkedList();
  ~LinkedList();
  void add(Airport a);
  void clear();
  bool equals(LinkedList list);
  Airport get(int index);
  void insert(int index, Airport a);
  void exchg(int index1, int index2);
  void swap(int index1, int index2);
  bool isEmpty();
  void remove(int index);
  void set(int index, Airport a);
  int size();
  node* getFirst();
  node* getLast();
};