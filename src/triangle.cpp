/**
 * Connor Kroll
 * Graphics
 *
 * This file implements control to a triangle object
 * 		It extends shape and adds two more points
 */

#include <vector>
#include <cstdlib>
#include <algorithm>

#include "triangle.h"

using namespace std;

/**
 * basic triangle constructor
 * @param x  : origin x coordinate
 * @param y  : origin y coordinate
 * @param R  : RED value
 * @param G  : GREEN value
 * @param B  : BLUE value
 * @param x2 : second point x coordinate
 * @param y2 : second point y coordinate
 * @param x3 : third point x coordinate
 * @param y3 : third point y coordinate
 */
triangle::triangle(float x, float y, int R, int G, int B, float x2, float y2, float x3, float y3):shape(x,y,R,G,B){
	this->x2 = x2;
	this->y2 = y2;
	this->x3 = x3;
	this->y3 = y3;
	coor[0][1] = x2;
	coor[1][1] = y2;
	coor[0][2] = x3;
	coor[1][2] = y3;
	for(int i = 0; i < 4; i++){
		coor[2][i] = 1;
		coor[3][i] = 1;
	}
}

triangle::triangle(float x, float y, int R, int G, int B, float x2, float y2, float x3, float y3, viewcontext* vc)
									:shape(x,y,R,G,B){
	//create display matrix
	this->x2 = x2;
	this->y2 = y2;
	this->x3 = x3;
	this->y3 = y3;
	coor[0][1] = x2;
	coor[1][1] = y2;
	coor[0][2] = x3;
	coor[1][2] = y3;
	for(int i = 0; i < 4; i++){
		coor[2][i] = 1;
		coor[3][i] = 1;
	}

	//convert display matrix to model
	//convert display matrix to image matrix
	matrix newCoor = vc->convertToImage(coor);
	coor = newCoor;
	x = coor[0][0];
	y = coor[0][1];
	x2 = coor[1][0];
	y2 = coor[1][1];
	x3 = coor[0][2];
	y3 = coor[1][2];
}

/**
 * copy constructor
 * @param from : triangle to copy data from
 */
triangle::triangle(const triangle& from):shape(from){
	this->x2 = from.x2;
	this->y2 = from.x2;
	this->x3 = from.x3;
	this->y3 = from.x3;
	coor[0][1] = x2;
	coor[1][1] = y2;
	coor[0][2] = x3;
	coor[1][2] = y3;
}

/**
 * destructor - doesn't do much
 */
triangle::~triangle(){}

/**
 * draws a triangle to a target graphics context interface
 * @param GC : target interface
 */
void triangle::draw(GraphicsContext* GC){
	int color = (((this->RED << 8) + this->GREEN) << 8) + this->BLUE;
	GC->setColor(color);
	GC->drawLine(coor[0][0],  coor[1][0],  coor[0][1], coor[1][1]);
	GC->drawLine(coor[0][1],  coor[1][1],  coor[0][2], coor[1][2]);
	GC->drawLine(coor[0][2],  coor[1][2],  coor[0][0], coor[0][1]);
}

void triangle::draw(GraphicsContext* GC, viewcontext* vc){
	int color = (((this->RED << 8) + this->GREEN) << 8) + this->BLUE;
	GC->setColor(color);
	GC->drawLine(coor[0][0],  coor[1][0],  coor[0][1], coor[1][1]);
	GC->drawLine(coor[0][1],  coor[1][1],  coor[0][2], coor[1][2]);
	GC->drawLine(coor[0][2],  coor[1][2],  coor[0][0], coor[0][1]);
}

/**
 * assignment operator - assigns one triangle the data of another
 * @param from : triangle to assign from
 * @return     : address of the triangle assigned to
 */
triangle& triangle::operator=(const triangle& from){
	this->shape::operator=(from);
	this->coor[0][1] = this->x2 = from.x2;
	this->coor[1][1] = this->y2 = from.y2;
	this->coor[0][2] = this->x3 = from.x3;
	this->coor[1][2] = this->y3 = from.y3;
	return *this;
}

/**
 * copies a triangle into a different location in memory
 * @return : address of newly allocated triangle
 */
triangle& triangle::clone(){
	return *(new triangle(x, y, RED, GREEN, BLUE, x2, y2, x3, y3));
}

/**
 * outputs data from the triangle to the desired output stream
 * @param os : desired output stream
 * @return   : address of that same stream
 */
std::ostream& triangle::out(std::ostream& os) const{
	os << "START TRIANGLE" << "\n";
	shape::out(os);
	os << "  " << coor[0][1] << "\n";
	os << "  " << coor[1][1] << "\n";
	os << "  " << coor[0][2] << "\n";
	os << "  " << coor[1][2] << "\n";
	os << "END" << endl << endl;
	return os;
}

/**
 * read in a single triangle from a file
 * @param in : istream to parse from
 * @return   : the new triangle object
 */
void triangle::in(std::istream& in) {

		//Print error if file does not open for whatever reason
		if(!in){
			cerr << "\n**Unable to open file " << endl;
			cout << "**\n**File may be missing, incorrect format, or corrupted**\n\n";
		}
		//If the file is valid
		else{
			string holder;

				getline(in, holder);
				holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
				this->coor[0][0] = this->x = stof(holder);
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
				getline(in, holder);
				holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
				this->coor[0][1] = this->x2 = stof(holder);
				getline(in, holder);
				holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
				this->coor[1][1] = this->y2 = stof(holder);
				getline(in, holder);
				holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
				this->coor[0][2] = this->x3 = stof(holder);
				getline(in, holder);
				holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
				this->coor[1][2] = this->y3 = stof(holder);
		}
}

/**
 * over-written global operator for easy output
 * @param os  : desired output stream
 * @param rhs : object to output
 * @return    : address of the output stream
 */
std::ostream& operator<<(std::ostream& os, const triangle& rhs){
	rhs.out(os);
	return os;
}
