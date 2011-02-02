#ifndef MODE_H
#define MODE_H

enum mode {WORLD_MODE, OVERWORLD_MODE};

#include<display.hh>
#include<update.hh>
#include<input.hh>

void set_mode(mode);

#endif
