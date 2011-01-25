#ifndef VEC_H
#define VEC_H

class vec {
	public:
	double x, y;
	vec();
	vec(double,double);
	vec operator+(vec);
	vec& operator+=(vec);
	vec& operator=(vec);
	vec operator-(vec);
	vec& operator-=(vec);
	vec operator-();
	vec& operator*=(double);
	vec operator/(double);
	double norm();
	double dot(vec);

	friend vec operator*(double, vec);
	friend vec operator*(vec, double);
};

#endif
