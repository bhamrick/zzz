#include<overworld.hh>
#include<display.hh>
#include<GL/glut.h>
#include<cstdio>

overworld_loc::overworld_loc() {
	levelname = NULL;
}

overworld_loc::overworld_loc(char* n) {
	levelname = n;
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

overworld::overworld() {
	current_loc = NULL;
}

overworld::overworld(char* fname) {
	load(fname);
}

void overworld::add_location(overworld_loc* l) {
	locs.push_back(l);
}

void overworld::draw() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0,0.0,0.0);

	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_QUADS);
		for(std::vector<overworld_loc*>::iterator iter = locs.begin(); iter != locs.end(); iter++) {
			double eps = 1e-2;
			double x = (*iter)->pos.x, y = (*iter)->pos.y;
			glVertex2f(x-eps,y-eps);
			glVertex2f(x+eps,y-eps);
			glVertex2f(x+eps,y+eps);
			glVertex2f(x-eps,y+eps);
		}
	glEnd();

	draw_circle(current_loc->pos, 0.03);
}

void overworld::set_current_location(overworld_loc* l) {
	current_loc = l;
}

void overworld::load(char* fname) {
	int N, S;
	FILE *fin = fopen(fname,"r");
	fscanf(fin,"%d%d",&N,&S);
	for(int i = 0; i<N; i++) {
		add_location(new overworld_loc());
	}
	for(int i = 0; i<N; i++) {
		locs[i]->levelname = new char[17];
		int u, r, d, l;
		fscanf(fin,"%s%lf%lf%d%d%d%d",locs[i]->levelname,&(locs[i]->pos.x),&(locs[i]->pos.y),&u,&r,&d,&l);
		locs[i]->set_neighbors(u == -1 ? NULL : locs[u],
				      r == -1 ? NULL : locs[r],
				      d == -1 ? NULL : locs[d],
				      l == -1 ? NULL : locs[l]);
	}
	current_loc = locs[S];
}
