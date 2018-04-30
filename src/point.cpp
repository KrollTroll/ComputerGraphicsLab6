/**
 * Connor Kroll
 * Graphics
 *
 * This file implements control to a point object
 * 		The most basic shape, has no extra features
 */

#include "point.h"

#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

/**
 * Point constructor
 * @param x : point x coordinate
 * @param y : point y coordinate
 * @param R : point red color value
 * @param G : point green color value
 * @param B : point blue color value
 */
point::point(float x, float y, int R, int G, int B):shape(x,y,R,G,B){}

point::point(float x, float y, int R, int G, int B, viewcontext* vc):shape(x,y,R,G,B){

	//create display matrix
	coor[0][0] = x;
	coor[1][0] = y;
	for(int i = 0; i < 4; i++){
		coor[2][i] = 1;
		coor[3][i] = 1;
	}

	//convert display matrix to reflect image
	matrix newCoor = vc->convertToImage(coor);
	coor = newCoor;
	//std::cout << "COOR IN IMAGE" << std::endl;
	//std::cout << coor << std::endl;
	//std::cout << newCoor << std::endl;
	shape::x = x = coor[0][0];
	shape::y = y = coor[1][0];
	//std::cout << "x:" << x << " y:" << y << std::endl;
}

/**
 * copy constructor
 * @param from : point to cpoy data from
 */
point::point(const point& from):shape(from){}

/**
 * destructor - doesn't do much
 */
point::~point(){}

/**
 * draws the shape to the appropriate graphicscontext interface
 * @param GC : target graphicscontext interface
 */
void point::draw(GraphicsContext* GC){
	int color = (((this->RED << 8) + this->GREEN) << 8) + this->BLUE;
	GC->setColor(color);
	GC->setPixel(this->x, this->y);
}

void point::draw(GraphicsContext* GC, viewcontext* vc){

	matrix drawCoor = vc->convertToWindow(coor);
	//std::cout << "COOR OUT OF IMAGE" << std::endl;
	//std::cout << coor << std::endl;
	//std::cout << "DRAW COOR" << std::endl;
	//std::cout << drawCoor << std::endl;
	int color = (((this->RED << 8) + this->GREEN) << 8) + this->BLUE;
	GC->setColor(color);
	GC->setPixel(drawCoor[0][0], drawCoor[1][0]);
	//GC->setPixel(coor[0][0], coor[1][0]);
}

/**
 * Assignment operator
 * @param from : object to assign from
 * @return     : address of newly assigned object
 */
point& point::operator=(const point& from){
	this->shape::operator=(from);
	return *this;
}

/**
 * copies a point into another location in memory
 * @return : address of newly allocated point
 */
point& point::clone(){
	return *(new point(x, y, RED, GREEN, BLUE));
}

/**
 * prints point data to an output stream
 * @param os : target output stream
 * @return   : adress of same output stream
 */
std::ostream& point::out(std::ostream& os) const{
	os << "START POINT" << "\n";
	shape::out(os);
	os << "END" << endl << endl;
	return os;
}

/**
 * scans a single point from a file
 * @param in : desired file
 */
void point::in(std::istream& in) {
	//placeholder string for scanning
	string holder;
	//scan in line by line
	getline(in, holder);
	//remove whitespace
	holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
	//convert as necessary
	this->coor[1][0] = this->x = stof(holder);
	getline(in, holder);
	holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
	this->coor[1][0] = this->y = stof(holder);
	getline(in, holder);
	holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
	this->RED = stoi(holder);
	getline(in, holder);
	holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
	this->GREEN = stoi(holder);
	getline(in, holder);
	holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
	this->BLUE = stoi(holder);
}

/**
 * over-written global operator to print point data
 * @param os  : target output stream
 * @param rhs : point to output
 * @return    : adress of the same output stream
 */
std::ostream& operator<<(std::ostream& os, const point& rhs){
	rhs.out(os);
	return(os);
}
