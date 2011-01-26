#ifndef MASS_H
#define MASS_H

#include<vec.hh>
#include<unistd.h>

class mass {
	public:
	double m;
	vec position, momentum, ipos, imo;
	bool fixed;

	mass();
	mass(double);
	mass(double, vec);
	mass(double, vec, vec);
	mass(double, vec, vec, bool);

	void update(double);
	void impulse(vec);
	void reset();

	void fix();
	void unfix();
};

#endif
