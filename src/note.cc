#include<note.hh>
#include<source.hh>
#include<filter.hh>
#include<modulator.hh>
#include<cmath>

void init_notes() {
	
}

ALuint create_note(double freq, double duration, int sample_rate) {
	ALuint note_buf;
	alGenBuffers(1,&note_buf);
	int N = (int)(duration * sample_rate);
	double* buf = new double[N];
	short* data = new short[N];
	source s(SOURCE_SAW, freq);
	filter f1(FILTER_LOWPASS, 200, 3);
	filter f2(FILTER_HIGHPASS, 20, 3);
	modulator m(1.0,1.2,7);
	s.make_waveform(buf, N, sample_rate);
	f1.apply(buf, N, sample_rate);
	f2.apply(buf, N, sample_rate);
	m.apply(buf, N, sample_rate);
	double max_amp = 0;
	for(int i = 0; i<N; i++) {
		if(buf[i] > max_amp) {
			max_amp = buf[i];
		}
		if(-buf[i] > max_amp) {
			max_amp = -buf[i];
		}
	}
	for(int i = 0; i<N; i++) {
		data[i] = (short)(0x7FFF * buf[i] / max_amp);
	}
	alBufferData(&note_buf, AL_FORMAT_MONO_16, data, 2*N, sample_rate);
	delete[] buf;
	delete[] data;
	return note_buf;
}
