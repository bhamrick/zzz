#ifndef MENU_H
#define MENU_H

#include<vector>

class menu_item {
	public:
	char* text;

	menu_item();
	menu_item(char*);
};

class menu {
	public:
	std::vector<menu_item*> items;
	void (*action_handler)(int);
	int current_index;

	menu();
	menu(void(*)(int));
	void draw();
	void add_item(menu_item*);
	void handle_special(int);
	void handle_key(unsigned char);
	void set_action_handler(void(*)(int));
};

#endif
