#ifndef SOURCE_H
#define SOURCE_H

#include<complex>

enum source_type {SOURCE_SINE, SOURCE_SQUARE, SOURCE_SAW, SOURCE_TRIANGLE};

class source {
	public:
	source_type type;
	double freq;

	source();
	source(source_type type, double freq);

	void make_waveform(std::complex<double>* buf, int N, int sample_rate);
	void make_waveform(double* buf, int N, int sample_rate);
};

#endif
