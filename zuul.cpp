#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include "Room.h"

using namespace std;

void printBoard(int boardSize, vector<vector<int>> *board);
void makeRooms(int roomNum, vector<Room*> *vect, vector<vector<int>> &board, map<int, vector<int>> &roomMap);
void updateBoard(vector<vector<int>> &roomBoard, vector<Room*> *vect);

int main() {
  const int boardSize = 20;
  vector<vector<int>> roomBoard(boardSize, vector<int>(boardSize));
  map<int, vector<int>> roomMap;
  cout << "before empty loop" << endl;
  cout << "After empty loop" << endl;
  int roomNum = 2;
  vector<Room*> vect;
  makeRooms(roomNum, &vect, roomBoard, roomMap);
  printBoard(20, &roomBoard);
  return 0;
}

void printBoard(int boardSize, vector<vector<int>> *board) {
  for(int y = 0; y < boardSize; y++) {
    for(int x = 0; x < boardSize; x++) {
      if((*board)[x][y] != 0) {
	if((*board)[x][y] < 10) {
	  cout << "[0" << (*board)[x][y] << "]";
	}
	else {
	  cout << "[" << (*board)[x][y] << "]";
	}
      }
      else {
	cout << "[  ]";
      }
    }
    cout << endl;
  }
}

void makeRooms(int roomNum, vector<Room*> *vect, vector<vector<int>> &board, map<int, vector<int>> &roomMap) {
  int randDirection = 0;
  int randDestination = 0;
  int boardSize = 20;
  Room *roomptr;
  cout << "boardSize: " << boardSize << endl;
  //generate room objects
  for(int i = 0; i < roomNum; i++) {
    Room *r = new Room(i + 1);
    vect->push_back(r);
  }
  //place first room in center of board
  roomptr = vect->at(0);
  roomMap[roomptr->getID()].push_back(roomptr->getCoord[0]);
  roomMap[roomptr->getID()].push_back(roomptr->getCoord[1]);
  for(int i = 1; i < vect->size(); i++) {
    roomptr = vect->at(i);
    
  }
  updateBoard(board, vect);
}

void updateBoard(vector<vector<int>> &roomBoard, vector<Room*> *vect) {
  int x;
  int y;
  for(int i = 0; i < vect->size(); i++) {
    if(vect->at(i)->getCoord()[0] <= 20 && vect->at(i)->getCoord()[1] <= 20) {
      x = vect->at(i)->getCoord()[0];
      y = vect->at(i)->getCoord()[1];
      roomBoard[x][y] = vect->at(i)->getID();
      cout << "Room " << vect->at(i)->getID() << " in slot " << i << endl;
    }
  }
}
