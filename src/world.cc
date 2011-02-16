#include<world.hh>
#include<cstdio>
#include<options.hh>
#include<message.hh>

world::world(overworld* over) {
	paused = false;
	main_view = new view();
	gettimeofday(&last_update, NULL);
	this->over = over;

	world_menu = new menu();
	world_menu->add_item(new menu_item((char*)"Resume"));
	world_menu->add_item(new menu_item((char*)"Restart level"));
	world_menu->add_item(new menu_item((char*)"Exit level"));

	timestamp = 0.0;
}

void world::update() {
	struct timeval now;
	gettimeofday(&now, NULL);
	double dt = now.tv_sec - last_update.tv_sec + 1e-6*(now.tv_usec - last_update.tv_usec);
	if(dt < 0.01 && !paused) {
		timestamp += dt;
		input_handler->update(dt);
		// Springs
		for(std::vector<spring*>::iterator iter = springs.begin(); iter != springs.end(); iter++) {
			(*iter)->update(dt);
		}
		for(std::vector<character*>::iterator iter = characters.begin(); iter != characters.end(); iter++) {
			// Check for character collisions with springs
			for(std::vector<spring*>::iterator it = springs.begin(); it != springs.end(); it++) {
				(*iter)->collide(*it);
			}
			// Gravity
			(*iter)->impulse(g*dt*((*iter)->mass));
			// Update
			(*iter)->update(dt);
		}
		for(std::vector<mass*>::iterator iter = masses.begin(); iter != masses.end(); iter++) {
			// Gravity
			(*iter)->impulse(g*dt*((*iter)->m));
			// Update
			(*iter)->update(dt);
		}
	}

	main_view->update();

	// Check for winning
	if((player->position - goal).norm() < player->radius + GOAL_RADIUS) {
		win();
	}

	// Check for messages
	if(!messages.empty()) {
		world_message* m = messages.front();
		if(timestamp > m->timestamp) {
			init_message(m->text);
			messages.pop();
		}
	}

	last_update = now;
}

void world::add_mass(mass* m) {
	masses.push_back(m);
}

void world::add_spring(spring* s) {
	springs.push_back(s);
}

void world::add_character(character* c) {
	characters.push_back(c);
}

void world::queue_message(world_message* m) {
	messages.push(m);
}

void world::pause() {
	paused = true;
}

void world::unpause() {
	paused = false;
}

void world::reset() {
	for(std::vector<mass*>::iterator iter = masses.begin(); iter != masses.end(); iter++) {
		(*iter)->reset();
	}
	for(std::vector<character*>::iterator iter = characters.begin(); iter != characters.end(); iter++) {
		(*iter)->reset();
	}
	main_view->reset();
	timestamp = 0.0;
}

void world::draw() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(-(main_view->minx + main_view->maxx)/2., -(main_view->miny + main_view->maxy)/2., 0.0);

//	glClearColor(1.0,1.0,1.0,0.0);
//	glColor3f(0.0,0.0,0.0);
//
//	glClear(GL_COLOR_BUFFER_BIT);
	
	draw_background(bg_center + main_view->center()/64.);

	glColor3f(1.0,1.0,1.0);
	glBegin(GL_QUADS);
	for(std::vector<mass*>::iterator iter = masses.begin(); iter != masses.end(); iter++) {
		double x = (*iter)->position.x, y = (*iter)->position.y;
		double eps = 1e-2;
		glVertex2f(x-eps,y-eps);
		glVertex2f(x+eps,y-eps);
		glVertex2f(x+eps,y+eps);
		glVertex2f(x-eps,y+eps);
	}
	glEnd();

	glBegin(GL_LINES);
	for(std::vector<spring*>::iterator iter = springs.begin(); iter != springs.end(); iter++) {
		glVertex2f((*iter)->m1->position.x,(*iter)->m1->position.y);
		glVertex2f((*iter)->m2->position.x,(*iter)->m2->position.y);
	}
	glEnd();

	for(std::vector<character*>::iterator iter = characters.begin(); iter != characters.end(); iter++) {
		draw_player((*iter)->position,(*iter)->radius);
//		draw_circle((*iter)->position,(*iter)->radius);
//		glBegin(GL_LINES);
//			glVertex2f((*iter)->position.x, (*iter)->position.y);
//			glVertex2f((*iter)->position.x - 0.05*(*iter)->momentum.x, (*iter)->position.y - 0.05*(*iter)->momentum.y);
//		glEnd();
	}

	// draw the goal
	double radius = 0.03;
	glBegin(GL_LINES);
	for(int i = 0; i<5; i++) {
		glVertex2f(goal.x + radius*sin(2*pi*i/5), goal.y+radius*cos(2*pi*i/5));
		glVertex2f(goal.x + radius*sin(2*pi*(i+2)/5), goal.y + radius*cos(2*pi*(i+2)/5));
	}
	glEnd();

	if(is_option_set(OPTION_SHOW_TIME)) {
		char timestr[10];
		sprintf(timestr,"%.2lf",timestamp);
		draw_string(-0.05,1.0,timestr);
	}
	
	if(paused && world_menu) {
		world_menu->draw();
	}
}

void world::win() {
	if(!over->current_loc->cleared || timestamp < over->current_loc->record) {
		over->current_loc->record = timestamp;
	}
	over->clear_current();
	set_mode(OVERWORLD_MODE);
}

world_message::world_message(double t, char* s) {
	text = s;
	timestamp = t;
}
