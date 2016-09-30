#include <problem.h>
#include <QFile>
#include <QTextStream>
extern bool writeLog;

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

	for(auto Action:*problem->vecOperations){
		int act=0;
		int stepCost = 1; //TODO: create foo stepCost(stateOld,stateNew,action)
		State* newState = Action(current,act);
		if(newState != nullptr){
			Node* s = new Node(newState, current, act,
							   current->getCost()+stepCost,
							   current->getDepth()+1);
			successors->insert(successors->end(),s);
		}
	}

	return successors;
}

extern void refreshEvents();

Node* Tree_Search(Problem* problem, QHash<QString,Node*> *visitedNodes, QQueue<Node*>* fringe, QTextEdit* TextEdit){
	Node* startNode = new Node(new State(
								   problem->pInitialNode->getState()->iState,
								   problem->pInitialNode->getState()->iXPos
								   ), nullptr,-1,
							   problem->pInitialNode->getCost(),problem->pInitialNode->getDepth());
	fringe->insert(fringe->begin(),startNode); //включаем начальный узел в очередь
	visitedNodes->insert(startNode->getState()->getHash(),startNode);


	QFile file("out.txt");
	 if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		 return nullptr;
	QTextStream out(&file);

	while(1){
		if(fringe->empty())
			return nullptr;	//если очередь пуста выходим
		Node* current = fringe->first();fringe->pop_front();  //вынимаем первый элемент очереди
			//посетили первую ноду

		if(writeLog)
			TextEdit->append("C"+QString::number(current->getDepth())+": "+current->getState()->toString());
		out << "C" << current->getDepth() << ": " + current->getState()->toString()<< "\n";
		out << "N: " << visitedNodes->size() << " Q: " << fringe->size() << "\n";
		if(problem->goalTest(current->getState(), problem->targetState))  //проверяем на совпадение с целевым
			return current;	//TODO: return solution - queue of nodes contains path

		QList<Node*>* successors = Expand(current, problem, TextEdit); //раскрываем листья
		//проверяем на нахождение листьев в очереди
		QString str;
		//if(writeLog)
			str = "S"+QString::number(current->getDepth()+1)+":";
		for(Node* s:*successors){
			QString hash = s->getState()->getHash(); //получаем хэш ноды
			if(visitedNodes->find(hash) == visitedNodes->end()){	//если нет в посещенных
				visitedNodes->insert(hash,s);			//добавляем в посещенные
				fringe->append(s);						//добавляем в кромку
				//if(writeLog)
					str.append(" " + s->getState()->toString());
			}else {
				delete s;
			}
		}
		if(writeLog)
			TextEdit->append(str);
		out << str << "\n";
		successors->clear();
		delete successors;
		refreshEvents();
	}
}

QList<Node>* SolveProblem(Problem* problem,QQueue<Node*> fringe,QTextEdit* logWiget,int type){

	QList<Node>* solution;
	return solution;
}
