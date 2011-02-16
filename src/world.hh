class world;
class world_message;

#ifndef WORLD_H
#define WORLD_H

#include<mass.hh>
#include<vector>
#include<queue>
#include<unistd.h>
#include<sys/time.h>
#include<const.hh>
#include<spring.hh>
#include<character.hh>
#include<input.hh>
#include<view.hh>
#include<display.hh>
#include<overworld.hh>
#include<menu.hh>

class world {
	public:
	std::vector<mass*> masses;
	std::vector<spring*> springs;
	std::vector<character*> characters;
	character* player;
	struct timeval last_update;
	overworld* over;
	menu* world_menu;
	input* input_handler;
	view* main_view;
	vec bg_center;
	bool paused;
	double timestamp;
	
	vec goal;
	
	world(overworld*);
	void update();
	void reset();
	void add_mass(mass*);
	void add_spring(spring*);
	void add_character(character*);
	void queue_message(world_message*);
	void pause();
	void unpause();
	void draw();
	void draw_goal();
	void win();
};

#endif
