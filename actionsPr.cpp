#include "actionsPr.h"


QString& getActStr(int a){
	QString* str = new QString();
	switch(a){
	case UP:
		str->append("^"); break;
	case RIGHT:
		str->append(">");break;
	case DOWN:
		str->append(".");break;
	case LEFT:
		str->append("<");break;
	default:
		str->append("X");
	}
	return *str;
}

State* up(Node* current, int& type){
	if(current->getState()->getPosI() == 2)
		return nullptr;

	int xPos = current->getState()->iXPos;

	unsigned int mask1=0xFF<<(4*(xPos)),
			mask2=0xF<<(4*(xPos+2)),
			mask3=~(mask1|mask2),
			temp=current->getState()->iState;
	temp = (temp&mask3)|((temp&mask1)<<4)|((temp&mask2)>>8);

	State* newState = new State(temp,xPos+3);

	type = UP;
	return newState;
}


State* right(Node* current, int& type){
	if(current->getState()->getPosJ() == 0)
		return nullptr;

	State* newState = new State(current->getState()->iState,current->getState()->iXPos-1);

	type = RIGHT;
	return newState;
}

State* down(Node* current, int& type){
	if(current->getState()->getPosI() == 0)
		return nullptr;

	int xPos = current->getState()->iXPos;

	unsigned int mask1=0xFF<<(4*(xPos-2)),
			mask2=0xF<<(4*(xPos-3)),
			mask3=~(0xFFF<<4*(xPos-3)),
			temp=current->getState()->iState;
	temp = ((temp&mask1)>>4)|((temp&mask2)<<8)|(mask3&temp);

	State* newState = new State(temp,xPos-3);

	type = DOWN;
	return newState;
}

State* left(Node* current, int& type){
	if(current->getState()->getPosJ() == 2)
		return nullptr;

	State* newState = new State(current->getState()->iState,current->getState()->iXPos+1);

	type = LEFT;
	return newState;
}

bool goalTest(State* current, State* eqState){
	return (current->iState == eqState->iState && current->iXPos == eqState->iXPos);
}
