#include<input.hh>

input* main_input;

input::input(character* c, world* w) {
	main_input = this;
	mover = c;
	force = vec();
	env = w;
	jumped = false;

	glutSpecialFunc(keySpecialDown);
	glutSpecialUpFunc(keySpecialUp);
}

void input::update(double dt) {
	mover->impulse(force*dt);
}

void keySpecialDown(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT:
			main_input->force += vec(-3.0,0.0);
			break;
		case GLUT_KEY_RIGHT:
			main_input->force += vec(3.0,0.0);
			break;
		case GLUT_KEY_UP:
			if(main_input->jumped) break;
			main_input->jumped = true;
			for(std::vector<spring*>::iterator iter = main_input->env->springs.begin(); iter != main_input->env->springs.end(); iter++) {
				main_input->mover->jump(*iter);
			}
			break;
	}
}

void keySpecialUp(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT:
			main_input->force += vec(3.0,0.0);
			break;
		case GLUT_KEY_RIGHT:
			main_input->force += vec(-3.0,0.0);
			break;
		case GLUT_KEY_UP:
			main_input->jumped = false;
			break;
	}
}
