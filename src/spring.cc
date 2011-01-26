#include<spring.hh>

spring::spring(mass* a, mass* b) {
	m1 = a;
	m2 = b;
	k = 1.0;
	d = (m1->position - m2->position).norm();
}

spring::spring(mass* a, mass* b, double k) {
	m1 = a;
	m2 = b;
	this->k = k;
	d = (m1->position - m2->position).norm();
}

spring::spring(mass* a, mass* b, double k, double d) {
	m1 = a;
	m2 = b;
	this->k = k;
	this->d = d;
}

void spring::update(double dt) {
	vec L = m2->position - m1->position;
	m1->impulse(k*L*dt);
	m2->impulse(-k*L*dt);
}

void spring::impulse(vec pos, vec I) {
	double d1 = (m1->position - pos).norm(), d2 = (m2->position - pos).norm();
	m1->impulse(I*d2/(d1+d2));
	m2->impulse(I*d1/(d1+d2));
}

void spring::reset() {
	m1->reset();
	m2->reset();
}
