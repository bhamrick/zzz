#include<view.hh>

view::view() {
	minx = -1;
	miny = -1;
	maxx = 1;
	maxy = 1;
	following = NULL;
}

void view::update() {
	if(following) {
		if(following->position.x > minx + 5./6.*(maxx-minx)) {
			double dx = maxx - minx;
			minx = following->position.x - 5./6.*dx;
			maxx = following->position.x + 1./6.*dx;
		}
		if(following->position.x < minx + 1./6.*(maxx-minx)) {
			double dx = maxx - minx;
			minx = following->position.x - 1./6.*dx;
			maxx = following->position.x + 5./6.*dx;
		}
		if(following->position.y > miny + 5./6.*(maxy-miny)) {
			double dy = maxy - miny;
			miny = following->position.y - 5./6.*dy;
			maxy = following->position.y + 1./6.*dy;
		}
		if(following->position.y < miny + 1./6.*(maxy-miny)) {
			double dy = maxy - miny;
			miny = following->position.y - 1./6.*dy;
			maxy = following->position.y + 5./6.*dy;
		}
	}
}

void view::follow(character* c) {
	following = c;
	minx = c->position.x - 1;
	miny = c->position.y - 1;
	maxx = c->position.x + 1;
	maxy = c->position.y + 1;
}

void view::unfollow() {
	following = NULL;
}

void view::reset() {
	if(following) {
		minx = following->position.x - 1;
		miny = following->position.y - 1;
		maxx = following->position.x + 1;
		maxy = following->position.y + 1;
	} else {
		minx = -1;
		miny = -1;
		maxx = 1;
		maxy = 1;
	}
}
