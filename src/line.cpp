/**
 * Connor Kroll
 * Graphics
 *
 * This file implements control to a line object
 * 		Lines extend shape and add an endpoint
 */

#include "line.h"

#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

	/**
 	 * line consructor
	 * @param x  : start point x coordinate
	 * @param y  : start point y coordinate
	 * @param R  : line red color value
	 * @param G  : line green color value
	 * @param B  : line blue color value
	 * @param x2 : end point x coordinate
	 * @param y2 : end point y coordinate
	 */
	line::line(float x, float y, int R, int G, int B, float x2, float y2):shape(x,y,R,G,B){
		this->x2 = x2;
		this->y2 = y2;
		this->coor[0][1] = x2;
		this->coor[1][1] = y2;
		for(int i = 0; i < 4; i++){
			coor[2][i] = 0;
			coor[3][i] = 1;
		}
	}

	line::line(float x, float y, int R, int G, int B, float x2, float y2, viewcontext* vc):shape(x,y,R,G,B){
			//create display matrix
			this->x2 = x2;
			this->y2 = y2;
			//coor[0][0] = x;
			//coor[1][0] = y;
			coor[0][1] = this->x2;
			coor[1][1] = this->y2;
			//std::cout << "INIT COOR : " << x << "," << y << " | " << x2 << "," << y2 << std::endl;
			for(int i = 0; i < 4; i++){
					coor[2][i] = 0;
					coor[3][i] = 1;
			}

			//convert display matrix to image matrix
			matrix newCoor = vc->convertToImage(coor);
			coor = newCoor;
			shape::x = coor[0][0];
			shape::y = coor[1][0];
			//std::cout << "CONV COOR1 : " << x << "," << y << " | " << x2 << "," << y2 << std::endl;
			//std::cout << "MAT COOR1 : " << coor[0][0] << "," << coor[1][0] << " | " << coor[0][1] << "," << coor[1][1] << std::endl;
			this->x2 = coor[0][1];
			this->y2 = coor[1][1];
			//std::cout << "CONV COOR2 : " << x << "," << y << " | " << x2 << "," << y2 << std::endl;
			//std::cout << "MAT COOR2 : " << coor[0][0] << "," << coor[1][0] << " | " << coor[0][1] << "," << coor[1][1] << std::endl;
			//std::cout << "COOR GOING INTO IMAGE" << std::endl;
			//std::cout << coor << std::endl;
	}

	/**
	 * copy constructor for a line
	 * @param from : line to copy from
	 */
	line::line(const line& from):shape(from){
		this->coor[0][1] = this->x2 = from.x2;
		this->coor[1][1] = this->y2 = from.x2;
	}

	/**
	 * Destructor - there is nothing to free
	 */
	line::~line(){}

	/**
	 * draws a line to a garphics context interface
	 * @param GC : target interface
	 */
	void line::draw(GraphicsContext* GC){
		int color = (((this->RED << 8) + this->GREEN) << 8) + this->BLUE;
		GC->setColor(color);
		GC->drawLine(coor[0][0], coor[1][0], coor[0][1], coor[1][1]);
	}

	void line::draw(GraphicsContext* GC, viewcontext* vc){

			//std::cout << "COOR OUT OF FILE" << std::endl;
			//std::cout << coor << std::endl;
			matrix drawCoor = vc->convertToWindow(coor);
			//std::cout << "DRAW COOR" << std::endl;
			//std::cout << drawCoor << std::endl;

			int color = (((this->RED << 8) + this->GREEN) << 8) + this->BLUE;
			GC->setColor(color);
			GC->drawLine(drawCoor[0][0], drawCoor[1][0], drawCoor[0][1], drawCoor[1][1]);
			//GC->drawLine(coor[0][0], coor[1][0], coor[0][1], coor[1][1]);
	}

	/**
	 * assignment operator - sets one line equal to another
	 * @param from : line to assign from
	 * @return     :  address of newly assigned line
	 */
	line& line::operator=(const line& from){
		this->shape::operator=(from);
		this->coor[0][1] = this->x2 = from.x2;
		this->coor[1][1] = this->y2 = from.x2;
		return *this;
	}

	/**
	 * Copies one line into a new location in memory
	 * @return : address of newly allocated copy
	 */
	line& line::clone(){
		return *(new line(x, y, RED, GREEN, BLUE, x2, y2));
	}

	/**
	 * outputs line characteristics to desired output stream
	 * @param os : desired output stream
	 * @return   :  address of that same stream
	 */
	std::ostream& line::out(std::ostream& os) const{
		//std::cout << "OUT COOR : " << shape::x << "," << shape::y << " | " << x2 << "," << y2 << std::endl;
		os << "START LINE" << "\n";
		shape::out(os);
		os << "  " << coor[0][1] << "\n";
		os << "  " << coor[1][1] << "\n";
		os << "END" << endl << endl;

		//std::cout << this->coor[0][1] << " " << this->coor[1][1] << std::endl;
		return os;
	}

	/**
	 * read in a single line from a file
	 * @param in : istream to parse from
	 * @return   : the new triangle object
	 */
	void line::in(std::istream& in) {
		//placeholder string for read in
		string holder;
		//read in data line by line
		getline(in, holder);
		//remove spaces
		holder.erase(std::remove(holder.begin(),holder.end(),' '),holder.end());
		//convert as necessary
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
	}

	/**
	 * over-written global operator for easy output
	 * @param os  : target output stream
	 * @param rhs : object to output
	 * @return    : address of the same output stream
	 */
	std::ostream& operator<<(std::ostream& os, const line& rhs){
		rhs.out(os);
		return os;
	}
