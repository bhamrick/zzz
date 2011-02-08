#include<level.hh>
#include<cstdio>
#include<sys/stat.h>

void load(char* fname, world* w) {
	w->masses.clear();
	w->springs.clear();
	w->characters.clear();
	FILE *fin = fopen(fname, "r");
	vec start;
	double pradius;
	fscanf(fin,"%lf%lf%lf",&start.x,&start.y,&pradius);
	character* player = new character(pradius,1.0,start);
	w->add_character(player);
	w->player = player;
	w->main_view->follow(player);
	if(w->input_handler) {
		w->input_handler->mover = player;
	} else {
		w->input_handler = new input(player,w);
	}
	
	fscanf(fin,"%lf%lf",&w->goal.x,&w->goal.y);
	// masses
	int N;
	fscanf(fin,"%d",&N);
	for(int i = 0; i<N; i++) {
		double m;
		vec pos, mo;
		int fix;
		fscanf(fin,"%lf%lf%lf%lf%lf%d",&m,&pos.x,&pos.y,&mo.x,&mo.y,&fix);
		w->add_mass(new mass(m,pos,mo,fix));
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

	// message?
	int is_msg;
	fscanf(fin,"%d",&is_msg);
	if(is_msg) {
		fscanf(fin," ");
		int filesize, curpos;
		struct stat fstatus;
		stat(fname, &fstatus);
		filesize = fstatus.st_size;
		curpos = ftell(fin);
		char * buf = new char[filesize - curpos + 1];
		int count = fread(buf, 1, filesize - curpos, fin);
		buf[count] = 0;
		while(count >= 1 && buf[count-1] == '\n') {
			buf[count-1] = 0;
			count--;
		}
		
		w->queue_message(new world_message(0.02, buf));
	}

	fclose(fin);

	w->timestamp = 0.0;
}
