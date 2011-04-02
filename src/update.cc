#include<update.hh>
#include<init.hh>
#include<cstdio>

world* global_update_world;
mode update_mode;

void global_update() {
//	printf("foo\n");
	switch(update_mode) {
		case WORLD_MODE:
			global_update_world->update();
			break;
	}
}

void update_set_mode(mode m) {
	update_mode = m;
}

void init_global_update(world* w) {
	global_update_world = w;
}
