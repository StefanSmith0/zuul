#include <cstring>
#include "room.h"
#include "item.h"
#include <map>
#include <vector>
#include <utility>

using namespace std;

Room::Room(int iID) {
  ID = iID;
  strcpy(name, "Default name");
  strcpy(desc, "Default description");
  coord[0] = 100;
  coord[1] = 100;
  visible = false;
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

Room* Room::getExit(int exitDirection) {
  if(exits.find(exitDirection) != exits.end()) {
    Room* exitptr = exits[exitDirection];
    return exitptr;
  }
  return NULL;
}

void Room::setExit(int index, Room *newExit) {
  exits[index] = newExit;
}

int Room::getExitSize() {
  return exits.size();
}

int Room::getCoord(int pos) {
  int localCoord = 0;
  localCoord = coord[pos];
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

Item* Room::takeItem(char requestedItem[]) {
  for(vector<Item>::iterator it = inventory.begin(); it != inventory.end(); it++) {
    if(!strcmp(it->getName(), requestedItem)) {
      Item* itemptr = new Item(it->getID(), it->getName(), it->getDesc());
      inventory.erase(it);
      return itemptr;
    }
  }
  return NULL;
}

void Room::giveItem(Item newItem) {
  inventory.push_back(newItem);
}

int Room::getInventorySize() {
  return inventory.size();
}

void Room::setVisible() {
  visible = true;
}

bool Room::isVisible() {
  return visible;
}
