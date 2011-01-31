#include<mass.hh>

mass::mass() {
	m = 1.0;
	position = vec();
	momentum = vec();
	ipos = position;
	imo = momentum;
	fixed = 0;
}

mass::mass(double m) {
	this->m = m;
	position = vec();
	momentum = vec();
	ipos = position;
	imo = momentum;
	fixed = 0;
}

mass::mass(double m, vec pos) {
	this->m = m;
	position = pos;
	momentum = vec();
	ipos = position;
	imo = momentum;
	fixed = 0;
}

mass::mass(double m, vec pos, vec mo) {
	this->m = m;
	position = pos;
	momentum = mo;
	ipos = position;
	imo = momentum;
	fixed = 0;
}

mass::mass(double m, vec pos, vec mo, int fixed) {
	this->m = m;
	position = pos;
	momentum = mo;
	this->fixed = fixed;
	switch(fixed) {
		case 1:
			momentum = vec();
			break;
		case 2:
			momentum.x = 0;
			break;
		case 3:
			momentum.y = 0;
			break;
	}
	ipos = position;
	imo = momentum;
}

void mass::update(double dt) {
	switch(fixed) {
		case 1:
			momentum = vec();
			break;
		case 2:
			momentum.x = 0;
			break;
		case 3:
			momentum.y = 0;
			break;
	}
	position += momentum*dt/m;
}

void mass::impulse(vec I) {
	momentum += I;
	switch(fixed) {
		case 1:
			momentum = vec();
			break;
		case 2:
			momentum.x = 0;
			break;
		case 3:
			momentum.y = 0;
			break;
	}
}

void mass::fix() {
	fixed = 1;
}

void mass::unfix() {
	fixed = 0;
}

void mass::reset() {
	position = ipos;
	momentum = imo;
}
