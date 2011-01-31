#include<input.hh>
#include<cstdio>

input* main_input;
mode input_mode;

input::input(character* c, world* w) {
	main_input = this;
	mover = c;
	force = vec();
	env = w;
	over = w->over;
	jumped = false;

	glutSpecialFunc(keySpecialDown);
	glutSpecialUpFunc(keySpecialUp);

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
}

void input::update(double dt) {
	mover->impulse(force*dt);
}

void keyDown(unsigned char key, int x, int y) {
	switch(input_mode) {

	case WORLD_MODE:
		switch(key) {
			case 27: // ESC
				if(main_input->env->paused) {
					main_input->env->unpause();
				} else {
					main_input->env->pause();
				}
				break;
			case 'r':
				main_input->env->reset();
				break;
		}
		break;

	case OVERWORLD_MODE:
		switch(key) {
			case ' ':
			case '\n':
			case '\r':
				char fname[50];
				sprintf(fname,"levels/%s",main_input->over->current_loc->levelname);
				load(fname, main_input->env);
				set_mode(WORLD_MODE);
				break;
		}
		break;

	}
}

void keyUp(unsigned char key, int x, int y) {
	switch(input_mode) {

	case WORLD_MODE:
		switch(key) {
		}
		break;
	
	case OVERWORLD_MODE:
		switch(key) {
		}
		break;
	
	}
}

void keySpecialDown(int key, int x, int y) {
	switch(input_mode) {

	case WORLD_MODE:
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
				vec premo = main_input->mover->momentum;
				for(std::vector<spring*>::iterator iter = main_input->env->springs.begin(); iter != main_input->env->springs.end(); iter++) {
					main_input->mover->jump(*iter);
					if(main_input->mover->momentum != premo) {
						break;
					}
				}
				break;
		}
		break;
	
	case OVERWORLD_MODE:
		switch(key) {
			case GLUT_KEY_UP:
				main_input->over->transition(0);
				break;
			case GLUT_KEY_RIGHT:
				main_input->over->transition(1);
				break;
			case GLUT_KEY_DOWN:
				main_input->over->transition(2);
				break;
			case GLUT_KEY_LEFT:
				main_input->over->transition(3);
				break;
		}
		break;

	}
}

void keySpecialUp(int key, int x, int y) {
	switch(input_mode) {
	
	case WORLD_MODE:
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
		break;
	
	case OVERWORLD_MODE:
		switch(key) {
			
		}
		break;
	
	}
}

void input_set_mode(mode m) {
	input_mode = m;
}
