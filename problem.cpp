#include <problem.h>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QtAlgorithms>

#include <actionsPr.h>

extern bool writeLog;
extern bool stepMode;
extern bool doStep;
extern bool doStop;
extern int countStep;
extern int countObj;

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

QList<Node*>* Expand(Node* current, Problem* problem, int (*heurFoo) (State*, State*)){
	QList<Node*>* successors = new QList<Node*>();

	for(auto Action:*problem->vecOperations){
		int act=0;
		State* newState = Action(current,act);
		if(newState != nullptr){
			int stepCost = (heurFoo)?(heurFoo(newState,problem->getTargetSate())):1;
			Node* s = new Node(newState, current, act,
							   current->getCost()+stepCost,
							   current->getDepth()+1);
			countObj++;
			successors->insert(successors->end(),s);
		}
	}

	return successors;
}

extern void refreshEvents();

Node* Tree_Search_BFS(Problem* problem, QHash<int,Node*> *visitedNodes, QQueue<Node*>* fringe, QTextEdit* logWidget){
	Node* startNode = new Node(new State(
								   problem->pInitialNode->getState()->iState,
								   problem->pInitialNode->getState()->iXPos
								   ), nullptr,-1,
							   problem->pInitialNode->getCost(),problem->pInitialNode->getDepth());
	countObj++;
	fringe->insert(fringe->begin(),startNode); //�������� ��������� ���� � �������
	visitedNodes->insert(startNode->getState()->getHashI(),startNode);

	QFile file("out.txt");
	 if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		 return nullptr;
	QTextStream out(&file);

	while(1){
		countStep++;
		if(doStop){
			doStop = false;
			logWidget->append("Stopped");
			return nullptr;
		}

		if(fringe->empty())
			return nullptr;	//���� ������� ����� �������
		Node* current = fringe->first();fringe->pop_front();  //�������� ������ ������� �������
			//�������� ������ ����

		if(writeLog){
			out << "C" << current->getDepth() << ": " + current->getState()->toString()<< "\n";
			out << "N: " << visitedNodes->size() << " Q: " << fringe->size() << "\n";
		}

		if(problem->goalTest(current->getState(), problem->targetState))  //��������� �� ���������� � �������
			return current;	//TODO: return solution - queue of nodes contains path

		QList<Node*>* successors = Expand(current, problem); //���������� ������
		//��������� �� ���������� ������� � �������
		QString str;
		QString strDel;
		if(writeLog)
			str = "S"+QString::number(current->getDepth()+1)+":";
		for(Node* i:*successors){
			int hash = i->getState()->getHashI(); //�������� ��� ����
			if(visitedNodes->contains(hash)){	//���� � ����������
				if(stepMode)
					strDel.append(" " + i->getState()->toString());
				delete i;
			}else {
				visitedNodes->insert(hash,i);			//��������� � ����������
				fringe->append(i);						//��������� � ������
				if(writeLog||stepMode)
					str.append(" " + i->getState()->toString());
			}
		}
		if(stepMode){
			logWidget->append("Target node: "+problem->targetState->toString());
			logWidget->append("Current node: "+current->getState()->toString());
			logWidget->append("Depth: "+QString::number(current->getDepth()));
			logWidget->append("Successors:"+str);
			logWidget->append("Colisions:"+strDel);
			logWidget->append("Visited nodes: "+QString::number(visitedNodes->size()));
			logWidget->append("Fringe size: "+QString::number(fringe->size()));
			QString strFringe;
			int counter = 6;
			for(Node* i:*fringe){
				strFringe.append(i->getState()->toString()+ " D: "+QString::number(i->getDepth())+"; ");
				counter--;
				if(counter==0){
					strFringe.append("\n");
					counter=6;
				}
			}
			logWidget->append("Fringe: \n"+strFringe);

		}
		if(writeLog){
			out << str << "\n";
		}
		successors->clear();
		delete successors;
		refreshEvents();

		if(stepMode){
			logWidget->append("Wait for step....");
			while(!doStep){
				refreshEvents();
			}
			if(stepMode) logWidget->clear();
			doStep = false;
		}
	}
}

