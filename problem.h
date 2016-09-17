#ifndef TREE_H
#define TREE_H


#include <QQueue>
#include <QVector>

#include <node.h>

class Problem{
private:
	Node *pInitialNode;
	State targetState;

	QVector<State (*)(Node*, int&)> vecOperations;
	bool (*goalTest) (Node*);
	int (*pathCost)();
public:
	Problem();
	Problem(QVector<State (*)(Node*, int&)> op, bool (*)(Node*),int (*)());
	friend Node* Tree_Search(Problem&, QQueue<Node>);	//Tree search (FIFO by QQueue) TODO: global alg
	friend QQueue<Node>& Expand(Node*, Problem&);
};


#endif // TREE_H
