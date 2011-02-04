#ifndef MODE_H
#define MODE_H

enum mode {MAIN_MODE, WORLD_MODE, OVERWORLD_MODE, OPTIONS_MODE, MESSAGE_MODE};

#include<display.hh>
#include<update.hh>
#include<input.hh>

void set_mode(mode);
mode get_current_mode();

#endif
