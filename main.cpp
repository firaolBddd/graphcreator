#include <iostream>
#include <cstring>
#include "vertex.h"

//Colors
#define RESET "\033[0m"
#define RED   "\033[31m"
#define BLUE  "\033[34m"

using namespace std;

Vertex* findVertex(Vertex** list, char in, int IC);
void addVertex(Vertex **list, int IC);
void removeVertex(Vertex **list, int IC);
void addEdge(Vertex **list, int IC);
void removeEdge(Vertex **list, int IC);
void PRINT(Vertex **list, int IC);
void fastPath(Vertex** list, int IC);

int main() {
  Vertex **list = new Vertex*[20];
  int IC = 0; //index counter
  cout << "Graph Creator; C++ Edition (No GUI)" << endl;
  bool running = true;
  char command[15];
  while (running == true) {
    cout << endl << "Options: AddVer, DelVer, AddEdge, DelEdge, Print, Fpath, Quit" << endl;
    cin.get(command, 15);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(command, "AddVer") == 0) { //Add Vertex
      addVertex(list, IC);
      IC++;
    }
    else if (strcmp(command, "DelVer") == 0) { //Delete Vertex
      removeVertex(list, IC);
      IC--;
    }
    else if (strcmp(command, "AddEdge") == 0) { //Add Edge
      addEdge(list, IC);
    }
    else if (strcmp(command, "DelEdge") == 0) { //Delete Edge
      removeEdge(list, IC);
    }
    else if (strcmp(command, "Print") == 0) { //Print
      PRINT(list, IC);
      cout << endl;
    }
    else if (strcmp(command, "Fpath") == 0) { //Shortest path algorithm, aka Dijkstra's algorithm
      cout << "Find the fastest path between two vertexs using Dijkstra's algorithm." << endl;
      fastPath(list, IC);
    }
    else if (strcmp(command, "Quit") == 0) { //Quit
      cout << endl << "Quitting Graph Creator" << endl;
      running = false;
    }
    else {
      cout << "Invalid input, try again." << endl << endl;
    }
  }
}

