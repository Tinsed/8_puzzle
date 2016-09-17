#include "actionsPr.h"

enum {UP,RIGHT,DOWN,LEFT,NUF};

void swap(char& a, char& b){
	auto c = a;
	a=b;
	b=c;
}

extern State* up(Node* current, int& type){
	if(current->getState()->iXPosI == 0 || current->getAction() == DOWN)
		return nullptr;

	int posI = current->getState()->iXPosI;
	int posJ = current->getState()->iXPosJ;

	State* newState = new State(current->getState()->aState,posI-1,posJ);
	swap(newState->aState[posI][posJ],
		 newState->aState[posI-1][posJ]);

	type = UP;
	return newState;
}


State* right(Node* current, int& type){
	if(current->getState()->iXPosJ == 2 || current->getAction() == LEFT)
		return nullptr;

	int posI = current->getState()->iXPosI;
	int posJ = current->getState()->iXPosJ;

	State* newState = new State(current->getState()->aState,posI,posJ+1);
	swap(newState->aState[posI][posJ],
		 newState->aState[posI][posJ+1]);

	type = RIGHT;
	return newState;
}

State* down(Node* current, int& type){
	if(current->getState()->iXPosI == 2 || current->getAction() == UP)
		return nullptr;

	int posI = current->getState()->iXPosI;
	int posJ = current->getState()->iXPosJ;

	State* newState = new State(current->getState()->aState,posI+1,posJ);
	swap(newState->aState[posI][posJ],
		 newState->aState[posI+1][posJ]);

	type = DOWN;
	return newState;
}

State* left(Node* current, int& type){
	if(current->getState()->iXPosJ == 0 || current->getAction() == RIGHT)
		return nullptr;

	int posI = current->getState()->iXPosI;
	int posJ = current->getState()->iXPosJ;

	State* newState = new State(current->getState()->aState,posI,posJ-1);
	swap(newState->aState[posI][posJ],
		 newState->aState[posI][posJ-1]);

	type = LEFT;
	return newState;
}

bool goalTest(Node* current, State* eqState){
	State* currentState = current->getState();
	if(currentState == nullptr) return false;
	for(int i = 0; i<9; i++){
		if(currentState->aState[i/3][i%3] != eqState->aState[i/3][i%3])
			return false;
	}
	return true;
}
