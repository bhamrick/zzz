#ifndef CHARACTER_H
#define CHARACTER_H

#include<spring.hh>

class character {
	public:
	vec position, momentum;
	double radius, mass;

	character(double,double,vec);
	character(double,double,vec,vec);
	void impulse(vec);
	void collide(spring*,double);
	void jump(spring*);
	void update(double);
};

#endif
