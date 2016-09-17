#include <node.h>

Node::Node(){
	char s[3][3] = {{'7', '4', '2'}, {'3','4','8'}, {'6', 'x', '1'}};
	state = State((char**)s,(int)0x21);
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
