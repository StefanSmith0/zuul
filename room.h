#include <iostream>
#include <map>
#include <vector>
#include <utility>
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
  Room* getExit(int exitDirection);
  void setExit(int index, Room *newExit);
  int getExitSize();
  int getCoord(int pos);
  void setCoord(int x, int y);
  Item getItem(int itemID);
  Item* takeItem(char itemRequested[]);
  void giveItem(Item newItem);
  int getInventorySize();
  void setVisible();
  bool isVisible();
private:
  int ID;
  int coord[2];
  char name[20];
  char desc[150];
  map<int, Room*> exits;
  vector<Item> inventory;
  bool visible;
};
#endif
