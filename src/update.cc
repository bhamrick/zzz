#include<update.hh>
#include<cstdio>

world* global_update_world;

void global_update() {
	global_update_world->update();
}

void init_global_update(world* w) {
	global_update_world = w;
}
