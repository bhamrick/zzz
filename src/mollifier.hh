#ifndef MOLLIFIER_HH
#define MOLLIFIER_HH

#include<complex>

class mollifier {
	public:
	mollifier();
	void apply(double* buf, int N, int sample_rate);
};

#endif
