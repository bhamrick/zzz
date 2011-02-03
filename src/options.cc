#include<options.hh>
#include<menu.hh>

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
}

void options_menu_key_handler(int key) {
	options_menu->handle_key(key);
}

void options_menu_special_handler(int key) {
	options_menu->handle_special(key);
}

void options_menu_action_handler(int index) {
	switch(index) {
		
	}
}

void draw_options_screen() {
	
}
