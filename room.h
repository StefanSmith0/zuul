#include <iostream>
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
  char* getExits();
  void setExits(char newExits[]);
  int* getCoord();
  void setCoord(int x, int y);
 private:
  int ID;
  int coord[2];
  char name[20];
  char desc[50];
  char exits[12];
};
#endif
