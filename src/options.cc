#include<options.hh>
#include<menu.hh>
#include<GL/glut.h>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<mode.hh>

int options;
menu *options_menu;

void set_option(int opt, int state) {
	if(state) {
		options |= opt;
	} else {
		options &= ~opt;
	}
}

void set_options(int opts) {
	options = opts;
}

bool is_option_set(int opt) {
	return (bool)(options & opt);
}

void init_options_menu() {
	options_menu = new menu();
	char* item_text_1 = new char[15];
	sprintf(item_text_1,"Show timer: %s",is_option_set(OPTION_SHOW_TIME) ? "yes" : "no");
	options_menu->add_item(new menu_item(item_text_1));

	options_menu->add_item(new menu_item("Return"));
	
	options_menu->set_action_handler(options_menu_action_handler);
}

void options_menu_key_handler(int key) {
	options_menu->handle_key(key);
	if(key == 27) {
		set_mode(MAIN_MODE);
	}
}

void options_menu_special_handler(int key) {
	options_menu->handle_special(key);
}

void options_menu_action_handler(int index) {
	switch(index) {
		case 0:
			set_option(OPTION_SHOW_TIME, !is_option_set(OPTION_SHOW_TIME));
			sprintf(options_menu->items[0]->text,"show timer: %s", is_option_set(OPTION_SHOW_TIME) ? "yes" : "no");
			break;

		default:
			set_mode(MAIN_MODE);
			break;
	}
}

void draw_options_screen() {
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	options_menu->draw();
}
