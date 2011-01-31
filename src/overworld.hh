class overworld_loc;
class overworld;

#ifndef OVERWORLD_H
#define OVERWORLD_H

#include<vec.hh>
#include<vector>
#include<menu.hh>

class overworld_loc {
	public:
	vec pos;
	char* levelname;
	overworld_loc *up, *right, *down, *left;
	
	overworld_loc();
	overworld_loc(char*);
	void set_neighbor(int, overworld_loc*);
	void set_neighbors(overworld_loc*, overworld_loc*, overworld_loc*, overworld_loc*);
};

class overworld {
	public:
	std::vector<overworld_loc*> locs;
	overworld_loc* current_loc;
	menu* overworld_menu;
	bool paused;

	overworld();
	overworld(char*);
	void add_location(overworld_loc*);
	void draw();
	void set_current_location(overworld_loc*);
	void load(char*);
	void transition(int);
	void pause();
	void unpause();
};

#endif
