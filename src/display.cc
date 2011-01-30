#include<cstdlib>
#include<GL/glut.h>
#include<display.hh>
#include<cstdio>
#include<const.hh>

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
