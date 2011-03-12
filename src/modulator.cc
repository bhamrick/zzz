#include<modulator.hh>
#include<const.hh>
#include<cmath>

modulator::modulator() {
	min_amp = 1.0;
	max_amp = 1.0;
	freq = 0.0;
}

modulator::modulator(double min_amp, double max_amp, double freq) {
	this->min_amp= min_amp;
	this->max_amp= max_amp;
	this->freq = freq;
}

void modulator::apply(std::complex<double>* buf, int N, int sample_rate) {
	for(int i = 0; i<N; i++) {
		double t = (double)i/sample_rate;
		double ratio = (min_amp + max_amp)/2. + (max_amp - min_amp)/2. * cos(2*pi*freq*t);
		buf[i] *= ratio;
	}
}

void modulator::apply(double* buf, int N, int sample_rate) {
	for(int i = 0; i<N; i++) {
		double t = (double)i/sample_rate;
		double ratio = (min_amp + max_amp)/2. + (max_amp - min_amp)/2. * cos(2*pi*freq*t);
		buf[i] *= ratio;
	}
}
