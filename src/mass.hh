#ifndef MASS_H
#define MASS_H

#include<vec.hh>
#include<unistd.h>

class mass {
	public:
	double m;
	vec position, momentum, ipos, imo;
	int fixed; // 0 = unfixed, 1 = totally fixed, 2 = only vertical movement, 3 = only horizontal movement

	mass();
	mass(double);
	mass(double, vec);
	mass(double, vec, vec);
	mass(double, vec, vec, int);

	void update(double);
	void impulse(vec);
	void reset();

	void fix();
	void unfix();
};

#endif
