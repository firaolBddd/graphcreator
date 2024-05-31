//this is the node.h file for the graph creator with all the 
//getter and seeter and varbiles naems
#ifndef NODE_H
#define NODE_H

using namespace std;

class Node {
 public:
  Node();
  ~Node();
  //Getters
  char getName();
  int getIndex();
  int getLink(int);
  //Setters
  void setName(char);
  void setIndex(int);
  void setLink(int, int);
//dont forget to make private ones
 private:
  char nodeName;
  int nodeIndex;
  int links[20];
};
#endif

