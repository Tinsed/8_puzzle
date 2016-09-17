#ifndef TREE_H
#define TREE_H


#include <QQueue>
#include <QVector>
#include <QTextEdit>

#include <node.h>

class Problem{
private:
	Node *pInitialNode;
	State *targetState;
	int	iMaxDepth;
	QVector<State* (*)(Node*, int&)> vecOperations;
	bool (*goalTest) (Node*, State*);
	int (*pathCost)();
public:
	Problem();
	Problem(QVector<State* (*)(Node*, int&)> op,
			bool (*)(Node*, State*),
			int (*)(),
			int);
	int getMaxDepth(){return iMaxDepth;}
	void setMaxDepth(int d){iMaxDepth=d;}


	friend Node* Tree_Search(Problem&, QQueue<Node*>&, QTextEdit* TextEdit);	//Tree search (FIFO by QQueue) TODO: global alg
	friend QQueue<Node*>* Expand(Node*, Problem&, QTextEdit* TextEdit);
};


#endif // TREE_H
