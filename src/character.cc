#include<character.hh>
#include<cstdlib>
#include<cstdio>
#include<cmath>

character::character(double r, double m, vec pos) {
	radius = r;
	mass = m;
	position = pos;
	momentum = vec();
	ipos = position;
	imo = momentum;
}

character::character(double r, double m, vec pos, vec mo) {
	radius = r;
	mass = m;
	position = pos;
	momentum = mo;
	ipos = position;
	imo = momentum;
}

void character::impulse(vec I) {
	momentum += I/mass;
}

bool between(vec a, vec b, vec c) {
	//return if a is between b and c
	return (b-a).dot(c-a) < 0;
}

void character::collide(spring* s) {
	vec L = s->m2->position - s->m1->position;
	vec uL = L/L.norm();
	vec v = position - s->m1->position;
	vec w = v.dot(uL)*uL;
	vec nr = w - v;
	vec r = nr/nr.norm() * radius;
	vec ur = r/r.norm();
	vec contact = position + nr;
	if(nr.norm() < radius && between(contact,s->m1->position,s->m2->position)) {
		double alpha = (contact - s->m1->position).norm(), beta = (contact - s->m2->position).norm();
		vec spring_momentum = ((alpha*s->m1->momentum + beta*s->m2->momentum)/(alpha+beta)).dot(ur)*ur;
		vec total_momentum = momentum.dot(ur)*ur + spring_momentum;
		vec new_vel = total_momentum / (mass + s->m1->m + s->m2->m);
		impulse(mass*new_vel - momentum.dot(ur)*ur);
		s->impulse(contact,(s->m1->m + s->m2->m)*new_vel - spring_momentum);
		position = position + nr - r;
	}
}

void character::jump(spring* s) {
	vec L = s->m2->position - s->m1->position;
	vec uL = L/L.norm();
	vec v = position - s->m1->position;
	vec w = v.dot(uL)*uL;
	vec nr = w - v;
	vec r = nr/nr.norm() * radius;
	vec ur = r/r.norm();
	vec contact = position + nr;
	collide(s);
	if(nr.norm() < radius + 1e-2 && between(contact,s->m1->position,s->m2->position)) {
		impulse(-3*ur);
		s->impulse(contact,3*ur);
		position = position + nr - (1+1e-6)*r;
	}
}

void character::update(double dt) {
	position += momentum/mass*dt;
}

void character::reset() {
	position = ipos;
	momentum = imo;
}
