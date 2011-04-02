#include<cstdlib>
#include<GL/glut.h>
#include<display.hh>

int main(int argc, char** argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(600,600);
	glutCreateWindow("zzz");

	set_mode(LOADING_MODE);
	
	glutDisplayFunc(display);
	glutTimerFunc(0,refresh,0);
	//glutTimerFunc(10,global_update,0);
	glutIdleFunc(global_update);
	glutMainLoop();

	return 0;
}
