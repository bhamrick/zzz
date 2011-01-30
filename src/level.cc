#include<level.hh>
#include<cstdio>

void load(char* fname, world* w) {
	w->masses.clear();
	w->springs.clear();
	w->characters.clear();
	FILE *fin = fopen(fname, "r");
	vec start;
	fscanf(fin,"%lf%lf",&start.x,&start.y);
	character* player = new character(0.03,1.0,start);
	w->add_character(player);
	w->main_view->follow(player);
	w->input_handler = new input(player,w);
	
	fscanf(fin,"%lf%lf",&w->goal.x,&w->goal.y);
	// masses
	int N;
	fscanf(fin,"%d",&N);
	for(int i = 0; i<N; i++) {
		double m;
		vec pos, mo;
		int fix;
		fscanf(fin,"%lf%lf%lf%lf%lf%d",&m,&pos.x,&pos.y,&mo.x,&mo.y,&fix);
		w->add_mass(new mass(m,pos,mo,(bool)fix));
	}
	// springs
	fscanf(fin,"%d",&N);
	for(int i = 0; i<N; i++) {
		int i, j;
		double k, eq;
		fscanf(fin,"%d%d%lf%lf",&i,&j,&k,&eq);
		if(eq > 0) {
			w->add_spring(new spring(w->masses[i],w->masses[j],k,eq));
		} else {
			w->add_spring(new spring(w->masses[i],w->masses[j],k));
		}
	}
	fclose(fin);
}
