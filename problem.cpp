#include <problem.h>
#include <QFile>
#include <QTextStream>
#include <QTime>
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

QList<Node*>* Expand(Node* current, Problem* problem){
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

Node* Tree_Search_BFS(Problem* problem, QHash<int,Node*> *visitedNodes, QQueue<Node*>* fringe){
	Node* startNode = new Node(new State(
								   problem->pInitialNode->getState()->iState,
								   problem->pInitialNode->getState()->iXPos
								   ), nullptr,-1,
							   problem->pInitialNode->getCost(),problem->pInitialNode->getDepth());
	fringe->insert(fringe->begin(),startNode); //включаем начальный узел в очередь
	visitedNodes->insert(startNode->getState()->getHashI(),startNode);

	QFile file("out.txt");
	 if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		 return nullptr;
	QTextStream out(&file);

	while(1){
		if(fringe->empty())
			return nullptr;	//если очередь пуста выходим
		Node* current = fringe->first();fringe->pop_front();  //вынимаем первый элемент очереди
			//посетили первую ноду

		if(writeLog){
			out << "C" << current->getDepth() << ": " + current->getState()->toString()<< "\n";
			out << "N: " << visitedNodes->size() << " Q: " << fringe->size() << "\n";
		}
		if(problem->goalTest(current->getState(), problem->targetState))  //проверяем на совпадение с целевым
			return current;	//TODO: return solution - queue of nodes contains path

		QList<Node*>* successors = Expand(current, problem); //раскрываем листья
		//проверяем на нахождение листьев в очереди
		QString str;
		if(writeLog)
			str = "S"+QString::number(current->getDepth()+1)+":";
		for(Node* i:*successors){
			int hash = i->getState()->getHashI(); //получаем хэш ноды
			if(visitedNodes->contains(hash)){	//если в посещенных
				delete i;
			}else {
				visitedNodes->insert(hash,i);			//добавляем в посещенные
				fringe->append(i);						//добавляем в кромку
				if(writeLog)
					str.append(" " + i->getState()->toString());

			}
		}
		if(writeLog){
			out << str << "\n";
		}
		successors->clear();
		delete successors;
		refreshEvents();
	}
}
//enum{BFS,DLS,ERRCOUNT,MTT};

Node* RecDLS(Node*& pNode, Problem* problem, QHash<int,Node*>* visitedNodes, QQueue<Node*>* fringe, QTextStream& out){
	if(writeLog){
		out << "C" << pNode->getDepth() << ": " + pNode->getState()->toString()<< "\n";
		out << "N: " << visitedNodes->size() << " Q: " << fringe->size() << "\n";
	}
	if(problem->goalTest(problem->getTargetSate(),pNode->getState()))
		return pNode;
	if(pNode->getDepth()<=problem->getMaxDepth()){
		QList<Node*>* successors = Expand(pNode,problem);
		QString str;
		if(writeLog)
			str = "S"+QString::number(pNode->getDepth()+1)+":";
		for(Node* i:*successors){
			int hash = i->getState()->getHashI();
			if(writeLog)
				str.append(" " + i->getState()->toString()); // QString::number(hash,16) + " - " +
			if(visitedNodes->contains(hash)){	//если в посещенных
				successors->removeOne(i);
				delete i; //убираем уже пройденный узел
			}else{
				visitedNodes->insert(hash,i);//добавляем в посещенные
			}
		}
		if(writeLog)
			out << str << "\n";
		for(Node* i:*successors){
			Node* rlt = RecDLS(i,problem,visitedNodes,fringe,out);
			if(rlt)
				return rlt;
			else
				visitedNodes->remove(i->getState()->getHashI());
		}
		successors->clear();
		delete successors;
	}
	return nullptr;
}

Node* Tree_Search_DLS(Problem* problem, QHash<int,Node*> *visitedNodes, QQueue<Node*>* fringe){
	QFile file("out.txt");
	 if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		 return nullptr;
	QTextStream out(&file);

	Node* pStartNode = new Node(new State(
								   problem->getInitSate()->iState,
								   problem->getInitSate()->iXPos
								   ), nullptr,-1,0,0);
	visitedNodes->insert(pStartNode->getState()->getHashI(),pStartNode);
	return RecDLS(pStartNode,problem,visitedNodes,fringe,out);
}

QList<Node*>* SolveProblem(Problem* problem,QTextEdit* logWidget,int type){

	QQueue<Node*>* fringe = new QQueue<Node*>();
	QHash<int,Node*>* visitedNodes = new QHash<int,Node*>();

	logWidget->append("Initial: "+problem->getInitSate()->toString());
	logWidget->append("Target: "+problem->getTargetSate()->toString());

	QTime start = QTime::currentTime();
	Node* pResultNode = nullptr;
	switch(type){
	case BFS:
		logWidget->append("Type: BFS \n");
		pResultNode = Tree_Search_BFS(problem, visitedNodes, fringe);
		break;
	case DLS:
		logWidget->append("Type: DLS");
		logWidget->append("Depth: "+QString::number(problem->getMaxDepth())+"\n");
		pResultNode = Tree_Search_DLS(problem, visitedNodes, fringe);
		break;
	}
	logWidget->append("Time elapsed: "+QString::number(start.elapsed())+"ms");
	//Получаем решение
	QList<Node*>* solution = nullptr;
	if(pResultNode){
		solution = new QList<Node*>();
		for(Node* i = pResultNode;i;i=i->getParentNode()){
			Node* pNewNode = new Node(new State(i->getState()->iState,i->getState()->iXPos),i->getParentNode(),i->getAction(),i->getCost(),i->getDepth());
			solution->insert(solution->begin(),pNewNode);
		}
	}
	//Чистим память
	for(auto s:*visitedNodes){
		if(s!= nullptr)
			delete s;
	}
	delete visitedNodes;
	delete fringe;
	return solution;
}
