#include <cstring>
#include "Room.h"

using namespace std;

Room::Room(int iID) {
  ID = iID;
  cout << "Room " << ID << " Initialized" << endl;
  coord[0] = 100;
  coord[1] = 100;
}

char* Room::getName() {
  char *localName = new char[strlen(name) + 1];
  strcpy(localName, name);
  return localName;
}

void Room::setName(char newName[]) {
  strcpy(name, newName);
}

char* Room::getDesc() {
  char *localDesc = new char[strlen(desc) + 1];
  strcpy(localDesc, desc);
  return localDesc;
}

void Room::setDesc(char newDesc[]) {
  strcpy(desc, newDesc);
}

int Room::getID() {
  return ID;
}

void Room::setID(int newID) {
  ID = newID;
}

char* Room::getExits() {
  char *localExits = new char[strlen(exits) + 1];
  strcpy(localExits, exits);
  return localExits;
}

void Room::setExits(char newExits[]) {
  strcpy(exits, newExits);
}

int* Room::getCoord() {
  int *localCoord = new int[2];
  localCoord[0] = coord[0];
  localCoord[1] = coord[1];
  return localCoord;
}

void Room::setCoord(int x, int y) {
  coord[0] = x;
  coord[1] = y;
}
