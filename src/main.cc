#include<cstdlib>
#include<GL/glut.h>
#include<display.hh>
#include<world.hh>
#include<update.hh>
#include<spring.hh>

int main(int argc, char** argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(600,600);
	glutCreateWindow("zzz");
	
	world* w = new world();
	mass* m[4];
	m[0] = new mass(1.0,vec(-0.5,0.0),vec(),true);
	m[1] = new mass(1.0,vec(-0.5 + 1/3.0,0.0),vec(),false);
	m[2] = new mass(1.0,vec(-0.5 + 2/3.0,0.0),vec(),false);
	m[3] = new mass(1.0,vec(0.5,0.0),vec(),true);
	w->add_mass(m[0]);
	w->add_mass(m[1]);
	w->add_mass(m[2]);
	w->add_mass(m[3]);
	w->add_spring(new spring(m[0],m[1],200));
	w->add_spring(new spring(m[1],m[2],200));
	w->add_spring(new spring(m[2],m[3],200));

	mass *w1 = new mass(1.0,vec(-0.5,0.5),vec(),true), *w2 = new mass(1.0,vec(0.5,0.5),vec(),true);
	w->add_mass(w1);
	w->add_mass(w2);
	w->add_spring(new spring(m[0],w1));
	w->add_spring(new spring(m[3],w2));

	character* player = new character(0.03,1.0,vec(0.45,0.1));
	w->add_character(player);
	w->input_handler = new input(player,w);

	init_global_update(w);
	init_display(w);

	glutDisplayFunc(display);
	glutTimerFunc(10,refresh,0);
	glutIdleFunc(global_update);
	glutMainLoop();

	return 0;
}
