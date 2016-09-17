#include <problem.h>

Problem::Problem(){

}

Problem::Problem(QVector<State (*)(Node*, int&)> op, bool (*goalTestFunc)(Node*),int (*pathCostFunc)()){
	pInitialNode = new Node();
	char s[3][3] = {{'1', '2', '3'}, {'4','x','5'}, {'6', '7', '8'}};
	targetState = State((char**)s,(int)0x11);

	vecOperations.append(op);
	goalTest = goalTestFunc;
	pathCost = pathCostFunc;
}

QQueue<Node>& Expand(Node* current, Problem& problem){
	QQueue<Node>* successors = new QQueue<Node>();
	for(auto Action:problem.vecOperations){
		int act=0;
		int stepCost=1; //TODO: create foo stepCost(stateOld,stateNew,action)
		State newState = Action(current,act);
		Node* s = new Node(newState,
						   current,
						   act,
						   current->getCost()+stepCost,
						   current->getDepth()+1);
		successors->insert(successors->end(),*s);
	}
	return *successors;
}

Node* Tree_Search(Problem& problem, QQueue<Node> fringe){
	fringe.insert(fringe.begin(),*problem.pInitialNode);
	while(1){
		if(fringe.empty())
			return nullptr;
		Node* current = &fringe.first();
		fringe.removeFirst();
		if(problem.goalTest(current))
			return current;	//TODO: return solution - queue of nodes contains path
		fringe.append(Expand(current, problem));
	}
}
