#ifndef SPRING_H
#define SPRING_H

#include<mass.hh>
#include<cmath>

class spring {
	public:
	mass *m1, *m2;
	double k; // spring constant
	double d; // equillibrium distance

	spring(mass*,mass*);
	spring(mass*,mass*,double);
	spring(mass*,mass*,double,double);

	void update(double);
	void impulse(vec,vec);
};

#endif
