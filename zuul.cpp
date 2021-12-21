#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <time.h>
#include "Room.h"

using namespace std;

void printBoard(int boardSize, vector<vector<int>> &board, Room* currentRoom);
void makeRooms(int roomNum, vector<Room*> &vect, vector<vector<int>> &board, map<int, vector<int>> &roomMap,
	       Item goldKey);
void updateBoard(vector<vector<int>> &roomBoard, vector<Room*> &vect);
bool validnewCoord(map<int, vector<int>> roomMap, int newCoord[2]);
void parseCommand(char input[], vector<vector<int>> &roomBoard, vector<Room*> &vect,
		  map<int, vector<int>> roomMap, Room *currentRoom, vector<Item> &inventory); 
Room* moveToRoom(Room* currentRoom, vector<Room*> &vect);
void printRoomDetails(Room* currentRoom);

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
  strcpy(newDesc, "A beautiful, golden key. It might be a ticket out of here.");
  Item goldKey(newID, newName, newDesc);
  
  newID = 2;
  strcpy(newName, "redKey");
  strcpy(newDesc, "A key which appears red, hopefully not due to rust.");
  Item redKey(newID, newName, newDesc);
  
  newID = 3;
  strcpy(newName, "yellowKey");
  strcpy(newDesc, "A yellow-ish key. Not the pretty type.");
  Item yellowKey(newID, newName, newDesc);
  
  newID = 4;
  strcpy(newName, "blueKey");
  strcpy(newDesc, "A blue key. It's a good thing they color-coded these.");
  Item blueKey(newID, newName, newDesc);
  
  newID = 5;
  strcpy(newName, "ram");
  strcpy(newDesc, "One of those battering rams SWAT teams use.");
  Item ram(newID, newName, newDesc);

  vector<vector<int>> roomBoard(boardSize, vector<int>(boardSize));
  map<int, vector<int>> roomMap;
  vector<Item> inventory;
  int roomNum = 15;
  vector<Room*> vect;
  makeRooms(roomNum, vect, roomBoard, roomMap, goldKey);
  //Main play loop
  bool running = true;
  char input[20];
  Room *currentRoom = vect[0];
  printBoard(boardSize, roomBoard, currentRoom);
  while(running) {
    printRoomDetails(currentRoom);
    cout << "Enter command: ";
    cin.getline(input, 20);
    if(!strcmp(input, "QUIT")) {
      running = false;
    }
    else {
      parseCommand(input, roomBoard, vect, roomMap, currentRoom, inventory);
      updateBoard(roomBoard, vect);
      printBoard(boardSize, roomBoard, currentRoom);
    }
  }
  return 0;
}

void printRoomDetails(Room* currentRoom) {
  map<int, Room*> localMap(currentRoom->getExit());
  cout << "You are in room: " << currentRoom->getID() << endl;
  cout << "At (" << currentRoom->getCoord()[0] << "," << currentRoom->getCoord()[1] << ")" << endl;
  cout << "Exits: ";
  map<int, Room*>::iterator it;
  for(it = localMap.begin(); it != localMap.end(); it++) {
    if(it->first == NORTH) {
      cout << "North, ";
    }
    else if(it->first == EAST) {
      cout << "East, ";
    }
    else if(it->first == SOUTH) {
      cout << "South, ";
    }
    else {
      cout << "West, ";
    }
    cout << "Room " << it->second->getID() << "   ";
  }
  cout << endl;
  if(currentRoom->getInventorySize() > 0) {
    cout << "Items: " << endl;
    for(int i = 0; i < currentRoom->getInventorySize(); i++) {
      cout << currentRoom->getItem(i).getName() << " - " << currentRoom->getItem(i).getDesc() << endl;
    }
  }
}

void parseCommand(char input[], vector<vector<int>> &roomBoard, vector<Room*> &vect,
		  map<int, vector<int>> roomMap, Room *currentRoom, vector<Item> &playerInventory) {
  if(!strcmp(input, "MOVE")) {
    *currentRoom = *moveToRoom(currentRoom, vect);
  }
  else if(!strcmp(input, "GRAB")) {
    if(currentRoom->getInventorySize() > 0) {
      cout << "Grab: " << endl;
      cin.getline(input, 20);
      for(int i = 0; i < currentRoom->getInventorySize(); i++) {
	if(!strcmp(input, currentRoom->getItem(i).getName())) {
	  int localID = currentRoom->getItem(i).getID();
	  playerInventory.push_back(currentRoom->takeItem(localID));
	  cout << playerInventory.back().getName() << " picked up" << endl;
	}
      }
    }
    else {
      cout << "There's nothing to grab!" << endl;
    }
  }
  else if(!strcmp(input, "DROP")) {

  }
  else if(!strcmp(input, "BAG")) {
    for(int i = 0; i < playerInventory.size(); i++) {
      cout << playerInventory[i].getName() << " - " << playerInventory[i].getDesc() << endl;
    }
  }
  else {
    cout << "Command not recognized." << endl;
  }
}

