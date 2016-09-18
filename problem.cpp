#include <problem.h>

Problem::Problem(){
	pInitialNode = new Node();
	targetState = new State();
	goalTest = nullptr;
	pathCost =nullptr;
}

Problem::Problem(QVector<State* (*)(Node*, int&)> op, bool (*goalTestFunc)(Node*,State*),int (*pathCostFunc)(),int Depth){
	iMaxDepth = Depth;
	pInitialNode = new Node();
	targetState = new State(0x12345678,4);  //123|4x5|678

	vecOperations.append(op);
	goalTest = goalTestFunc;
	pathCost = pathCostFunc;
}

QQueue<Node*>* Expand(Node* current, Problem& problem, QTextEdit* TextEdit){
	QQueue<Node*>* successors = new QQueue<Node*>();
	if(current->getDepth()>problem.getMaxDepth()) return successors;
	QString str = "S"+QString::number(current->getDepth()+1)+": ";
	for(auto Action:problem.vecOperations){
		int act=0;
		int stepCost=1; //TODO: create foo stepCost(stateOld,stateNew,action)
		State* newState = Action(current,act);
		if(newState != nullptr){
			Node* s = new Node(newState,
							   current,
							   act,
							   current->getCost()+stepCost,
							   current->getDepth()+1);
			successors->insert(successors->end(),s);
			str.append(" " + s->getState()->toString());
		}
	}
	TextEdit->append(str);
	return successors;
}

extern void refreshEvents();

Node* Tree_Search(Problem& problem, QQueue<Node*>& fringe, QTextEdit* TextEdit){
	fringe.insert(fringe.begin(),problem.pInitialNode);
	while(1){
		if(fringe.empty())
			return nullptr;
		Node* current = fringe.first();

		TextEdit->append("C"+QString::number(current->getDepth())+": "+current->getState()->toString());
		fringe.removeFirst();
		if(problem.goalTest(current, problem.targetState))
			return current;	//TODO: return solution - queue of nodes contains path
		QQueue<Node*>* successors = Expand(current, problem, TextEdit);
		for(Node* s:*successors){
			for(auto f:fringe){
				if(problem.goalTest(s,f->getState()))
					delete s;
					successors->removeOne(s);
			}
		}
		fringe.append(*successors);
		delete successors;
		refreshEvents();
	}
}
