#include<cstdlib>
#include<GL/glut.h>
#include<display.hh>
#include<cstdio>
#include<const.hh>

world* display_world;

void display() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(-(display_world->main_view->minx + display_world->main_view->maxx)/2., -(display_world->main_view->miny + display_world->main_view->maxy)/2., 0.0);

	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0,0.0,0.0);

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	for(std::vector<mass*>::iterator iter = display_world->masses.begin(); iter != display_world->masses.end(); iter++) {
		double x = (*iter)->position.x, y = (*iter)->position.y;
		double eps = 1e-2;
		glVertex2f(x-eps,y-eps);
		glVertex2f(x+eps,y-eps);
		glVertex2f(x+eps,y+eps);
		glVertex2f(x-eps,y+eps);
	}
	glEnd();

	glBegin(GL_LINES);
	for(std::vector<spring*>::iterator iter = display_world->springs.begin(); iter != display_world->springs.end(); iter++) {
		glVertex2f((*iter)->m1->position.x,(*iter)->m1->position.y);
		glVertex2f((*iter)->m2->position.x,(*iter)->m2->position.y);
	}
	glEnd();

	for(std::vector<character*>::iterator iter = display_world->characters.begin(); iter != display_world->characters.end(); iter++) {
		draw_circle((*iter)->position,(*iter)->radius);
//		glBegin(GL_LINES);
//			glVertex2f((*iter)->position.x, (*iter)->position.y);
//			glVertex2f((*iter)->position.x - 0.05*(*iter)->momentum.x, (*iter)->position.y - 0.05*(*iter)->momentum.y);
//		glEnd();
	}

	draw_goal(display_world->goal);

	glFlush();
	glutSwapBuffers();
}

void init_display(world* w) {
	display_world = w;
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

void draw_goal(vec center) {
	double radius = 0.03;
	glBegin(GL_LINES);
	for(int i = 0; i<5; i++) {
		glVertex2f(center.x + radius*sin(2*pi*i/5), center.y+radius*cos(2*pi*i/5));
		glVertex2f(center.x + radius*sin(2*pi*(i+2)/5), center.y + radius*cos(2*pi*(i+2)/5));
	}
	glEnd();
}
