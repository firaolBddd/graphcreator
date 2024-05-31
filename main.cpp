//Firaol Berehanu
//graph creator 5/31/24
//things i used to help me
//got help from uncle
//used stsck over flow for help with the algorthim
//used java graph creator to get an idea
//prupuosse is to create a gprah and hopfuly find the fast path


#include <iostream>
#include <cstring>
#include "node.h"

//Colors
#define RESET "\033[0m"
#define RED   "\033[31m"
#define BLUE  "\033[34m"

using namespace std;

Node* findNode(Node** nodes, char inputChar, int nodeCount);
void addNode(Node **nodes, int nodeCount);
void removeNode(Node **nodes, int nodeCount);
void addLink(Node **nodes, int nodeCount);
void removeLink(Node **nodes, int nodeCount);
void displayGraph(Node **nodes, int nodeCount);
void shortestPath(Node** nodes, int nodeCount);

int main() {
  Node **nodes = new Node*[20];
  int nodeCount = 0; //index counter
  cout << "Graph Creator; C++ Edition (No GUI)" << endl;
  bool running = true;
  char command[15];
  while (running == true) {
    cout << endl << "Options: AddNode, DelNode, AddLink, DelLink, Display, ShortestPath, Quit" << endl;
    cin.get(command, 15);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(command, "AddNode") == 0) { //Add Vertex
      addNode(nodes, nodeCount);
      nodeCount++;
    }
    else if (strcmp(command, "DelNode") == 0) { //Delete Vertex
      removeNode(nodes, nodeCount);
      nodeCount--;
    }
    else if (strcmp(command, "AddLink") == 0) { //Add Edge
      addLink(nodes, nodeCount);
    }
    else if (strcmp(command, "DelLink") == 0) { //Delete Edge
      removeLink(nodes, nodeCount);
    }
    else if (strcmp(command, "Display") == 0) { //Print
      displayGraph(nodes, nodeCount);
      cout << endl;
    }
    else if (strcmp(command, "ShortestPath") == 0) { //Shortest path algorithm, aka Dijkstra's algorithm
      cout << "Find the shortest path between two nodes using Dijkstra's algorithm." << endl;
      shortestPath(nodes, nodeCount);
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


Node* findNode(Node** nodes, char inputChar, int nodeCount) { //Find Node, used for Removing Nodes, Adding and Removing links
  int i = 0;
  while (i < nodeCount) {
    if ((nodes[i])->getName() == inputChar) {
      return (nodes[i]);
    }
    else {
      i++;
    }
  }
  return NULL;
}

void addNode(Node **nodes, int nodeCount) { //Add Node, adds a user inputted node
  //New node object
  Node* newNode = new Node();
  newNode->setIndex(nodeCount);
  char inputChar;
  cout << "Character for new node >> ";
  cin >> inputChar;
  cin.clear();
  cin.ignore(10000, '\n');
  //Assign input value to object
  newNode->setName(inputChar);
  //Add node to list
  nodes[nodeCount] = newNode;
  cout << endl << "Node " << newNode->getName() << " added." << endl;
}

void removeNode(Node **nodes, int nodeCount) { //Remove Node, deletes a user inputted node
  if (nodes[0] == NULL) {
    cout << endl << "No nodes to delete, add some first." << endl;
    return;
  }
  char inputChar;
  cout << "Node to be deleted >> ";
  cin >> inputChar;
  cin.clear();
  cin.ignore(10000, '\n');
  Node* n = findNode(nodes, inputChar, nodeCount);
  if (n == NULL) {
    cout << endl << "No node found. Try again." << endl;
    return;
  }
  int i = n->getIndex();
  n->~Node(); //Remove data from node
  cout << "Node at index " << i << " removed." << endl;
  //Redo link list for every node
  for (int r = 0; r < nodeCount; r++) {
    Node* current = nodes[r];
    for (int currLink = i; currLink < nodeCount; currLink++) {
      if (currLink == nodeCount - 1) {
	      current->setLink(currLink, 0);
      }
      else {
	//Move all links above removed index down by 1 index
	int next = currLink + 1;
	current->setLink(currLink, current->getLink(next));
      }
    }
    nodes[r] = current;
  }
  //Remove index from list
  nodes[i] = NULL;
  //move all elements that follow down by 1 index
  while (i < nodeCount) {
    if (i == nodeCount - 1) {
      nodes[i] = NULL;
      break;
    }
    nodes[i] = nodes[i + 1];
    (nodes[i])->setIndex(i);
    i++;
  }
  cout << endl << "Node deleted." << endl;
}

void displayGraph(Node **nodes, int nodeCount) { //Display, prints out adjacency matrix
  char display[21][21];  //[row][col]
  //initialize empty matrix
  for (int r = 0; r < 21; r++) {
    for (int c = 0; c < 21; c++) {
      display[r][c] = ' ';
    }
  }
  int linkDisplay[20][20];
  int count = 0;
  //construct adjacency matrix visual
  //first row and column
  while (count < nodeCount) {
    display[0][count+1] = (nodes[count])->getName();
    display[count+1][0] = (nodes[count])->getName();
    count++;
  }
  //create link display list
  for (int r = 0; r < nodeCount; r++) {
    Node* n = nodes[r];
    for (int c = 0; c < nodeCount; c++) {
      Node* nr = nodes[c];
      if (n->getLink(nr->getIndex()) != 0) {
	      linkDisplay[r][c] = 'T';
      } 
      else {
	      linkDisplay[r][c] = 'F';
      }
    }
  }
  //place link matrix in display array
  for (int r = 0; r < nodeCount; r++) {
    for (int c = 0; c < nodeCount; c++) {
      display[r+1][c+1] = linkDisplay[r][c];
    }
  }
  //display adjacency matrix
  for (int r = 0; r < 21; r++) {
    for (int c = 0; c < 21; c++) {
      if (display[r][c] == 'T' && c != 0 && r != 0) {
	      cout << BLUE << display[r][c] << RESET << '\t';
      }  
      else if (display[r][c] == 'F' && c != 0 && r != 0) {
	      cout << RED << display[r][c] << RESET << '\t';
      } 
      else {
      	cout << display[r][c] << '\t';
      }
    }
    cout << endl;
    if (display[r+1][0] == ' ') break;
  }
}

void addLink(Node **nodes, int nodeCount) { //Add Link, add a link between two given nodes
  if(nodes[0] == NULL || nodes[1] == NULL) {
    //Need at least two nodes
    cout << endl << "Have at least two nodes first." << endl;
    return;
  }
  char input1, input2;
  cout << endl << "Which two nodes is this link being added to?" << endl;
  cout << "Node 1 >> ";
  cin >> input1;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "Node 2 >> ";
  cin >> input2;
  cin.clear();
  cin.ignore(10000, '\n');
  Node* n1 = findNode(nodes, input1, nodeCount);
  Node* n2 = findNode(nodes, input2, nodeCount);
  if (n1 == NULL || n2 == NULL) {
    cout << endl << "Nodes couldn't be located. Try again." << endl;
    return;
  }
  //Assign link value
  cout << "Link value >> ";
  int val;
  cin >> val;
  cin.clear();
  cin.ignore(10000, '\n');
  n1->setLink(n2->getIndex(), val);
  n2->setLink(n1->getIndex(), val);
}

void removeLink(Node **nodes, int nodeCount) { //Remove Link, delete a link between two given nodes
  if(nodes[0] == NULL || nodes[1] == NULL) {
    //Need at least two nodes
    cout << endl << "Have at least two nodes first." << endl;
    return;
  }
  char input1, input2;
  cout << "What nodes are connected by this link?" << endl;
  cout << "Node 1 >> ";
  cin >> input1;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "Node 2 >> ";
  cin >> input2;
  cin.clear();
  cin.ignore(10000, '\n');
  Node* n1 = findNode(nodes, input1, nodeCount);
  Node* n2 = findNode(nodes, input2, nodeCount);
  if (n1 == NULL || n2 == NULL) {
    cout << endl << "Nodes couldn't be located. Try again." << endl;
    return;
  }
  n1->setLink(n2->getIndex(), 0);
  n2->setLink(n1->getIndex(), 0);
  cout << "Link deleted." << endl;
}

void shortestPath(Node** nodes, int nodeCount) { //Shortest path, Dijkstra's algorithm
  if (nodes[0] == NULL || nodes[1] == NULL) {
    //Need at least two nodes
    cout << endl << "Have at least two nodes first." << endl;
    return;
  }
  char input1, input2;
  cout << "Starting Node >> ";
  cin >> input1;
  cin.clear();
  cin.ignore(10000, '\n');
  cout << "Ending Node >> ";
  cin >> input2;
  cin.clear();
  cin.ignore(10000, '\n');
  Node* start = findNode(nodes, input1, nodeCount);
  Node* end = findNode(nodes, input2, nodeCount);
  if (start == NULL || end == NULL) {
    cout << endl << "Nodes couldn't be located. Try again." << endl;
    return;
  }
	else {
    int max = nodeCount;
    int n = nodeCount;
    int INFINITY = 999; //Assuming 999 as Infinity value
    int startNode = start->getIndex();
    int destNode = end->getIndex();
    int cost[max][max],distance[max],pred[max];
    int visited[max],count,mindistance,nextnode,i,j,y,z;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){ 
            if(nodes[i]->getLink(j) == 0){
                cost[i][j] = INFINITY;
            }
            else{
                cost[i][j] = nodes[i]->getLink(j);
            }
        }
     }   

    // Main functionality (Algorithm)
   for(i = 0; i < n; i++) {
      distance[i] = cost[startNode][i];
      pred[i] = startNode;
      visited[i] = 0;
   }
   distance[startNode] = 0;
   visited[startNode] = 1;
   count = 1;
   while(count < n-1) {
      mindistance = INFINITY;
      for(i = 0; i < n; i++)
         if(distance[i] < mindistance && !visited[i]) {
         mindistance = distance[i];
         nextnode = i;
      }
      visited[nextnode] = 1;
      for(i = 0; i < n; i++)
         if(!visited[i])
      if(mindistance+cost[nextnode][i] < distance[i]) {
         distance[i] = mindistance+cost[nextnode][i];
         pred[i] = nextnode;
      }
      count++;
   }
    // Printing the shortest path along with the cost
   for(i = 0; i < n; i++) {
   if(i == destNode) {
      cout << "\nDistance/Cost: " << distance[i];
      cout << "\nPath: " << nodes[i]->getName();
      j = i;
      do {
         j = pred[j];
         cout << "<-" << nodes[j]->getName();
      }
      while(j != startNode);
    }
   }
  }
}

