#include<overworld.hh>
#include<display.hh>
#include<GL/glut.h>
#include<cstring>
#include<cstdio>
#include<ctype.h>
#include<cstdlib>

overworld_loc::overworld_loc() {
	levelname = NULL;
	cleared = false;
}

overworld_loc::overworld_loc(char* n) {
	levelname = n;
	cleared = false;
}

void overworld_loc::set_neighbor(int d, overworld_loc* n) {
	switch(d) {
		case 0:
			up = n;
			break;
		case 1:
			right = n;
			break;
		case 2:
			down = n;
			break;
		case 3:
			left = n;
			break;
	}
}

void overworld_loc::set_neighbors(overworld_loc *u, overworld_loc *r, overworld_loc *d, overworld_loc *l) {
	up = u;
	right = r;
	down = d;
	left = l;
}

bool overworld_loc::unlocked() {
	for(std::vector<overworld_loc*>::iterator iter = prereqs.begin(); iter != prereqs.end(); iter++) {
		if(!(*iter)->cleared) {
			return false;
		}
	}
	return true;
}

void overworld_loc::add_prereq(overworld_loc* p) {
	prereqs.push_back(p);
}

overworld::overworld() {
	current_loc = NULL;
	overworld_menu = new menu();
	overworld_menu->add_item(new menu_item((char*)"Return to game"));
	overworld_menu->add_item(new menu_item((char*)"Save"));
	overworld_menu->add_item(new menu_item((char*)"Quit game"));
	paused = false;
}

overworld::overworld(char* fname) {
	load(fname);
	overworld_menu = new menu();
	overworld_menu->add_item(new menu_item((char*)"Return to game"));
	overworld_menu->add_item(new menu_item((char*)"Save"));
	overworld_menu->add_item(new menu_item((char*)"Quit game"));
	paused = false;
}

void overworld::add_location(overworld_loc* l) {
	locs.push_back(l);
}

void overworld::draw() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

//	glClearColor(1.0,1.0,1.0,0.0);
//	glColor3f(0.0,0.0,0.0);
//
//	glClear(GL_COLOR_BUFFER_BIT);

	draw_background(vec());

	glColor3f(1.0,1.0,1.0);
	
	glBegin(GL_QUADS);
		for(std::vector<overworld_loc*>::iterator iter = locs.begin(); iter != locs.end(); iter++) {
			if((*iter)->unlocked()) {
				if((*iter)->cleared) {
					glColor3f(0.0,1.0,0.0);
				} else {
					glColor3f(1.0,0.0,0.0);
				}
				double eps = 1e-2;
				double x = (*iter)->pos.x, y = (*iter)->pos.y;
				glVertex2f(x-eps,y-eps);
				glVertex2f(x+eps,y-eps);
				glVertex2f(x+eps,y+eps);
				glVertex2f(x-eps,y+eps);
			}
		}
	glEnd();

	glColor3f(1.0,1.0,1.0);

	draw_circle(current_loc->pos, 0.03);
	
	draw_string(-0.99, 0.99, current_loc->levelname);
	if(current_loc->cleared) {
		char recordstr[20];
		sprintf(recordstr,"Best time: %.2lf",current_loc->record);
		draw_string(-0.99, 0.99-line_height(), recordstr);
	}

	if(paused) {
		overworld_menu->draw();
	}

	glPopMatrix();
}

void overworld::set_current_location(overworld_loc* l) {
	current_loc = l;
}

void overworld::load(char* fname) {
	int N, S;
	FILE *fin = fopen(fname,"r");
	if(!fin) {
		printf("Overworld file not found\n");
		exit(1);
		return;
	}
	fscanf(fin,"%d%d",&N,&S);
	for(int i = 0; i<N; i++) {
		add_location(new overworld_loc());
	}
	starting_loc = locs[S];
	for(int i = 0; i<N; i++) {
		locs[i]->levelname = new char[17];
		int u, r, d, l;
		fscanf(fin,"%s%lf%lf%d%d%d%d",locs[i]->levelname,&(locs[i]->pos.x),&(locs[i]->pos.y),&u,&r,&d,&l);
		locs[i]->set_neighbors(u == -1 ? NULL : locs[u],
				      r == -1 ? NULL : locs[r],
				      d == -1 ? NULL : locs[d],
				      l == -1 ? NULL : locs[l]);
		int M;
		fscanf(fin,"%d",&M);
		for(int j = 0; j<M; j++) {
			int preid;
			fscanf(fin,"%d",&preid);
			locs[i]->add_prereq(locs[preid]);
		}
	}
	current_loc = locs[S];
}

void overworld::transition(int d) {
	overworld_loc *new_loc = NULL;
	switch(d) {
		case 0: // up
			new_loc = current_loc->up;
			break;
		case 1: // right
			new_loc = current_loc->right;
			break;
		case 2: // down
			new_loc = current_loc->down;
			break;
		case 3: // left
			new_loc = current_loc->left;
			break;
	}
	if(new_loc && new_loc->unlocked()) {
		current_loc = new_loc;
	}
}

void overworld::pause() {
	paused = true;
}

void overworld::unpause() {
	paused = false;
}

void overworld::clear_current() {
	current_loc->cleared = true;
}

void overworld::load_save(char* fname) {
	FILE *fin = fopen(fname,"r");
	if(!fin) {
		new_game();
		return;
	}
	for(std::vector<overworld_loc*>::iterator iter = locs.begin(); iter != locs.end(); iter++) {
		int a;
		fscanf(fin,"%d",&a);
		if(a) {
			(*iter)->cleared = true;
			fscanf(fin,"%lf",&(*iter)->record);
		} else {
			(*iter)->cleared = false;
		}
	}
	fclose(fin);
}

void overworld::write_save(char* fname) {
	FILE *fout= fopen(fname,"w");
	for(std::vector<overworld_loc*>::iterator iter = locs.begin(); iter != locs.end(); iter++) {
		if((*iter)->cleared) {
			fprintf(fout,"1 %.2lf\n",(*iter)->record);
		} else {
			fprintf(fout,"0\n");
		}
	}
	fclose(fout);
}

void overworld::new_game() {
	for(std::vector<overworld_loc*>::iterator iter = locs.begin(); iter != locs.end(); iter++) {
		(*iter)->cleared = false;
	}
	current_loc = starting_loc;
}
