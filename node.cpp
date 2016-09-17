#include <node.h>

Node::Node(){
	char s[3][3] = {{'x', '2', '3'}, {'1','7','5'}, {'4', '6', '8'}};
	state = new State(s,0,0);
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
