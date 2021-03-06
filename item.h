#include <iostream>
#ifndef ITEM_H
#define ITEM_H

using namespace std;

class Item {
 public:
  Item(int newID, char newName[20], char newDesc[100]);
  Item(int newID);
  int getID();
  char* getName();
  char* getDesc();
  Item clone();
private:
  int id;
  char name[20];
  char desc[100];
};

#endif
