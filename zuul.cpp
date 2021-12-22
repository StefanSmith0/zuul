#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <time.h>
#include "Room.h"

using namespace std;

void printBoard(int boardSize, vector<vector<int>> &board, Room* currentRoom, vector<Room*> &vect);
void makeRooms(int roomNum, vector<Room*> &vect, vector<vector<int>> &board, map<int, vector<int>> &roomMap,
	       Item goldKey, Item redKey, Item blueKey, Item axe, Item rope);
void updateBoard(vector<vector<int>> &roomBoard, vector<Room*> &vect);
bool validnewCoord(map<int, vector<int>> roomMap, int newCoord[2]);
Room* parseCommand(char input[], vector<vector<int>> &roomBoard, vector<Room*> &vect,
		  map<int, vector<int>> roomMap, Room *currentRoom, vector<Item> &inventory); 
Room* moveToRoom(Room* currentRoom, vector<Room*> &vect);
void printRoomDetails(Room* currentRoom);
bool eventCheck(vector<Room*> &vect, Item goldKey, Item redKey, Item blueKey, Item axe, Item rope);

const int NORTH = 1;
const int EAST = 2;
const int SOUTH = 3;
const int WEST = 4;
const int boardSize = 20;

int main() {
  srand(time(0));
  int newID;
  char newName[20];
  char newDesc[100];
  
  newID = 1;
  strcpy(newName, "goldKey");
  strcpy(newDesc, "A beautiful, golden key. It might be your ticket out of here.");
  Item goldKey(newID, newName, newDesc);
  
  newID = 2;
  strcpy(newName, "redKey");
  strcpy(newDesc, "A key which appears red, hopefully not due to rust.");
  Item redKey(newID, newName, newDesc);
  
  newID = 3;
  strcpy(newName, "blueKey");
  strcpy(newDesc, "A blue key. Nice of them to color-code these.");
  Item blueKey(newID, newName, newDesc);
  
  newID = 4;
  strcpy(newName, "axe");
  strcpy(newDesc, "Sweet. This baby could probably take out the front door.");
  Item axe(newID, newName, newDesc);
  
  newID = 5;
  strcpy(newName, "rope");
  strcpy(newDesc, "There's gotta be something you can do with this.");
  Item rope(newID, newName, newDesc);

  vector<vector<int>> roomBoard(boardSize, vector<int>(boardSize));
  map<int, vector<int>> roomMap;
  vector<Item> inventory;
  int roomNum = 15;
  vector<Room*> vect;
  makeRooms(roomNum, vect, roomBoard, roomMap, goldKey, redKey, blueKey, axe, rope);
  //Main play loop
  bool running = true;
  char input[20];
  Room *currentRoom = vect[0];
  printBoard(boardSize, roomBoard, currentRoom, vect);
  cout << "Welcome to Zuul. Escape the scary mansion your friends locked you in to win!" << endl;
  while(running) {
    printRoomDetails(currentRoom);
    cout << "Enter command: ";
    cin.getline(input, 20);
    if(!strcmp(input, "quit")) {
      running = false;
    }
    else {
      currentRoom = parseCommand(input, roomBoard, vect, roomMap, currentRoom, inventory);
      updateBoard(roomBoard, vect);
      printBoard(boardSize, roomBoard, currentRoom, vect);
      if(eventCheck(vect, goldKey, redKey, blueKey, axe, rope)) {
	cout << "---Glorious Victory---" << endl;
	running = false;
      }
    }
  }
  return 0;
}

