#ifndef STATE_H
#define STATE_H

#include <stdio.h>

class State
{
	char aState[2][2];  //State of the "world" like 742|358|6x1
	int iXPosition;  // high bite for i, low - j.
public:
	State(){
		iXPosition=0;
		//aState={{'x','1','2'},{'3','4','5'},{'6','7','8'}};
	}
	State(char* s,int pos):iXPosition(pos){
		for(int i =0; i<9;*(*(aState+i/3)+i%3)=*(s+i));
	}
};

#endif // STATE_H
