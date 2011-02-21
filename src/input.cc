#include<input.hh>
#include<cstdio>
#include<cstdlib>
#include<main_screen.hh>
#include<options.hh>
#include<message.hh>

input* main_input;
mode input_mode;

input::input(character* c, world* w) {
	main_input = this;
	keymask = 0;
	mover = c;
	force = vec();
	env = w;
	over = w->over;
	jumped = false;

	env->world_menu->set_action_handler(world_menu_handler);
	over->overworld_menu->set_action_handler(overworld_menu_handler);

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
		if(main_input->env->paused) {
			main_input->env->world_menu->handle_key(key);
		}
		break;

	case OVERWORLD_MODE:
		switch(key) {
			case 27:
				if(main_input->over->paused) {
					main_input->over->unpause();
				} else {
					main_input->over->pause();
				}
				break;
			case ' ':
			case '\n':
			case '\r':
				if(!main_input->over->paused) {
					char fname[50];
					sprintf(fname,"levels/%s",main_input->over->current_loc->levelname);
					load(fname, main_input->env);
					set_mode(WORLD_MODE);
				}
				break;
		}
		if(main_input->over->paused) {
			main_input->over->overworld_menu->handle_key(key);
		}
		break;
	
	case MAIN_MODE:
		main_menu_key_handler(key);
		break;
	
	case OPTIONS_MODE:
		options_menu_key_handler(key);
		break;

	case MESSAGE_MODE:
		restore_state();
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
				main_input->keymask |= 1;
				break;
			case GLUT_KEY_RIGHT:
				main_input->force += vec(3.0,0.0);
				main_input->keymask |= 2;
				break;
			case GLUT_KEY_UP:
				if(main_input->env->paused) break;
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
		if(main_input->env->paused) {
			main_input->env->world_menu->handle_special(key);
		}
		break;
	
	case OVERWORLD_MODE:
		if(main_input->over->paused) {
			main_input->over->overworld_menu->handle_special(key);
		} else {
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
		}
		break;

	case MAIN_MODE:
		main_menu_special_handler(key);
		break;
	
	case OPTIONS_MODE:
		options_menu_special_handler(key);
		break;
	
	case MESSAGE_MODE:
		restore_state();
		break;

	}
}

void keySpecialUp(int key, int x, int y) {
	switch(input_mode) {
	
	case WORLD_MODE:
		switch(key) {
			case GLUT_KEY_LEFT:
				if(main_input->keymask & 1) {
					main_input->force += vec(3.0,0.0);
				}
				main_input->keymask &= ~1;
				break;
			case GLUT_KEY_RIGHT:
				if(main_input->keymask & 2) {
					main_input->force += vec(-3.0,0.0);
				}
				main_input->keymask &= ~2;
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
	if(m == WORLD_MODE) {
		main_input->force = vec();
		main_input->keymask = 0;
	}
}

void world_menu_handler(int action) {
	switch(action) {
		case 0:
			main_input->env->unpause();
			break;
		case 1:
			main_input->env->unpause();
			main_input->env->reset();
			break;
		case 2:
			main_input->env->unpause();
			set_mode(OVERWORLD_MODE);
			break;
	}
}

void overworld_menu_handler(int action) {
	switch(action) {
		case 0:
			main_input->over->unpause();
			break;
		case 1:
			main_input->over->write_save("files/savefile");
			main_input->over->unpause();
			push_message("\nYour progress\nhas been saved.\n");
			break;
		case 2:
			set_mode(MAIN_MODE);
			break;
	}
}
