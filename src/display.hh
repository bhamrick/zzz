#ifndef DISPLAY_H
#define DISPLAY_H

#include<world.hh>
#include<overworld.hh>
#include<mode.hh>

void refresh(int);
void display();
void init_display(world*, overworld*);
void draw_circle(vec,double);
void draw_goal(vec);
void display_set_mode(mode);
void draw_string(vec,char*);
void draw_string(double, double, char*);
double line_height();

#endif
