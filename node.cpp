#include <node.h>

Node::Node(){
	state = new State(0x23175468,8);
	pParentNode = nullptr;
	iAction = -1;
	iPathCost = 0;
	iDepth =0;
}

Node::Node(State* s, Node* parrent, int act, int cost, int depth){
	state = s;
	pParentNode = parrent;
	iAction = act;
	iPathCost = cost;
	iDepth = depth;
}
Node::~Node(){
	if(state!=nullptr)
		delete state;
	pParentNode = nullptr;
}

