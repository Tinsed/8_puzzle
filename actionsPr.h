#ifndef ACTIONS_H_0
#define ACTIONS_H_0

#include <node.h>

enum{ UP, RIGHT, DOWN, LEFT, NUF}; //Actions

QString& getActStr(int);

State* up(Node*, int&);
State* right(Node*, int&);
State* down(Node*, int&);
State* left(Node*, int&);

bool goalTest(State*,State*);

int heuristicErrCount(State*, State*);
int heuristicManhattan(State*, State*);

#endif // ACTIONS_H
