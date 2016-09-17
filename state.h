#ifndef STATE_H
#define STATE_H

#include <QString>

class State
{
public:
	char aState[3][3];  //State of the "world" like 742|358|6x1
	int iXPosI, iXPosJ;

	State(){
		iXPosI = iXPosJ = 0;
		for(int i =0; i<9;i++)
			aState[i/3][i%3]=0;
	}

	State(char s[][3],int posI,int posJ){
		iXPosI = posI;
		iXPosJ = posJ;
		for(int i = 0; i<9; i++)
			aState[i/3][i%3] = s[i/3][i%3];
	}

	QString toString(){
		QString str;
		str.append(QString::fromLatin1(aState[0],3)+"|");
		str.append(QString::fromLatin1(aState[1],3)+"|");
		str.append(QString::fromLatin1(aState[2],3));

		return str;
	}
};

#endif // STATE_H
