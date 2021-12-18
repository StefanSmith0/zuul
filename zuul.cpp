#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <time.h>
#include "Room.h"

using namespace std;

void printBoard(int boardSize, vector<vector<int>> &board);
void makeRooms(int roomNum, vector<Room*> &vect, vector<vector<int>> &board, map<int, vector<int>> &roomMap);
void updateBoard(vector<vector<int>> &roomBoard, vector<Room*> &vect);
bool validnewCoord(map<int, vector<int>> roomMap, int newCoord[2]);

const int NORTH = 1;
const int EAST = 2;
const int SOUTH = 3;
const int WEST = 4;

int main() {
  srand(time(0));
  const int boardSize = 20;
  vector<vector<int>> roomBoard(boardSize, vector<int>(boardSize));
  map<int, vector<int>> roomMap;
  int roomNum = 15;
  vector<Room*> vect;
  makeRooms(roomNum, vect, roomBoard, roomMap);
  printBoard(20, roomBoard);
  //Main play loop
  bool running = true;
  char input[20];
  while(running) {
    cout << "Enter command: ";
    cin.getline(input, 20);
    if(!strcmp(input, "MOVE")) {
      
    }
  }
  return 0;
}

void printBoard(int boardSize, vector<vector<int>> &board) {
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
      if(x == 10 && y == 10) {
	cout << "[00]";
      }
      else {
	if(board[x][y] != 0) {
	  if(board[x][y] < 10) {
	    cout << "[0" << board[x][y] << "]";
	  }
	  else {
	    cout << "[" << board[x][y] << "]";
	  }
	}
	else {
	  cout << "[  ]";
	}
      }
    }
    cout << endl;
  }
}

void makeRooms(int roomNum, vector<Room*> &vect, vector<vector<int>> &board, map<int, vector<int>> &roomMap) {
  int randDirection = 0;
  int randRoom = 0;
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
    randRoom = (rand() % roomMap.size());
    cout << "Random Room: " << randRoom << endl;
    randDirection = (rand() % 4 + 1);
    cout << "Random Direction: " << randDirection << endl;
    if(randDirection == NORTH) {
      newCoord[0] = roomMap[randRoom][0];
      newCoord[1] = roomMap[randRoom][1] - 1;
    }
    else if(randDirection == EAST) {
      newCoord[0] = roomMap[randRoom][0] + 1;
      newCoord[1] = roomMap[randRoom][1];
    }
    else if(randDirection == SOUTH) {
      newCoord[0] = roomMap[randRoom][0];
      newCoord[1] = roomMap[randRoom][1] + 1;
    }
    else if(randDirection == WEST) {
      newCoord[0] = roomMap[randRoom][0] - 1;
      newCoord[1] = roomMap[randRoom][1];
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
      cout << "Room " << vect.at(i)->getID() << " in slot " << i << endl;
    }
  }
}