bool eventCheck(vector<Room*> &vect, Item goldKey, Item redKey, Item blueKey, Item axe, Item rope) {
  cout << "Top of eventCheck" << endl;
  Item* localItemptr;  //takeItem returns an item*
  if(vect[1]->getItem(2).getID() == 2 && vect[1]->getItem(3).getID() == 3) {
    localItemptr = vect[1]->takeItem(redKey.getName());
    localItemptr = vect[1]->takeItem(blueKey.getName());
    vect[1]->giveItem(goldKey);
    cout << "The heavy case opened with a long creak, and something inside gleamed gold." << endl;
  }
  if(vect[9]->getItem(1).getID() == 1) {
    localItemptr = vect[1]->takeItem(goldKey.getName());
    cout << "The golden key unlocked the front door's golden padlock, and you strolled out into the night toward home." << endl;
    return true;
  }
  else if(vect[9]->getItem(4).getID() == 4) {
    localItemptr = vect[1]->takeItem(axe.getName());
    cout << "The door might have been beautiful at one point, but you didn't feel too bad about destroying it in it's current state. After a couple good swings, you stepped through the hole in the door and strolled off into the night." << endl;
    return true;
  }
  if(vect[13]->getItem(5).getID() == 5) {
    cout << "You swung the rope over the balcony, and after a few moments of summoning courage, swung over and climbed down to the ground. Now to make some new friends..." << endl;
    return true;
  }
  return false;
}

void printRoomDetails(Room* currentRoom) {
  cout << "Currently in: Room " << currentRoom->getID() << " - " << currentRoom->getName() << " ";
  cout << "(" << currentRoom->getCoord(0) << "," << currentRoom->getCoord(1) << ")" << endl;
  cout << " - " << currentRoom->getDesc() << endl;
  cout << "Exits:   ";
  if(currentRoom->getExit(NORTH) != NULL) {
    cout << "(North - Room " << currentRoom->getExit(NORTH)->getID() << ")   ";
  }
  if(currentRoom->getExit(EAST) != NULL) {
    cout << "(East - Room " << currentRoom->getExit(EAST)->getID() << ")   ";
  }
  if(currentRoom->getExit(SOUTH) != NULL) {
    cout << "(South - Room " << currentRoom->getExit(SOUTH)->getID() << ")   ";
  }
  if(currentRoom->getExit(WEST) != NULL) {
    cout << "(West - Room " << currentRoom->getExit(WEST)->getID() << ")   ";
  }
  cout << endl;
  
  if(currentRoom->getInventorySize() > 0) {
    cout << "---Items in room---" << endl;
    for(int i = 0; i < currentRoom->getInventorySize(); i++) {
      cout << currentRoom->getItem(i).getName() << " - " << currentRoom->getItem(i).getDesc() << endl;
    }
    cout << "-------------------" << endl;
  }
}

Room *parseCommand(char input[], vector<vector<int>> &roomBoard, vector<Room*> &vect,
		  map<int, vector<int>> roomMap, Room *currentRoom, vector<Item> &playerInventory) {
  if(!strcmp(input, "move")) {
    currentRoom = moveToRoom(currentRoom, vect);
  }
  else if(!strcmp(input, "grab")) {
    if(currentRoom->getInventorySize() > 0) {
      cout << "Name of item to grab (case sensitive): ";
      cin.getline(input, 20);
      Item* returnedItem = currentRoom->takeItem(input);
      if(returnedItem == NULL) {
	cout << "There's no item in room named " << input << "!" << endl;
      } else {
	playerInventory.push_back(*returnedItem);
	cout << playerInventory.back().getName() << " picked up." << endl;
	}
    }
    else {
      cout << "There's nothing to grab!" << endl;
    }
  }
  else if(!strcmp(input, "drop")) {
    cout << "Name of item to drop: ";
    cin.getline(input, 20);
    bool droppedAnItem = false;
    for(vector<Item>::iterator it = playerInventory.begin(); it != playerInventory.end(); it++) {
      if(!strcmp(input, it->getName())) {
	currentRoom->giveItem(*it);
	cout << it->getName() << " dropped into " << currentRoom->getName() << endl;
	playerInventory.erase(it);
	droppedAnItem = true;
	break;
      }
    }
    if(!droppedAnItem) {
      cout << "There's no item named " << input << " in your inventory." << endl;
    }
  }
  else if(!strcmp(input, "bag")) {
    cout << "---Items in bag---" << endl;
    for(int i = 0; i < playerInventory.size(); i++) {
      cout << playerInventory[i].getName() << " - " << playerInventory[i].getDesc() << endl;
    }
    cout << "------------------" << endl;
  }
  else if(!strcmp(input, "help")) {
    cout << "---Commands---" << endl;
    cout << "\"move\" - Enters move mode. Type a cardinal direction afterward to move to an adjacent room." << endl;
    cout << "\"grab\" - Enters grab mode. Type the name of an object in the room to pick it up." << endl;
    cout << "\"drop\" - Enters drop mode. Type the name of an object from your bag to drop it." << endl;
    cout << "\"bag\" - Lists the items in your bag." << endl;
    cout << "\"quit\" - Ends the program." << endl;
  }
  else {
    cout << "Command: " << input << " not recognized." << endl;
    cout << "Type \"help\" for a guide." << endl;
  }
  return currentRoom;
}

