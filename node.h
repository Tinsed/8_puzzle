#ifndef NODE_H
#define NODE_H


#include <state.h>

class Node{
	State* state;
	Node* pParentNode;
	int iAction;
	int iPathCost;		//Path cost from 0-node to current
	int iDepth;		//Depth, number of stages of path
public:
	Node();
	Node(State*, Node*, int, int, int);
	~Node();

	int getAction() {return iAction;}
	State* getState(){return state;}
	State* setState(unsigned int s, int p){
		state->iState=s;
		state->iXPos=p;
	}
	Node* getParentNode(){return pParentNode;}
	int getCost() {return iPathCost;}
	int getDepth() {return iDepth;}
};

#endif // NODE_H
