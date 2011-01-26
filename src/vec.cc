#include<vec.hh>
#include<cmath>

vec::vec() {
	x = y = 0;
}

vec::vec(double x, double y) {
	this->x = x;
	this->y = y;
}

vec vec::operator+(vec o) {
	return vec(x+o.x, y+o.y);
}

vec& vec::operator+=(vec o) {
	x += o.x;
	y += o.y;
	return *this;
}

vec& vec::operator=(vec o) {
	x = o.x;
	y = o.y;
	return *this;
}

vec vec::operator-(vec o) {
	return vec(x - o.x, y - o.y);
}

vec& vec::operator-=(vec o) {
	x -= o.x;
	y -= o.y;
	return *this;
}

vec vec::operator-() {
	return vec(-x,-y);
}

vec& vec::operator*=(double s) {
	x *= s;
	y *= s;
	return *this;
}

vec operator*(double s, vec v) {
	return vec(v.x*s, v.y*s);
}

vec operator*(vec v, double s) {
	return vec(v.x*s, v.y*s);
}

vec vec::operator/(double s) {
	return vec(x/s,y/s);
}

double vec::norm() {
	return sqrt(x*x + y*y);
}

double vec::dot(vec o) {
	return x*o.x + y*o.y;
}

bool vec::operator==(vec o) {
	return x == o.x && y == o.y;
}

bool vec::operator!=(vec o) {
	return x != o.x || y != o.y;
}
