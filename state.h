#ifndef STATE_H
#define STATE_H

#include <QString>

class State
{
public:
	unsigned int iState; 	//State of the "world" like 87654321
	int iXPos;	//pos x between the number

	State(){
		iXPos = 0;
		iState = 0x12345678;
	}

	State(unsigned int state,int pos){
		iXPos = pos;
		iState = state;
	}

	QString toString(){
		QString str(QString("%1").arg(iState,0,16).toUpper());
		str.insert(8-iXPos,"x");
		str.insert(3,"|");
		str.insert(7,"|");
		return str;
	}
	int getPosI() {return iXPos/3;}
	int getPosJ() {return iXPos%3;}

	void fromString(QString str){
		iXPos = 8-str.indexOf('x');
		str.remove("x");
		iState = str.toInt(nullptr,16);
	}
};

#endif // STATE_H