Room* moveToRoom(Room* currentRoom, vector<Room*> &vect) {
  char input[20];
  cout << "Direction: ";
  cin.getline(input, 20);
  Room* outRoom = currentRoom;
  int moveCoord[2];
  if(!strcmp(input, "north")) {
    moveCoord[0] = currentRoom->getCoord(0);
    moveCoord[1] = currentRoom->getCoord(1) - 1;
  }
  else if(!strcmp(input, "east")) {
    moveCoord[0] = currentRoom->getCoord(0) + 1;
    moveCoord[1] = currentRoom->getCoord(1);
  }
  else if(!strcmp(input, "south")) {
    moveCoord[0] = currentRoom->getCoord(0);
    moveCoord[1] = currentRoom->getCoord(1) + 1;
  }
  else if(!strcmp(input, "west")) {
    moveCoord[0] = currentRoom->getCoord(0) - 1;
    moveCoord[1] = currentRoom->getCoord(1);
  }
  else {
    cout << "Direction not recognized. (north, east, south, west)" << endl;
  }
  for(int i = 0; i < vect.size(); i++) {
    if(moveCoord[0] == vect[i]->getCoord(0) && moveCoord[1] == vect[i]->getCoord(1)) {
      outRoom = vect.at(i);
      outRoom->setVisible();
      return outRoom;
    }
  }
  cout << "There is no room there!" << endl;
  return currentRoom;
}

void printBoard(int boardSize, vector<vector<int>> &board, Room* currentRoom, vector<Room*> &vect) {
  Room* roomptr;
  cout << "    ";
  //prints the numbers across the top
  for(int x = 0; x < boardSize; x++) {
    if(x > 9) {
      cout << x << "  ";
    }
    else {
      cout << x << "   ";
    }
  }
  cout << endl;
  for(int y = 0; y < boardSize; y++) {
    //prints the numbers down the side
    if(y < 10) {
      cout << y << "  "; //Two spaces
    }
    else {
      cout << y << " "; //One space
    }
    for(int x = 0; x < boardSize; x++) {
      for(int i = 0; i < vect.size(); i++) {
	if(x == vect[i]->getCoord(0) && y == vect[i]->getCoord(1)) {
	  roomptr = vect[i];
	}
      }
      if(board[x][y] != 0 && roomptr->isVisible()) {
	if(x == currentRoom->getCoord(0) && y == currentRoom->getCoord(1)) {
	  cout << "[**]";
	}
	else if(board[x][y] < 10) {
	  cout << "[0" << board[x][y] << "]";
	}
	else {
	  cout << "[" << board[x][y] << "]";
	}
      }
      else if(x == 10 && y == 10) {
	cout << "[00]";
      }
      else {
	cout << "[  ]";
      }
    }
    cout << endl;
  }
}

