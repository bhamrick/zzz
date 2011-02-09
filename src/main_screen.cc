#include<main_screen.hh>
#include<menu.hh>
#include<GL/glut.h>
#include<cstdlib>
#include<mode.hh>
#include<display.hh>

menu *main_menu;
overworld *main_overworld;

void init_main_screen(overworld* ow) {
	main_menu = new menu();
	main_menu->add_item(new menu_item("Continue"));
	main_menu->add_item(new menu_item("New game"));
	main_menu->add_item(new menu_item("Options"));
	main_menu->add_item(new menu_item("Quit game"));
	main_menu->set_action_handler(main_menu_action_handler);

	main_overworld = ow;
}

void draw_main_screen() {
//	glClearColor(1.0, 1.0, 1.0, 0.0);
//	glClear(GL_COLOR_BUFFER_BIT);
	draw_background(vec());
	main_menu->draw();
}

void main_menu_action_handler(int index) {
	switch(index) {
		case 0:
			main_overworld->load_save("files/savefile");
			set_mode(OVERWORLD_MODE);
			main_overworld->unpause();
			break;
		case 1:
			main_overworld->new_game();
			set_mode(OVERWORLD_MODE);
			main_overworld->unpause();
			break;
		case 2:
			set_mode(OPTIONS_MODE);
			break;
		case 3:
			exit(0);
			break;
	}
}

void main_menu_key_handler(int key) {
	main_menu->handle_key(key);
}

void main_menu_special_handler(int key) {
	main_menu->handle_special(key);
}
