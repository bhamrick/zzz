class view;

#ifndef VIEW_H
#define VIEW_H

#include<character.hh>

class view {
	public:
	double minx, miny, maxx, maxy;
	character* following;

	view();
	void update();
	void reset();
	void follow(character*);
	void unfollow();
};

#endif
