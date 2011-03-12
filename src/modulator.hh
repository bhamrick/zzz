#ifndef MODULATOR_HH
#define MODULATOR_HH

#include<complex>

class modulator {
	public:
	double min_amp;
	double max_amp;
	double freq;

	modulator();
	modulator(double min_amp, double max_amp, double freq);
	void apply(std::complex<double>* buf, int N, int sample_rate);
	void apply(double* buf, int N, int sample_rate);
};

#endif
