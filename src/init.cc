#include<init.hh>
#include<input.hh>
#include<overworld.hh>
#include<world.hh>
#include<update.hh>
#include<spring.hh>
#include<level.hh>
#include<main_screen.hh>
#include<options.hh>
#include<message.hh>
#include<textures.hh>
#include<sound.hh>
#include<cstdio>

bool initialized = false;

void main_init(int value) {
	if(initialized) return;
	initialized = true;

	overworld* ow = new overworld((char*)"files/overworld");
	world* w = new world(ow);

	new input(NULL, w);

	set_options(OPTION_SHOW_TIME);

	init_textures();
	init_main_screen(ow);
	init_options_menu();
	init_global_update(w);
	init_display(w, ow);
	set_mode(MAIN_MODE);

//	init_sound();
}
