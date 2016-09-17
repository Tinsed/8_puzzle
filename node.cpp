#include <node.h>

Node::Node(){
	//state.State({{7, 4, 2}, {3, 4, 8}, {6, x, 1}},0x21);
	pParentNode = nullptr;
	iAction = NUF;
	iPathCost = 0;
	iDepth =0;
}

Node::Node(State s, Node* parrent, int act, int cost, int depth){
	state = s;
	pParentNode = parrent;
	iAction = act;
	iPathCost = cost;
	iDepth = depth;
}
