#include <iostream>
#include <map>
#include <vector>
#include "item.h"
#ifndef ROOM_H
#define ROOM_H

using namespace std;

class Room {  
public:
  Room(int iID);
  char* getName();
  void setName(char newName[]);
  char* getDesc();
  void setDesc(char newDesc[]);
  int getID();
  void setID(int newID);
  map<int, Room*> getExit();
  void setExit(int index, Room *newExit);
  int getExitSize();
  int* getCoord();
  void setCoord(int x, int y);
  Item getItem(int itemID);
  Item takeItem(int itemID);
  void giveItem(Item newItem);
  int getInventorySize();
private:
  int ID;
  int coord[2];
  char name[20];
  char desc[50];
  map<int, Room*> exits;
  vector<Item> inventory;  
};
#endif
