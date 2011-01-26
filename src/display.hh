#ifndef DISPLAY_H
#define DISPLAY_H

#include<world.hh>

void refresh(int);
void display();
void init_display(world*);
void draw_circle(vec,double);
void draw_goal(vec);

#endif
