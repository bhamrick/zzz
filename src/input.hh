class input;

#ifndef INPUT_H
#define INPUT_H

#include<GL/glut.h>
#include<world.hh>
#include<character.hh>
#include<mode.hh>

class input {
	public:
	vec force;
	character* mover;
	world* env;
	bool jumped;

	input(character*, world*);
	void update(double);
};

void keySpecialDown(int,int,int);
void keySpecialUp(int,int,int);
void keyDown(unsigned char,int,int);
void keyUp(unsigned char,int,int);
void input_set_mode(mode);

#endif
