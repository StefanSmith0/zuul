#include <cstring>
#include "item.h"

using namespace std;

Item::Item(int newID, char newName[20], char newDesc[100]) {
  id = newID;
  strcpy(name, newName);
  strcpy(desc, newDesc);
  cout << "Item Constructed." << endl;
}

Item::Item(int newID) {
  id = 0;
  strcpy(name, "defaultName");
  strcpy(desc, "defaultDesc");
  cout << "Default Item Constructed." << endl;
}

int Item::getID() {
  return id;
}

char* Item::getName() {
  char *localName = new char[strlen(name) + 1];
  strcpy(localName, name);
  return localName;
}

char* Item::getDesc() {
  char *localDesc = new char[strlen(desc) + 1];
  strcpy(localDesc, desc);
  return localDesc;
}

Item Item::clone() {
  Item localItem(id, name, desc);
  cout << "Item " << id << " cloned." << endl;
  return localItem;
}