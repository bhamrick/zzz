#include<world.hh>
#include<cstdio>

world::world() {
	gettimeofday(&last_update, NULL);
}

void world::update() {
	struct timeval now;
	gettimeofday(&now, NULL);
	double dt = now.tv_sec - last_update.tv_sec + 1e-6*(now.tv_usec - last_update.tv_usec);
	input_handler->update(dt);
	// Springs
	for(std::vector<spring*>::iterator iter = springs.begin(); iter != springs.end(); iter++) {
		(*iter)->update(dt);
	}
	for(std::vector<character*>::iterator iter = characters.begin(); iter != characters.end(); iter++) {
		// Check for character collisions with springs
		for(std::vector<spring*>::iterator it = springs.begin(); it != springs.end(); it++) {
			(*iter)->collide(*it,dt);
		}
		// Gravity
		(*iter)->impulse(g*dt*((*iter)->mass));
		// Update
		(*iter)->update(dt);
	}
	for(std::vector<mass*>::iterator iter = masses.begin(); iter != masses.end(); iter++) {
		// Gravity
		(*iter)->impulse(g*dt*((*iter)->m));
		// Update
		(*iter)->update(dt);
	}
	last_update = now;
}

void world::add_mass(mass* m) {
	masses.push_back(m);
}

void world::add_spring(spring* s) {
	springs.push_back(s);
}

void world::add_character(character* c) {
	characters.push_back(c);
}
