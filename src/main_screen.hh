#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include<overworld.hh>

void init_main_screen(overworld*);
void draw_main_screen();
void main_menu_action_handler(int);
void main_menu_key_handler(int);
void main_menu_special_handler(int);

#endif
