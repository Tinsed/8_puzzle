#include "actionsPr.h"

enum {UP,RIGHT,DOWN,LEFT,NUF};

void swap(char& a, char& b){
	auto c = a;
	a=b;
	b=c;
}

extern State* up(Node* current, int& type){
	if(current->getState()->getPosI() == 2 || current->getAction() == DOWN)
		return nullptr;

	int xPos = current->getState()->iXPos;

	unsigned int mask1=0xFF<<(4*(xPos+1)), mask2=0xF<<(4*xPos), mask3=~(mask1|mask2), temp=current->getState()->iState;
	temp = (temp&mask3)|((temp<<4)&mask1)|((temp>>8)&mask2);

	State* newState = new State(temp,xPos+3);

	type = UP;
	return newState;
}


State* right(Node* current, int& type){
	if(current->getState()->getPosJ() == 0 || current->getAction() == LEFT)
		return nullptr;

	State* newState = new State(current->getState()->iState,current->getState()->iXPos-1);

	type = RIGHT;
	return newState;
}

State* down(Node* current, int& type){
	if(current->getState()->getPosI() == 0 || current->getAction() == UP)
		return nullptr;

	int xPos = current->getState()->iXPos;

	unsigned int mask1=0xFF<<(4*(xPos-2)), mask2=0xF<<(4*(xPos-3)), mask3=~(0xFFF<<4*(xPos-3)), temp=current->getState()->iState;
	mask1 = (temp&mask1)>>4;
	mask2 = (temp&mask2)<<8;
	mask3 &= temp;
	temp = mask1|mask2|mask3;

	State* newState = new State(temp,xPos-3);

	type = DOWN;
	return newState;
}

State* left(Node* current, int& type){
	if(current->getState()->getPosJ() == 2 || current->getAction() == RIGHT)
		return nullptr;

	State* newState = new State(current->getState()->iState,current->getState()->iXPos+1);

	type = LEFT;
	return newState;
}

bool goalTest(Node* current, State* eqState){
	State* currentState = current->getState();
	if(currentState == nullptr) return false;
	if(currentState->iState != eqState->iState
			||currentState->iXPos != eqState->iXPos)
		return false;
	else return true;
}
