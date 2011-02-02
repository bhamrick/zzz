#include<update.hh>
#include<cstdio>

world* global_update_world;
mode update_mode;

void global_update() {
	if(update_mode == WORLD_MODE) {
		global_update_world->update();
	}
}

void update_set_mode(mode m) {
	update_mode = m;
}

void init_global_update(world* w) {
	global_update_world = w;
}
