#include<cstdlib>
#include<GL/glut.h>
#include<display.hh>
#include<world.hh>
#include<update.hh>
#include<spring.hh>
#include<level.hh>
#include<main_screen.hh>
#include<options.hh>
#include<message.hh>

int main(int argc, char** argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(600,600);
	glutCreateWindow("zzz");
	
	overworld* ow = new overworld((char*)"files/overworld");
	world* w = new world(ow);

	new input(NULL, w);

	set_options(OPTION_SHOW_TIME);

	init_main_screen(ow);
	init_options_menu();
	init_global_update(w);
	init_display(w, ow);
	set_mode(MAIN_MODE);

	init_message("Welcome to ZZZ\n----------------\nUse left and right to\nmove and up to jump");

	glutDisplayFunc(display);
	glutTimerFunc(10,refresh,0);
	glutIdleFunc(global_update);
	glutMainLoop();

	return 0;
}
