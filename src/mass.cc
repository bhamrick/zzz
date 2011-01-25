#include<mass.hh>

mass::mass() {
	m = 1.0;
	position = vec();
	momentum = vec();
	fixed = false;
}

mass::mass(double m) {
	this->m = m;
	position = vec();
	momentum = vec();
	fixed = false;
}

mass::mass(double m, vec pos) {
	this->m = m;
	position = pos;
	momentum = vec();
	fixed = false;
}

mass::mass(double m, vec pos, vec mo) {
	this->m = m;
	position = pos;
	momentum = mo;
	fixed = false;
}

mass::mass(double m, vec pos, vec mo, bool fixed) {
	this->m = m;
	position = pos;
	momentum = mo;
	this->fixed = fixed;
	if(fixed) {
		momentum = vec();
	}
}

void mass::update(double dt) {
	if(!fixed) {
		position += momentum*dt/m;
	} else {
		momentum = vec();
	}
}

void mass::impulse(vec I) {
	if(!fixed) {
		momentum += I;
	} else {
		momentum = vec();
	}
}

void mass::fix() {
	fixed = true;
}

void mass::unfix() {
	fixed = false;
}
