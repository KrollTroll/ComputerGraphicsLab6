#include "viewcontext.h"
#include <math.h>

viewcontext::viewcontext():transFWD(4,4), transBWD(4,4), homo(4,4), invHomo(4,4){
	for(int i = 0; i < 4; i++){
		transFWD[i][i] = 1;
		transBWD[i][i] = 1;
		homo[i][i] = 1;
		invHomo[i][i] = 1;
	}

	//set transformation x
	transFWD[0][3] =  -400;
	transBWD[0][3] = 400;
	//set transformation y
	transFWD[1][3] = 300;
	transBWD[1][3] = 300;
	//flip y
	transFWD[1][1] = -1;
	transBWD[1][1] = -1;
}

viewcontext::~viewcontext(){}

void viewcontext::changeX(char sign){
	matrix dummy = matrix::identity(4);
	matrix dummyInv = matrix::identity(4);
	int xlate = 0;
	if(sign == '-'){
		xlate = -20;
	}
	else{
		xlate = 20;
	}
	dummy[0][3] = xlate;
	dummyInv[0][3] = -xlate;
	homo = dummy * homo;
	invHomo = invHomo * dummyInv;

}

void viewcontext::changeY(char sign){
	matrix dummy = matrix::identity(4);
	matrix dummyInv = matrix::identity(4);
	int ylate = 0;
	if(sign == '-'){
		ylate = -20;
	}
	else{
		ylate = 20;
	}
	dummy[1][3] = ylate;
	dummyInv[1][3] = -ylate;
	homo = dummy * homo;
	invHomo = invHomo * dummyInv;
}

void viewcontext::changeDeg(char sign){
	matrix dummy = matrix::identity(4);
	matrix dummyInv = matrix::identity(4);
	float deg = 0.0;
	if(sign == '-'){
		deg = -10.0 * M_PI/180.0;
	}
	else{
		deg = 10.0 * M_PI/180.0;
	}
	dummy[0][0] =  cos(deg);
	dummy[1][0] = -sin(deg);
	dummy[0][1] =  sin(deg);
	dummy[1][1] =  cos(deg);

	dummyInv[0][0] =  cos(-deg);
	dummyInv[1][0] = -sin(-deg);
	dummyInv[0][1] =  sin(-deg);
	dummyInv[1][1] =  cos(-deg);

	//std::cout << dummy << std::endl;
	//std::cout << homo << std::endl;
	homo = dummy * homo;
	invHomo = invHomo * dummyInv;
	//std::cout << homo << std::endl;
}

void viewcontext::scale(char sign){
	matrix dummy = matrix::identity(4);
	matrix dummyInv = matrix::identity(4);
	double scaleFact = 1;
	if(sign == '-'){
		scaleFact = .5;
	}
	else{
		scaleFact = 2;
	}
	for(int i = 0; i < 2; i++){
		dummy[i][i] = scaleFact;
		dummyInv[i][i] = 1/scaleFact;
	}
	//std::cout << dummy << std::endl;
	homo = dummy * homo;
	invHomo = invHomo * dummyInv;
	//std::cout << homo << std::endl;
}

matrix viewcontext::convertToWindow(const matrix oldMat){
	//std::cout << oldMat << std::endl;
	return transBWD*homo*oldMat;
}

matrix viewcontext::convertToImage(const matrix oldMat){
	return invHomo*transFWD*oldMat;
}

void viewcontext::undo(){
	homo = matrix::identity(4);
	invHomo = matrix::identity(4);
}
