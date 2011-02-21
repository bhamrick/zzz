class input;

#ifndef INPUT_H
#define INPUT_H

#include<GL/glut.h>
#include<world.hh>
#include<character.hh>
#include<mode.hh>
#include<overworld.hh>
#include<level.hh>

class input {
	public:
	vec force;
	char keymask;
	character* mover;
	world* env;
	overworld* over;
	bool jumped;

	input(character*, world*);
	void update(double);
};

void keySpecialDown(int,int,int);
void keySpecialUp(int,int,int);
void keyDown(unsigned char,int,int);
void keyUp(unsigned char,int,int);
void input_set_mode(mode);

void world_menu_handler(int);
void overworld_menu_handler(int);

#endif
