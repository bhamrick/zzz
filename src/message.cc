#include<message.hh>
#include<display.hh>
#include<GL/glut.h>
#include<mode.hh>
#include<cstring>
#include<ctype.h>
#include<cstdio>

char* message;
mode old_mode;

void init_message(char* s) {
	old_mode = get_current_mode();
	message = s;
	set_mode(MESSAGE_MODE);
}

void restore_state() {
	set_mode(old_mode);
}

void draw_message() {
	double window_width = (double)glutGet(GLUT_WINDOW_WIDTH);
	double window_height = (double)glutGet(GLUT_WINDOW_HEIGHT);
	double mw = 0.0, mh = 40.0/window_height, lw = 0.0;
	for(int i = 0; i<strlen(message); i++) {
		if(message[i] == 10) {
			if(lw > mw) mw = lw;
			lw = 0.0;
			mh += (double)40./window_height;
		} else {
			lw += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, message[i] == '_' ? ' ' : toupper(message[i])) / (window_width/2.);
		}
	}
	if(lw > mw) {
		mw = lw;
	}
	
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_QUADS);
		glVertex2f(-(mw/2. + 0.01), -(mh/2. + 0.01));
		glVertex2f((mw/2. + 0.01), -(mh/2. + 0.01));
		glVertex2f((mw/2. + 0.01), (mh/2. + 0.01));
		glVertex2f(-(mw/2. + 0.01), (mh/2. + 0.01));
	glEnd();

	glColor3f(1.0,1.0,1.0);
	draw_string(-mw/2.,mh/2.,message);
	glPopMatrix();
}
