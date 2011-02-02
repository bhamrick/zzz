#include<menu.hh>
#include<GL/glut.h>
#include<display.hh>
#include<cstring>

menu_item::menu_item() {
	text = NULL;
}

menu_item::menu_item(char* s) {
	text = s;
}

menu::menu() {
	action_handler = NULL;
	current_index = 0;
}

menu::menu(void (*ah)(int)) {
	action_handler = ah;
}

void menu::draw() {
	glPushMatrix();
	glLoadIdentity();
	double lh = line_height();
	double eps = 1e-2;

	int longest_string = 0;
	for(int i = 0; i<items.size(); i++) {
		int tlen = strlen(items[i]->text);
		if(tlen > longest_string) {
			longest_string = tlen;
		}
	}
	
	double menu_width = lh*(longest_string + 1);
	double menu_height = lh*(items.size());

	glColor3f(0.0,0.0,1.0);
	glBegin(GL_QUADS);
		glVertex2f(-menu_width/2.,-menu_height/2.);
		glVertex2f( menu_width/2.,-menu_height/2.);
		glVertex2f( menu_width/2., menu_height/2.);
		glVertex2f(-menu_width/2., menu_height/2.);
	glEnd();

	glColor3f(1.0,1.0,1.0);
	for(int i = 0; i<items.size(); i++) {
		draw_string(-menu_width/2. + lh,menu_height/2.-lh*i,items[i]->text);
	}

	glBegin(GL_TRIANGLES);
		glVertex2f(-menu_width/2 + eps, menu_height/2.-lh*current_index-eps);
		glVertex2f(-menu_width/2 + eps, menu_height/2.-lh*(current_index+1)+eps);
		glVertex2f(-menu_width/2 + lh - eps, menu_height/2.-lh*(current_index + 0.5));
	glEnd();
	glPopMatrix();
}

void menu::add_item(menu_item* i) {
	items.push_back(i);
}

void menu::handle_special(int key) {
	switch(key) {
		case GLUT_KEY_UP:
			current_index--;
			if(current_index < 0) {
				current_index += items.size();
			}
			break;
		case GLUT_KEY_DOWN:
			current_index++;
			if(current_index >= items.size()) {
				current_index -= items.size();
			}
			break;
	}
}

void menu::handle_key(unsigned char key) {
	switch(key) {
		case '\r':
		case ' ':
			(*action_handler)(current_index);
			break;
	}
}

void menu::set_action_handler(void (*ah)(int)) {
	action_handler = ah;
}
