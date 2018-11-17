#include "Vector2D.h"


Vector2D::~Vector2D () {
}


Vector2D Vector2D::operator+(const Vector2D &other) {
	x += other.getX();
	y += other.getY();

	return *this;
}


Vector2D Vector2D::operator-(const Vector2D &other) {
	x -= other.getX();
	y -= other.getY();

	return *this;
}


Vector2D Vector2D::operator*(const int &number) {
	x *= number;
	y *= number;

	return *this;
}


double Vector2D::operator*(const Vector2D &other) {
	return (x + other.getX()) + (y + other.getY ());
}