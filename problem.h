#ifndef TREE_H
#define TREE_H


#include <QQueue>
#include <QHash>
#include <QVector>
#include <QTextEdit>

#include <node.h>

enum{DFS,EXDEPTH,ERRCOUNT,MTT};

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
	void setInitSate(){ pInitialNode->getState();}
	State* getTargetSate(){return targetState;}

	friend QList<Node>* SolveProblem(Problem* problem,QQueue<Node*> fringe,QTextEdit* logWiget,int type);
	friend Node* Tree_Search(Problem*, QHash<QString,Node*>*, QQueue<Node*>*, QTextEdit* TextEdit);	//Tree search (FIFO by QQueue) TODO: global alg
	friend QList<Node*>* Expand(Node*, Problem*, QTextEdit* TextEdit);
};


#endif // TREE_H