Node* RecDLS(Node*& pNode, Problem* problem, QHash<int,int>* visitedNodes, QQueue<Node*>* fringe,QHash<int,Node*> *unqNodes, QTextEdit* logWidget, QTextStream& out){
	if(writeLog){
		out << "C" << pNode->getDepth() << ": " + pNode->getState()->toString()<< "\n";
		out << "N: " << visitedNodes->size() << "\n";
	}
	countStep++;
	refreshEvents();
	if(doStop){
		return nullptr;
	}
	if(stepMode) fringe->removeOne(pNode);
	if(problem->goalTest(problem->getTargetSate(),pNode->getState()))
		return pNode;
	if(pNode->getDepth()<=problem->getMaxDepth()){
		QList<Node*>* successors = Expand(pNode,problem);
		QString str, strDel;
		if(writeLog)
			str = "S"+QString::number(pNode->getDepth()+1)+":";
		for(Node* i:*successors){
			int hash = i->getState()->getHashI();
			if(writeLog||stepMode)
				str.append(" " + i->getState()->toString()); // QString::number(hash,16) + " - " +
			if(!unqNodes->contains(hash)){
				unqNodes->insert(hash,nullptr);
			}
			if(visitedNodes->contains(hash)){	//���� � ����������
				if((*visitedNodes)[hash] <= i->getDepth()){
					successors->removeOne(i);
					if(stepMode)
						strDel.append(" " + i->getState()->toString());
					delete i; //������� ��� ���������� ����
				}else{
					(*visitedNodes)[hash]=i->getDepth();
				}
			}else{
				visitedNodes->insert(hash,i->getDepth());//��������� � ����������
				if(stepMode)
					fringe->insert(fringe->begin(),i);
			}
		}
		if(stepMode){
			logWidget->clear();
			logWidget->append("Target node: "+problem->targetState->toString());
			logWidget->append("Current node: "+pNode->getState()->toString());
			logWidget->append("Depth: "+QString::number(pNode->getDepth()));
			logWidget->append("Successors:"+str);
			logWidget->append("Colisions:"+strDel);
			logWidget->append("Unique nodes: "+QString::number(unqNodes->size()));
			logWidget->append("Visited nodes: "+QString::number(visitedNodes->size()));
			logWidget->append("Fringe size: "+QString::number(fringe->size()));
			QString strFringe;
			int counter = 6;
			for(Node* i:*fringe){
				strFringe.append(i->getState()->toString()+ " D: "+QString::number(i->getDepth())+"; ");
				counter--;
				if(counter==0){
					strFringe.append("\n");
					counter=6;
				}
			}
			logWidget->append("Fringe: \n"+strFringe);

		}
		if(writeLog)
			out << str << "\n";
		if(stepMode){
			logWidget->append("Wait for step....");
			while(!doStep){
				refreshEvents();
			}
			if(stepMode) logWidget->clear();
			doStep = false;
			doStop = false;
		}
		for(Node* i:*successors){
			Node* rlt = RecDLS(i,problem,visitedNodes,fringe,unqNodes,logWidget,out);
			if(rlt)
				return rlt;
		}
		successors->clear();
		delete successors;
	}
	return nullptr;
}

Node* Tree_Search_DLS(Problem* problem, QHash<int,Node*> *unqNodes, QQueue<Node*>* fringe, QTextEdit* logWidget){
	//��������� ��������� �����
	QFile file("out.txt");
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
		 if(writeLog)return nullptr;
	QTextStream out(&file);

	//�������� ��������� ���� �� �������
	Node* pStartNode = new Node(new State(
								   problem->getInitSate()->iState,
								   problem->getInitSate()->iXPos
								   ), nullptr,-1,0,0);
	countObj++;
	QHash<int,int> *dNodes = new QHash<int,int>();
	dNodes->insert(pStartNode->getState()->getHashI(),pStartNode->getDepth()); // ����������� ��� � ����������
	unqNodes->insert(pStartNode->getState()->getHashI(),pStartNode);
	fringe->insert(fringe->begin(),pStartNode);
	Node* ret = RecDLS(pStartNode,problem,dNodes,fringe,unqNodes,logWidget,out);
	delete dNodes;
	return ret;
}