void makeRooms(int roomNum, vector<Room*> &vect, vector<vector<int>> &board, map<int, vector<int>> &roomMap,
	       Item goldKey, Item redKey, Item blueKey, Item axe, Item rope) {
  int randDirection = 0;
  int oppositeDirection = 0;
  Room* randRoom;
  int boardSize = 20;
  Room *roomptr;
  int newCoord[2];
  char newName[20];
  char newDesc[150];
  //generate room objects
  for(int i = 0; i < roomNum; i++) {
    Room *r = new Room(i);
    vect.push_back(r);
  }
  //place first room in center of board
  roomptr = vect.at(0);
  roomMap[roomptr->getID()].push_back(10);
  roomMap[roomptr->getID()].push_back(10);
  roomptr->setCoord(10, 10);
  strcpy(newName, "Closet");
  roomptr->setName(newName);
  strcpy(newDesc, "Locking someone in the closet of a haunted mansion - what a cruel prank!");
  roomptr->setDesc(newDesc);
  //Place rooms an board
  for(int i = 1; i < vect.size(); i++) {
    roomptr = vect.at(i);
    randRoom = vect.at(rand() % roomMap.size()); //Pick a random room that has been placed
    randDirection = (rand() % 4 + 1); //Pick a random direction
    //Connects the new room to randRoom using randDirection
    if(randDirection == NORTH) {
      newCoord[0] = roomMap[randRoom->getID()][0];
      newCoord[1] = roomMap[randRoom->getID()][1] - 1;
      oppositeDirection = SOUTH;
    }
    else if(randDirection == EAST) {
      newCoord[0] = roomMap[randRoom->getID()][0] + 1;
      newCoord[1] = roomMap[randRoom->getID()][1];
      oppositeDirection = WEST;
    }
    else if(randDirection == SOUTH) {
      newCoord[0] = roomMap[randRoom->getID()][0];
      newCoord[1] = roomMap[randRoom->getID()][1] + 1;
      oppositeDirection = NORTH;
    }
    else if(randDirection == WEST) {
      newCoord[0] = roomMap[randRoom->getID()][0] - 1;
      newCoord[1] = roomMap[randRoom->getID()][1];
      oppositeDirection = EAST;
    }
    //Check if newCoords are occupied, or outside map boundaries.
    if(!validnewCoord(roomMap, newCoord)) {
      i--;
    }
    else {
      roomMap[roomptr->getID()].push_back(newCoord[0]);
      roomMap[roomptr->getID()].push_back(newCoord[1]);
      roomptr->setCoord(newCoord[0], newCoord[1]);
      roomptr->setExit(oppositeDirection, randRoom);
      randRoom->setExit(randDirection, roomptr);
      //Give rooms names, items, descriptions
      if(roomptr->getID() == 1) {
	strcpy(newName, "Master Bedroom");
	roomptr->setName(newName);
	strcpy(newDesc, "There's a safe in the corner. It has two locks on it - One red, and one blue. Seems a bit excessive.");
	roomptr->setDesc(newDesc);
      }
      else if(roomptr->getID() == 2) {
	strcpy(newName, "Master Bathroom");
	roomptr->setName(newName);
	strcpy(newDesc, "The smell tells you not to check under the toilet seat.");
	roomptr->setDesc(newDesc);
      }
      else if(roomptr->getID() == 3) {
	strcpy(newName, "Hallway");
	roomptr->setName(newName);
	strcpy(newDesc, "What a ridiculous place for a hallway. It's like someone just threw this house together.");
	roomptr->setDesc(newDesc);
      }
      else if(roomptr->getID() == 4) {
	strcpy(newName, "Sitting Room");
	roomptr->setName(newName);
	strcpy(newDesc, "This place probably would've been really nice to relax in a couple decades ago.");
	roomptr->setDesc(newDesc);
	roomptr->giveItem(redKey);
      }
      else if(roomptr->getID() == 5) {
	strcpy(newName, "Small Bedroom");
	roomptr->setName(newName);
	strcpy(newDesc, "Sounds like there's a whole nest of rats under the dresser. Gross.");
	roomptr->setDesc(newDesc);
      }
      else if(roomptr->getID() == 6) {
	strcpy(newName, "Medium Bedroom");
	roomptr->setName(newName);
	strcpy(newDesc, "Old dolls and puppets line the shelves of this room. Eurgh.");
	roomptr->setDesc(newDesc);
      }
      else if(roomptr->getID() == 7) {
	strcpy(newName, "Staircase");
	roomptr->setName(newName);
	strcpy(newDesc, "You've seen enough horror movies to go really slow on these, but the steps still creak and bend a little more than what you're comfortable with.");
	roomptr->setDesc(newDesc);
      }
      else if(roomptr->getID() == 8) {
	strcpy(newName, "Cellar");
	roomptr->setName(newName);
	strcpy(newDesc, "You only dare take a couple steps into the blackness of this cellar.");
	roomptr->setDesc(newDesc);
      }
      else if(roomptr->getID() == 9) {
	strcpy(newName, "Living Room");
	roomptr->setName(newName);
	strcpy(newDesc, "A lovely room ruined by water damage. And a front door, made of rotting oak and locked with a golden padlock.");
	roomptr->setDesc(newDesc);
      }
      else if(roomptr->getID() == 10) {
	strcpy(newName, "Cleaning closet");
	roomptr->setName(newName);
	strcpy(newDesc, "A closet filled with as-seen-on-TV junk, and maybe something useful.");
	roomptr->setDesc(newDesc);
	roomptr->giveItem(rope);
      }
      else if(roomptr->getID() == 11) {
	strcpy(newName, "Kitchen");
	roomptr->setName(newName);
	strcpy(newDesc, "When you squint a bit and plug your nose, this kitchen is pretty nice! They even have marble countertops.");
	roomptr->setDesc(newDesc);
      }
      else if(roomptr->getID() == 12) {
	strcpy(newName, "Dining Room");
	roomptr->setName(newName);
	strcpy(newDesc, "This room is totally not to your liking. And it's not just because of the spider nests.");
	roomptr->setDesc(newDesc);
	roomptr->giveItem(blueKey);
      }
      else if(roomptr->getID() == 13) {
	strcpy(newName, "Balcony");
	roomptr->setName(newName);
	strcpy(newDesc, "You could totally climb down from here if you had some rope. Sweet view too.");
	roomptr->setDesc(newDesc);
      }
      else if(roomptr->getID() == 14) {
	strcpy(newName, "Garage");
	roomptr->setName(newName);
	strcpy(newDesc, "You thought the garage would be the scariest room in the house, but this place isn't that bad.");
	roomptr->setDesc(newDesc);
	roomptr->giveItem(axe);
      }
    }
  }
  updateBoard(board, vect);
}
//Check if placement coordinated from makeRooms are valid
bool validnewCoord(map<int, vector<int>> roomMap, int newCoord[2]) {
  //Check if placement is outside board boundaries
  if(newCoord[0] > 20 || newCoord[1] > 20 || newCoord[0] < 0 || newCoord[1] < 0) {
    return false;
  }
  //Check if new placement is already occupied
  for(int i = 0; i < roomMap.size(); i++) {
    if(newCoord[0] == roomMap[i][0] && newCoord[1] == roomMap[i][1]) {
      return false;
    }
  }
  return true;
}
//Update the roomBoard for printing
void updateBoard(vector<vector<int>> &roomBoard, vector<Room*> &vect) {
  int x;
  int y;
  for(int i = 0; i < vect.size(); i++) {
    if(vect.at(i)->getCoord(0) <= 20 && vect.at(i)->getCoord(1) <= 20) {
      x = vect.at(i)->getCoord(0);
      y = vect.at(i)->getCoord(1);
      roomBoard[x][y] = vect.at(i)->getID();
    }
  }
}
