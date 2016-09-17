#ifndef ACTIONS_H_0
#define ACTIONS_H_0

#include <node.h>

//enum{ UP, RIGHT, DOWN, LEFT, NUF}; //Actions

State* up(Node*, int&);
State* right(Node*, int&);
State* down(Node*, int&);
State* left(Node*, int&);

bool goalTest(Node*,State*);

#endif // ACTIONS_H
