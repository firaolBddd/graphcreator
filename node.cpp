//this is the node.cpp files 
//all the prottypes and what not 

#include <iostream>
#include "node.h"

using namespace std;

Node::Node() {
  //Constructor
  nodeName = '\0';
  int i = 0;
  while (i < 20) {
    links[i] = 0;
    i++;
  }
}

Node::~Node() {
  //Destructor
  nodeName = '\0';
  nodeIndex = 0;
  int j = 0;
  while (j < 20) {
    links[j] = 0;
    j++;
  }
}

//Getters
char Node::getName() {
  return nodeName;
}

int Node::getIndex() {
  return nodeIndex;
}

int Node::getLink(int fromIndex) {
  return links[fromIndex];
}

//Setters
void Node::setName(char newName) {
  nodeName = newName;
}

void Node::setIndex(int newIndex) {
  nodeIndex = newIndex;
}

void Node::setLink(int fromIndex, int value) {
  links[fromIndex] = value;
}

