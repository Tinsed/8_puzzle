#include <problem.h>

Problem::Problem(){
	pInitialNode = new Node();
	targetState = new State();
	goalTest = nullptr;
	pathCost =nullptr;
}

Problem::Problem(QVector<State* (*)(Node*, int&)>* op, bool (*goalTestFunc)(State*,State*),int (*pathCostFunc)(),int Depth){
	iMaxDepth = Depth;
	pInitialNode = new Node();
	targetState = new State(0x12345678,4);  //123|4x5|678

	vecOperations=op;
	goalTest = goalTestFunc;
	pathCost = pathCostFunc;
}

Problem::~Problem(){
	delete pInitialNode;
	delete targetState;
}

QList<Node*>* Expand(Node* current, Problem* problem, QTextEdit* TextEdit){
	QList<Node*>* successors = new QList<Node*>();
	if(current->getDepth()>=problem->getMaxDepth())
		return successors;

	QString str = "S"+QString::number(current->getDepth()+1)+": ";

	for(auto Action:*problem->vecOperations){
		int act=0;
		int stepCost = 1; //TODO: create foo stepCost(stateOld,stateNew,action)
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

Node* Tree_Search(Problem* problem, QQueue<Node*>* fringe, QTextEdit* TextEdit){
	fringe->insert(fringe->begin(),problem->pInitialNode); //включаем начальный узел в очередь
	while(1){
		if(fringe->empty())	//если очередь пуста выходим
			return nullptr;
		Node* current = fringe->first();fringe->pop_front();  //вынимаем первый элемент очереди

		TextEdit->append("C"+QString::number(current->getDepth())+": "+current->getState()->toString());

		if(problem->goalTest(current->getState(), problem->targetState))  //проверяем на совпадение с целевым
			return current;	//TODO: return solution - queue of nodes contains path

		QList<Node*>* successors = Expand(current, problem, TextEdit); //раскрываем листья
		//проверяем на нахождение листьев в очереди
		for(auto f:*fringe){
			for(Node* s:*successors){
				if(problem->goalTest(s->getState(),f->getState())){
					successors->removeOne(s);
					delete s;
				}
			}
		}

		if(!(successors->empty()))
			fringe->append(*successors);
		delete successors;
		refreshEvents();
	}
}