Node* Tree_Search_AStar(Problem* problem, QHash<int, Node*> *unqNodes, QQueue<Node*>* fringeo, QTextEdit* logWidget){
	QMultiMap<int,Node*>* fringe = new QMultiMap<int, Node*>();
	Node* pStartNode = new Node(new State(
								   problem->getInitSate()->iState,
								   problem->getInitSate()->iXPos
								   ), nullptr,-1,0,0);
	fringe->insert(0,pStartNode);

	while(!fringe->isEmpty()){
		countStep++;
		refreshEvents();
		if(doStop){
			doStop = false;
			logWidget->append("Stopped");
			return nullptr;
		}

		Node* current = fringe->first();
		fringe->erase(fringe->begin());
		/*logWidget->append(QString("Cur: "+current->getState()->toString()+"  D:%1 C:%2")
						  .arg(current->getDepth(),2,10,QChar('0'))
						  .arg(current->getCost(),3,10,QChar('0')));*/
		unsigned int hash = current->getState()->getHashI();

		if(unqNodes->contains(hash))
			continue;
		else
			unqNodes->insert(hash,current);


		if(problem->goalTest(current->getState(),problem->targetState)){
			return current;
		}
		QList<Node*>* successors = Expand(current, problem, problem->heuristicFoo); //���������� ������
		//QString str = "Suc:";
		for(Node* s:(*successors)){
			if(unqNodes->contains(s->getState()->getHashI())){
				delete s;
			}else{
				//str.append(QString(" "+current->getState()->toString()+"  D:%1 C:%2")
								  //.arg(current->getDepth(),2,10,QChar('0'))
								  //.arg(current->getCost(),3,10,QChar('0')));
				fringe->insert(s->getCost(),s);
			}
		}
	}
	return nullptr;
}

QList<Node*>* SolveProblem(Problem* problem, QTextEdit* logWidget, int type){

	//��� ���������� �������, ����� solution ���������� ������ �� ����� ���������� ����� �������
	QQueue<Node*>* fringe = new QQueue<Node*>();
	QHash<int,Node*>* visitedNodes = new QHash<int,Node*>();

	logWidget->append("Initial: "+problem->getInitSate()->toString());
	logWidget->append("Target: "+problem->getTargetSate()->toString());

	QTime start = QTime::currentTime();
	Node* pResultNode = nullptr;
	switch(type){
	case BFS:  //� ������
		logWidget->append("Type: BFS \n");
		pResultNode = Tree_Search_BFS(problem, visitedNodes, fringe, logWidget);
		break;
	case DLS:  //� ������������ �������
		logWidget->append("Type: DLS");
		logWidget->append("Depth: "+QString::number(problem->getMaxDepth())+"\n");
		pResultNode = Tree_Search_DLS(problem, visitedNodes, fringe, logWidget);
		if(doStop){
			logWidget->append("Stopped");
			doStop = false;
		}
		break;
	case ERRCOUNT:
		logWidget->append("Type: A* \n");
		logWidget->append("H function: Error positions \n");
		problem->heuristicFoo = &heuristicErrCount;
		pResultNode = Tree_Search_AStar(problem, visitedNodes, fringe, logWidget);
		break;
	case MTT:
		logWidget->append("Type: A* \n");
		logWidget->append("Goal function: Manhattan \n");
		problem->heuristicFoo = &heuristicManhattan;
		pResultNode = Tree_Search_AStar(problem, visitedNodes, fringe, logWidget);
	}
	logWidget->append("Time elapsed: "+QString::number(start.elapsed())+"ms");
	//�������� �������
	QList<Node*>* solution = nullptr;
	if(pResultNode){
		solution = new QList<Node*>();
		for(Node* i = pResultNode;i;i=i->getParentNode()){ //����������� �� ����������� ����� � �����
			Node* pNewNode = new Node(new State(i->getState()->iState,i->getState()->iXPos),
									  i->getParentNode(),i->getAction(),i->getCost(),i->getDepth());
			countObj++;
			solution->insert(solution->begin(),pNewNode); //���� �������� � ������ ������
		}
	}
	logWidget->append("Unique nodes: "+QString::number(visitedNodes->size()));
	//������ ������
	for(auto s:*visitedNodes){
		if(s!= nullptr)
			delete s;
	}
	delete visitedNodes;
	delete fringe;
	return solution;
}
