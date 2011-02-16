#include<cstdlib>
#include<GL/glut.h>
#include<display.hh>
#include<cstdio>
#include<const.hh>
#include<cstring>
#include<ctype.h>
#include<main_screen.hh>
#include<options.hh>
#include<message.hh>
#include<textures.hh>

world* display_world;
overworld* display_overworld;
mode display_mode;
bool ready_for_next_message = 0;

void display() {
	if(display_mode != MESSAGE_MODE) {
		char* m = front_message();
		if(m) {
			if(ready_for_next_message) {
				init_message(m);
				pop_message();
				ready_for_next_message = 0;
			} else {
				ready_for_next_message = 1;
			}
		} else {
			ready_for_next_message = 0;
		}
	}
	switch(display_mode) {
		case WORLD_MODE:
			display_world->draw();
			break;
		case OVERWORLD_MODE:
			display_overworld->draw();
			break;
		case MAIN_MODE:
			draw_main_screen();
			break;
		case OPTIONS_MODE:
			draw_options_screen();
			break;
		case MESSAGE_MODE:
			draw_message();
			break;
	}
	glFlush();
	glutSwapBuffers();
}

void init_display(world* w, overworld* ow) {
	display_world = w;
	display_overworld = ow;
	display_mode = OVERWORLD_MODE;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void refresh(int value) {
	glutPostRedisplay();
	glutTimerFunc(10,refresh,0);
}

void draw_circle(vec center, double radius) {
	int N = 180;
	glBegin(GL_LINES);
	for(int i = 0; i<N; i++) {
		glVertex2f(center.x + radius*cos(2*pi*i/N), center.y + radius*sin(2*pi*i/N));
		glVertex2f(center.x + radius*cos(2*pi*(i+1)/N), center.y + radius*sin(2*pi*(i+1)/N));
	}
	glEnd();
}

void draw_player(vec center, double radius) {
	use_player_texture();
	double x = center.x, y = center.y;
	double eps = 5*radius;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0); glVertex2f(x-eps,y-eps);
	glTexCoord2f(1.0,0.0); glVertex2f(x+eps,y-eps);
	glTexCoord2f(1.0,1.0); glVertex2f(x+eps,y+eps);
	glTexCoord2f(0.0,1.0); glVertex2f(x-eps,y+eps);
	glEnd();
	end_texture();
}

void display_set_mode(mode m) {
	display_mode = m;
}

void draw_string(vec pos, char* s) {
	draw_string(pos.x, pos.y, s);
}

void draw_string(double x, double y, char* s) {
	glPushMatrix();
	glLoadIdentity();
	double dy = 40./glutGet(GLUT_WINDOW_HEIGHT);
	double line_skip = (double)40./glutGet(GLUT_WINDOW_HEIGHT);
	glRasterPos2d(x,y-dy);
	int line = 0;
	for(int i = 0; i<strlen(s); i++) {
		if(s[i] == '\n') {
			line++;
			glRasterPos2d(x,y-dy-line*line_skip);
		} else {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (s[i] == '_' ? ' ' : toupper(s[i])));
		}
	}
	glPopMatrix();
}

double string_width(char* s) {
	double w = 0.0;
	int window_width = glutGet(GLUT_WINDOW_WIDTH);
	for(int i = 0; i<strlen(s); i++) {
		w += (double)glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, (s[i]=='_' ? ' ' : toupper(s[i]))) / (window_width/2.0);
	}
	return w;
}

double line_height() {
	return 50./glutGet(GLUT_WINDOW_HEIGHT);
}

void draw_background(vec center) {
	double eps = 1/16.;
	use_background_texture();
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_QUADS);
	glTexCoord2f(center.x - eps, center.y - eps); glVertex2f(-1.0,-1.0);
	glTexCoord2f(center.x + eps, center.y - eps); glVertex2f( 1.0,-1.0);
	glTexCoord2f(center.x + eps, center.y + eps); glVertex2f( 1.0, 1.0);
	glTexCoord2f(center.x - eps, center.y + eps); glVertex2f(-1.0, 1.0);
	glEnd();
	glPopMatrix();
	end_texture();
}
