#include<filter.hh>
#include<const.hh>
#include<cmath>

filter::filter() {
	type = FILTER_LOWPASS;
	cutoff_freq = 20.0;
	slope = 1.0;
}

filter::filter(filter_type type, double cutoff_freq, double slope) {
	this->type = type;
	this->cutoff_freq = cutoff_freq;
	this->slope = slope;
}

void filter::apply(double* buf, int N, int sample_rate) {
	// TODO: make slopes work
	double dt = 1./sample_rate;
	double RC = 1./(2*pi*cutoff_freq);
	if(type == FILTER_LOWPASS) {
		double alpha = dt/(RC + dt);
		for(int i = 1; i<N; i++) {
			buf[i] = alpha*buf[i] + buf[i-1];
		}
	} else if(type == FILTER_HIGHPASS) {
		double alpha = RC/(RC + dt);
		double last = buf[0];
		for(int i = 1; i<N; i++) {
			double t = buf[i];
			buf[i] = alpha*buf[i-1] + alpha*(buf[i] - last);
			last = t;
		}
	}
}

void filter::apply(std::complex<double>* buf, int N, int sample_rate) {
	// TODO: make slopes work
	double dt = 1./sample_rate;
	double RC = 1./(2*pi*cutoff_freq);
	if(type == FILTER_LOWPASS) {
		double alpha = dt/(RC + dt);
		for(int i = 1; i<N; i++) {
			buf[i] = alpha*buf[i] + buf[i-1];
		}
	} else if(type == FILTER_HIGHPASS) {
		double alpha = RC/(RC + dt);
		std::complex<double> last = buf[0];
		for(int i = 1; i<N; i++) {
			std::complex<double> t = buf[i];
			buf[i] = alpha*buf[i-1] + alpha*(buf[i] - last);
			last = t;
		}
	}
}
