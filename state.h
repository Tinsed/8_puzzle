#ifndef STATE_H
#define STATE_H

#include <QString>
#include <QByteArray>

union intAChar{
	int a;
	char ch[4];
};

class State
{
public:
	unsigned int iState; 	//State of the "world" like 87654321
	int iXPos;	//pos x between the number

	State(){  //123|456|78x
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

	unsigned int getHashI(){
		return iState + iXPos;
	}

	int getPosI() {return iXPos/3;}
	int getPosJ() {return iXPos%3;}

	void fromString(QString str){
		iXPos = 8-str.indexOf('x');
		str.remove("x");
		QString temp = str;
		temp.remove(4,4);
		str.remove(temp);
		iState = (temp.toUInt(nullptr,16)<<16)|str.toUInt(nullptr,16);
	}
};

#endif // STATE_H
