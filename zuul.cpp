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

int main() {
  srand(time(0));
  const int boardSize = 20;
  vector<vector<int>> roomBoard(boardSize, vector<int>(boardSize));
  map<int, vector<int>> roomMap;
  cout << "before empty loop" << endl;
  cout << "After empty loop" << endl;
  int roomNum = 4;
  vector<Room*> vect;
  makeRooms(roomNum, vect, roomBoard, roomMap);
  printBoard(20, roomBoard);
  return 0;
}

void printBoard(int boardSize, vector<vector<int>> &board) {
  for(int y = 0; y < boardSize; y++) {
    if(y < 10) {
      cout << y << "  "; //Two spaces
    }
    else {
      cout << y << " "; //One space
    }
    for(int x = 0; x < boardSize; x++) {
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
    Room *r = new Room(i + 1);
    vect.push_back(r);
  }
  //place first room in center of board
  roomptr = vect.at(0);
  roomMap[roomptr->getID()].push_back(10);
  roomMap[roomptr->getID()].push_back(10);
  roomptr->setCoord(10, 10);
  for(int i = 1; i < vect.size(); i++) {
    roomptr = vect.at(i);
    randRoom = (rand() % vect.size());
    randDirection = (rand() % 4 + 1);
    cout << "Random Direction: " << randDirection << endl;
    if(randDirection == 1) { //North
      newCoord[0] = roomMap[i][0];
      newCoord[1] = roomMap[i][1] - 1;
    }
    else if(randDirection == 2) { //East
      newCoord[0] = roomMap[i][0] + 1;
      newCoord[1] = roomMap[i][1];
    }
    else if(randDirection == 3) { //South
      newCoord[0] = roomMap[i][0];
      newCoord[1] = roomMap[i][1] + 1;
    }
    else if(randDirection == 4) { //West
      newCoord[0] = roomMap[i][0] - 1;
      newCoord[1] = roomMap[i][1];
    }
    //Check if newCoords are occupied, or outside map boundaries.
    if(validnewCoord(roomMap, newCoord)) {
      cout << "Valid placement at: " << "(" << newCoord[0] << "," << newCoord[1] << ")" << endl;
      roomMap[roomptr->getID()].push_back(newCoord[0]);
      roomMap[roomptr->getID()].push_back(newCoord[1]);
      roomptr->setCoord(newCoord[0], newCoord[1]);
    }
    else {
      cout << "Invalid placement at: " << "(" << newCoord[0] << "," << newCoord[1] << ")" << endl;
    }
  }
  updateBoard(board, vect);
}

bool validnewCoord(map<int, vector<int>> roomMap, int newCoord[2]) {
  if(newCoord[0] > 20 || newCoord[1] > 20) {
    if(newCoord[0] < 0 || newCoord[1] < 0) {
      return false;
      cout << "Invalid placement: Outside board bounds." << endl;
    }
  }
  for(int i = 1; i < roomMap.size(); i++) {
    if(newCoord[0] == roomMap[i][0] && newCoord[1] == roomMap[i][0]) {
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
