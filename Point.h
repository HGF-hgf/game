#pragma once
#include<iostream>
#include<string>

using namespace std;

class Point {
public:
	float X, Y;

	Point(float X = 0, float Y = 0) : X(X), Y(Y){}

	inline Point operator+(const Point& p2) const {
		return Point(X + p2.X, Y + p2.Y);
	}

	inline friend Point operator +=(Point& p1, Point& p2) {
		p1.X += p2.X;
		p1.Y += p2.Y;
		return p1;
	}


	inline Point operator-(const Point& p2) const {
		return Point(X - p2.X, Y - p2.Y);
	}

	inline friend Point operator -=(Point& p1, Point& p2) {
		p1.X -= p2.X;
		p1.Y -= p2.Y;
		return p1;
	}

	inline Point operator *(const float scalar) const {
		return Point(X * scalar, Y * scalar);
	}

	void Log(string msg = "") {
		cout << msg << "(X,Y) = (" << X << " " << Y << ")" << endl;
	}

};