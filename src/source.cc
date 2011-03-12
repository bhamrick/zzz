#include<source.hh>
#include<const.hh>
#include<cmath>

source::source() {
	type = SOURCE_SINE;
	freq = 440.0;
}

source::source(source_type type, double freq) {
	this->type = type;
	this->freq = freq;
}

void source::make_waveform(std::complex<double>* buf, int N, int sample_rate) {
	for(int i = 0; i<N; i++) {
		double t = (double)i / sample_rate;
		double v;
		switch(type) {
			case SOURCE_SINE:
				buf[i] += sin(2*pi*freq*t);
				break;
			case SOURCE_SQUARE:
				v = sin(2*pi*freq*t);
				if(v > 0) {
					buf[i] += 1;
				} else if(v < 0) {
					buf[i] += -1;
				} else {
					buf[i] += 0;
				}
				break;
			case SOURCE_SAW:
				v = t*freq - floor(t*freq);
				buf[i] += -1 + 2*v;
				break;
			case SOURCE_TRIANGLE:
				v = t*freq - floor(t*freq);
				if(v < 0.5) {
					buf[i] += -1 + 4*v;
				} else {
					buf[i] += 3 - 4*v;
				}
				break;
		}
	}
}

void source::make_waveform(std::complex<double>* buf, int N, int sample_rate) {
	for(int i = 0; i<N; i++) {
		double t = (double)i / sample_rate;
		double v;
		switch(type) {
			case SOURCE_SINE:
				buf[i] += std::complex<double>(sin(2*pi*freq*t),0);
				break;
			case SOURCE_SQUARE:
				v = sin(2*pi*freq*t);
				if(v > 0) {
					buf[i] += std::complex<double>(1,0);
				} else if(v < 0) {
					buf[i] += std::complex<double>(-1,0);
				} else {
					buf[i] += std::complex<double>(0,0);
				}
				break;
			case SOURCE_SAW:
				v = t*freq - floor(t*freq);
				buf[i] += std::complex<double>(-1 + 2*v,0);
				break;
			case SOURCE_TRIANGLE:
				v = t*freq - floor(t*freq);
				if(v < 0.5) {
					buf[i] += std::complex<double>(-1 + 4*v,0);
				} else {
					buf[i] += std::complex<double>(3 - 4*v,0);
				}
				break;
		}
	}
}
