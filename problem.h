#ifndef TREE_H
#define TREE_H


#include <QQueue>
#include <QHash>
#include <QVector>
#include <QTextEdit>
#include <QTextStream>

#include <node.h>

enum{BFS,DLS,ERRCOUNT,MTT};

class Problem{
private:
	Node *pInitialNode;
	State *targetState;

	int type;

	int	iMaxDepth;
	QVector<State* (*)(Node*, int&)>* vecOperations;
	bool (*goalTest) (State*, State*);
	int (*pathCost)();

public:
	int (*heuristicFoo) (State*, State*);
	Problem();
	Problem(QVector<State* (*)(Node*, int&)>*,
			bool (*)(State*, State*),
			int (*)(),
			int);
	~Problem();

	int getMaxDepth(){return iMaxDepth;}
	void setMaxDepth(int d){iMaxDepth = d;}

	int getType(){ return type;}
	void setType(int t){ type=t;}

	State* getInitSate(){return pInitialNode->getState();}
	//void setInitSate(){ pInitialNode->getState();}
	State* getTargetSate(){return targetState;}

	friend QList<Node*>* SolveProblem(Problem* problem, QTextEdit* logWiget, int type);

	friend QList<Node*>* Expand(Node* currentNode, Problem*); //open node for successors

	friend Node* Tree_Search_BFS(Problem*, QHash<int, Node*>* visitedNodes, QQueue<Node*>* fringe, QTextEdit* logWidget);	//Tree search (FIFO by QQueue)

	friend Node* RecDLS(Node*& pStartNode, Problem* problem, QHash<int, int> *visitedNodes, QQueue<Node*>* fringe,QHash<int,Node*> *unqNodes, QTextEdit* logWidget, QTextStream& out);
	friend Node* Tree_Search_DLS(Problem* problem, QHash<int, Node*> *visitedNodes, QQueue<Node*>* fringe, QTextEdit* logWidget);

	friend Node* Tree_Search_AStar(Problem* problem, QHash<int, Node*> *visitedNodes, QTextEdit* logWidget);
};
#endif // TREE_H