Room* moveToRoom(Room* currentRoom, vector<Room*> &vect) {
  char input[20];
  cout << "Direction: ";
  cin.getline(input, 20);
  Room* outRoom = currentRoom;
  int moveCoord[2];
  if(!strcmp(input, "NORTH")) {
    moveCoord[0] = currentRoom->getCoord()[0];
    moveCoord[1] = currentRoom->getCoord()[1] - 1;
  }
  else if(!strcmp(input, "EAST")) {
    moveCoord[0] = currentRoom->getCoord()[0] + 1;
    moveCoord[1] = currentRoom->getCoord()[1];
  }
  else if(!strcmp(input, "SOUTH")) {
    moveCoord[0] = currentRoom->getCoord()[0];
    moveCoord[1] = currentRoom->getCoord()[1] + 1;
  }
  else if(!strcmp(input, "WEST")) {
    moveCoord[0] = currentRoom->getCoord()[0] - 1;
    moveCoord[1] = currentRoom->getCoord()[1];
  }
  else {
    cout << "Direction not recognized. (NORTH, EAST, SOUTH, WEST)" << endl;
  }
  for(int i = 0; i < vect.size(); i++) {
    if(moveCoord[0] == vect[i]->getCoord()[0] && moveCoord[1] == vect[i]->getCoord()[1]) {
      outRoom = vect[i];
      cout << "Current room is now: " << outRoom->getID() << endl;
      return outRoom;
    }
  }
  cout << "There is no room there!" << endl;
  return currentRoom;
}

void printBoard(int boardSize, vector<vector<int>> &board, Room* currentRoom) {
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
      if(board[x][y] != 0) {
	if(x == currentRoom->getCoord()[0] && y == currentRoom->getCoord()[1]) {
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
	       Item goldKey) {
  int randDirection = 0;
  int oppositeDirection = 0;
  Room* randRoom;
  int boardSize = 20;
  Room *roomptr;
  int newCoord[2];
  cout << "boardSize: " << boardSize << endl;
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
  cout << "Vector size: " << vect.size() << " (Should be " << roomNum << ")" << endl;
  for(int i = 1; i < vect.size(); i++) {
    roomptr = vect.at(i);
    randRoom = vect.at(rand() % roomMap.size());
    cout << "Random Room: " << randRoom << endl;
    randDirection = (rand() % 4 + 1);
    cout << "Random Direction: " << randDirection << endl;
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
    cout << "newCoords set" << endl;
    //Check if newCoords are occupied, or outside map boundaries.
    if(!validnewCoord(roomMap, newCoord)) {
      cout << "Invalid placement at: " << "(" << newCoord[0] << "," << newCoord[1] << ")" << endl;
      i--;
    }
    else {
      cout << "Valid placement at: " << "(" << newCoord[0] << "," << newCoord[1] << ")" << endl;
      roomMap[roomptr->getID()].push_back(newCoord[0]);
      roomMap[roomptr->getID()].push_back(newCoord[1]);
      roomptr->setCoord(newCoord[0], newCoord[1]);
      roomptr->setExit(oppositeDirection, randRoom);
      randRoom->setExit(randDirection, roomptr);
      if(roomptr->getID() == 1) {
	roomptr->giveItem(goldKey);
      }
    }
  }
  updateBoard(board, vect);
}

bool validnewCoord(map<int, vector<int>> roomMap, int newCoord[2]) {
  if(newCoord[0] > 20 || newCoord[1] > 20 || newCoord[0] < 0 || newCoord[1] < 0) {
    return false;
    cout << "Invalid placement: Outside board bounds." << endl;
  }
  for(int i = 0; i < roomMap.size(); i++) {
    if(newCoord[0] == roomMap[i][0] && newCoord[1] == roomMap[i][1]) {
      cout << "Invalid placement: Space already occupied." << endl;
      return false;
    }
  }
  return true;
}

void updateBoard(vector<vector<int>> &roomBoard, vector<Room*> &vect) {
  int x;
  int y;
  for(int i = 0; i < vect.size(); i++) {
    if(vect.at(i)->getCoord()[0] <= 20 && vect.at(i)->getCoord()[1] <= 20) {
      x = vect.at(i)->getCoord()[0];
      y = vect.at(i)->getCoord()[1];
      roomBoard[x][y] = vect.at(i)->getID();
    }
  }
}
