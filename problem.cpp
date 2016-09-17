#include <problem.h>

Problem::Problem(){

}

QQueue<Node>& Expand(Node* current, Problem& problem){
	QQueue<Node> successors;
	for(auto Action:problem.vecOperations){
		int act=0;
		int stepCost=1; //TODO: create foo stepCost(stateOld,stateNew,action)
		State newState = Action(current,act);
		Node* s = new Node(newState,
						   current,
						   act,
						   current->getCost()+stepCost,
						   current->getDepth()+1);
		successors.insert(successors.end(),*s);
	}
	return successors;
}

Node* Tree_Search(Problem& problem, QQueue<Node> fringe){
	fringe.insert(fringe.begin(),*problem.pInitialNode);
	while(1){
		if(fringe.empty())
			return nullptr;
		Node* current = &fringe.first();
		fringe.removeFirst();
		if(problem.goalTest(current))
			return current;
		fringe.append(Expand(current, problem));	//TODO: foo pointer for
	}
}


