class world;

#ifndef WORLD_H
#define WORLD_H

#include<mass.hh>
#include<vector>
#include<unistd.h>
#include<sys/time.h>
#include<const.hh>
#include<spring.hh>
#include<character.hh>
#include<input.hh>
#include<view.hh>

class world {
	public:
	std::vector<mass*> masses;
	std::vector<spring*> springs;
	std::vector<character*> characters;
	struct timeval last_update;
	input* input_handler;
	view* main_view;
	bool paused;
	
	vec goal;

	world();
	void update();
	void reset();
	void add_mass(mass*);
	void add_spring(spring*);
	void add_character(character*);
	void pause();
	void unpause();
};

#endif
