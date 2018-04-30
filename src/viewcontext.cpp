#include "viewcontext.h"
#include <math.h>

viewcontext::viewcontext():transFWD(4,4), transBWD(4,4), homo(4,4){
	for(int i = 0; i < 4; i++){
		transFWD[i][i] = 1;
		transBWD[i][i] = 1;
		homo[i][i] = 1;
	}

	//set transformation x
	transFWD[0][3] =  400;
	transBWD[0][3] = -400;
	//set transformation y
	transFWD[1][3] = 300;
	transBWD[1][3] = 300;
	//flip y
	transFWD[1][1] = -1;
	transBWD[1][1] = -1;

	homo = homo*transFWD;

	deg = 0;
	ylate = 0;
	xlate = 0;
	scaleFact = 1;

	//std::cout << transFWD << std::endl;
	//std::cout << transBWD << std::endl;
	//std::cout << homo << std::endl;
}

viewcontext::~viewcontext(){}

//TODO: make it work
matrix viewcontext::convertToImage(const matrix oldMat){
	return transBWD*oldMat;
}

matrix viewcontext::convertToWindow(const matrix oldMat){
	return transFWD*oldMat;
}

void viewcontext::changeX(char sign){
	if(sign == '-'){
		xlate = -20;
	}
	else{
		xlate = 20;
	}
}

void viewcontext::changeY(char sign){
	if(sign == '-'){
		ylate = -20;
	}
	else{
		ylate = 20;
	}
}

void viewcontext::changeDeg(char sign){
	if(sign == '-'){
		deg = -10;
	}
	else{
		deg = 10;
	}
}

void viewcontext::scale(char sign){
	if(sign == '-'){
		scaleFact = .5;
	}
	else{
		scaleFact = 2;
	}
}

void undo(){}
