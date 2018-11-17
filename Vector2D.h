#pragma once
#include "checkML.h"

class Vector2D {
// --------------------- variables------------------------------------------------------
private:
	double x, y;

// ---------------------- methods ------------------------------------------------------
public:
	Vector2D () : x (0.0), y (0.0) {}
	Vector2D (double xVal, double yVal) : x (xVal), y (yVal) {}
	~Vector2D ();

	// sum (+) operation between two vectors
	Vector2D operator+(const Vector2D &other);
	// substraction (-) operation between two vectors
	Vector2D operator-(const Vector2D &other);
	// multiplication by an integer (*int)
	Vector2D operator*(const int &number);
	// scalar product (Vector2D · Vector2D)
	double operator*(const Vector2D &other);

	// getter functions for X and Y
	double getX () const { return x; }
	double getY () const { return y; }

	// setter functions for X and Y
	void setX (double newX) { x = newX; }
	void setY (double newY) { y = newY; }
};

