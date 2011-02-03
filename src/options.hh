#ifndef OPTIONS_H
#define OPTIONS_H

const int OPTION_SHOW_TIME = 0x01;

void set_option(int,int);
void set_options(int);
bool is_option_set(int);
void init_options_menu();
void options_menu_key_handler(int);
void options_menu_special_handler(int);
void options_menu_action_handler(int);
void draw_options_screen();

#endif
