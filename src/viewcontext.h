#ifndef VIEWCONTEXT_H_
#define VIEWCONTEXT_H_

#include "matrix.h"

class viewcontext{

public:
viewcontext();
~viewcontext();

matrix convertToImage(const matrix oldMat);
matrix convertToWindow(const matrix oldMat);

void changeX(char sign);
void changeY(char sign);

void changeDeg(char sign);

void scale(char sign);

void undo();

private:
//trans image to disp
matrix transFWD;
//trans disp to image
matrix transBWD;
//homogenous matrix
matrix homo;

int deg;
int ylate;
int xlate;
int scaleFact;
};
#endif