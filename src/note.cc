#include<note.hh>
#include<source.hh>
#include<filter.hh>
#include<modulator.hh>
#include<mollifier.hh>
#include<cmath>
#include<const.hh>

ALuint** tone_map;
ALuint* rest_map;

void init_notes(double base_freq, double tempo, int noctaves, int sample_rate) {
	double sixteenth_duration = 60./(4*tempo);
	tone_map = new ALuint*[12*noctaves];
	for(int tone = 0; tone < 12*noctaves; tone++) {
		tone_map[tone] = new ALuint[16];
		printf("%d %lf\n",tone,base_freq*pow(semitone,tone));
		for(int i = 0; i<16; i++) {
			tone_map[tone][i] = create_note(base_freq*pow(semitone,tone), (i+1)*sixteenth_duration, sample_rate);
		}
	}
	rest_map = new ALuint[16];
	for(int i = 0; i<16; i++) {
		rest_map[i] = create_rest((i+1)*sixteenth_duration, sample_rate);
	}
}

ALuint get_note(int tone, int duration) {
	if(tone == -1) {
		return rest_map[duration-1];
	}
	return tone_map[tone][duration-1];
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
	mollifier mol;
	s.make_waveform(buf, N, sample_rate);
	f1.apply(buf, N, sample_rate);
	f2.apply(buf, N, sample_rate);
	m.apply(buf, N, sample_rate);
	mol.apply(buf, N, sample_rate);
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
	alBufferData(note_buf, AL_FORMAT_MONO16, data, 2*N, sample_rate);
	// These deletes apparently break stuff even though the OpenAL specification says they shouldn't
//	delete[] buf;
//	delete[] data;
	return note_buf;
}

ALuint create_rest(double duration, int sample_rate) {
	ALuint rest_buf;
	alGenBuffers(1,&rest_buf);
	int N = (int)(duration * sample_rate);
	short* data = new short[N];
	for(int i = 0; i<N; i++) {
		data[i] = 0;
	}
	alBufferData(rest_buf, AL_FORMAT_MONO16, data, 2*N, sample_rate);
//	delete[] data;
	return rest_buf;
}
