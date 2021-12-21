#include <cstring>
#include "room.h"
#include "item.h"
#include <map>
#include <vector>

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

map<int, Room*> Room::getExit() {
  return exits;
}

void Room::setExit(int index, Room *newExit) {
  exits[index] = newExit;
}

int Room::getExitSize() {
  return exits.size();
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

Item Room::getItem(int itemID) {
  for(int i = 0; i < inventory.size(); i++) {
    if(inventory[i].getID() == itemID) {
      return inventory[i];
    }
  }
  return inventory[0];
}

Item Room::takeItem(int itemID) {
  Item* nullItem = new Item(1);
  for(int i = 0; i < inventory.size(); i++) {
    if(inventory[i].getID() == itemID) {
      cout << "Vector size: " << inventory.size() << " (before clone)" << endl;
      Item* itemptr = new Item(inventory[i].getID(), inventory[i].getName(), inventory[i].getDesc());
      cout << "Vector size: " << inventory.size() << " (after clone)" << endl;
      inventory.erase(inventory.begin() + (i - 1));
      cout << "Vector size: " << inventory.size() << " (after erase)" << endl;
      return *itemptr;
    }
  }
  return *nullItem;
}

void Room::giveItem(Item newItem) {
  inventory.push_back(newItem);
}

int Room::getInventorySize() {
  return inventory.size();
}
