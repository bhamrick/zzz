#ifndef FILTER_H
#define FILTER_H

#include<complex>

enum filter_type {FILTER_LOWPASS, FILTER_HIGHPASS};

class filter {
	public:
	filter_type type;
	double cutoff_freq;
	double slope; // in dB/octave

	filter();
	filter(filter_type type, double cutoff_freq, double slope);

	void apply(double* buf, int N, int sample_rate);
	void apply(std::complex<double>* buf, int N, int sample_rate);
};

#endif
