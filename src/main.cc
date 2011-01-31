#include<cstdlib>
#include<GL/glut.h>
#include<display.hh>
#include<world.hh>
#include<update.hh>
#include<spring.hh>
#include<level.hh>

int main(int argc, char** argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(600,600);
	glutCreateWindow("zzz");
	
	overworld* ow = new overworld((char*)"files/overworld");
	world* w = new world(ow);

	load((char*)"levels/test",w);
//	load((char*)"levels/parabola",w);

	init_global_update(w);
	init_display(w, ow);
	set_mode(OVERWORLD_MODE);

	glutDisplayFunc(display);
	glutTimerFunc(10,refresh,0);
	glutIdleFunc(global_update);
	glutMainLoop();

	return 0;
}
