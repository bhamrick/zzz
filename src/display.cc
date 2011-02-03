#include<cstdlib>
#include<GL/glut.h>
#include<display.hh>
#include<cstdio>
#include<const.hh>
#include<cstring>
#include<ctype.h>
#include<main_screen.hh>
#include<options.hh>

world* display_world;
overworld* display_overworld;
mode display_mode;

void display() {
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
	}
	glFlush();
	glutSwapBuffers();
}

void init_display(world* w, overworld* ow) {
	display_world = w;
	display_overworld = ow;
	display_mode = OVERWORLD_MODE;
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
	glRasterPos2d(x,y-dy);
	for(int i = 0; i<strlen(s); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (s[i] == '_' ? ' ' : toupper(s[i])));
	}
	glPopMatrix();
}

double line_height() {
	return 50./glutGet(GLUT_WINDOW_HEIGHT);
}
