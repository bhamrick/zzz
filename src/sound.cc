#include<sound.hh>
#include<AL/al.h>
#include<AL/alc.h>
#include<cstdio>
#include<const.hh>
#include<cmath>
#include<cstdlib>
#include<fft.hh>

ALCdevice * device;
ALCcontext * context;
ALuint global_sound_source;

ALuint test_buffer_name;
short test_buffer[131072];
double temp_buffer[131072];
std::complex<double> temp_prebuf[131072];

const int sample_rate = 44000;

double abs(double x) {
	if(x > 0) return x;
	return -x;
}

void init_sound() {
	device = alcOpenDevice(NULL);
	if(device == NULL) {
		fprintf(stderr,"No sound device found\n");
		return;
	}
	context = alcCreateContext(device,NULL);
	if(context == NULL) {
		fprintf(stderr,"Could not create sound context\n");
		return;
	}
	alcMakeContextCurrent(context);

	alGetError();

	alDistanceModel(AL_NONE);

	alGenSources(1,&global_sound_source);
	alSourcei(global_sound_source, AL_LOOPING, AL_TRUE);
	alSourcei(global_sound_source, AL_SOURCE_RELATIVE, AL_TRUE);
	alSourcef(global_sound_source, AL_GAIN, 1.0);
	alSource3f(global_sound_source, AL_POSITION, 0.0, 0.0, 0.0);
	alListenerf(AL_GAIN, 1.0);

	
	add_tone(temp_prebuf, 131072, 14);
	add_tone(temp_prebuf, 131072, 18);
	add_tone(temp_prebuf, 131072, 21);

	fft(temp_prebuf,131072);
	double max_amp = 0.0;
	for(int i = 0; i<131072; i++) {
		temp_buffer[i] = temp_prebuf[i].imag();
	//	printf("%lf\n",temp_buffer[i]);
		if(abs(temp_buffer[i]) > max_amp) {
			max_amp = abs(temp_buffer[i]);
		}
	}
	for(int i = 0; i<131072; i++) {
		test_buffer[i] = (short)((32767./max_amp)*temp_buffer[i]);
	}

	alGenBuffers(1, &test_buffer_name);
	//alBufferData(test_buffer_name, AL_FORMAT_MONO16, test_buffer, 200000, sample_rate);
	alBufferData(test_buffer_name, AL_FORMAT_MONO16, test_buffer, 2*(131072), sample_rate);
	alSourceQueueBuffers(global_sound_source,1,&test_buffer_name);

	alSourcePlay(global_sound_source);
}

void add_tone(std::complex<double>* arr, int N, int tone) {
	double base_freq = 65.406;
	int nharms = 38;
	double harms[] = {
		26.13,
		777.99,
		3590.0,
		1164.6,
		330.84,
		1354.24,
		640.26,
		331.68,
		500.14,
		86.03,
		70.35,
		64.27,
		82.79,
		54.78,
		111.82,
		74.64,
		105.78,
		42.17,
		13.74,
		1.71,
		22.57,
		28.38,
		12.74,
		0.77,
		26.18,
		50.98,
		37.13,
		40.73,
		34.17,
		32.11,
		17.29,
		13.48,
		13.66,
		16.87,
		16.78,
		7.44,
		11.03,
		11.94
	};
	double freq = base_freq * pow(semitone,tone);
	for(int harmonic = 1; harmonic <= nharms; harmonic++) {
		if((int)(harmonic*freq * N/sample_rate) < N) {
			arr[(int)(harmonic*freq * N/sample_rate)] = harms[harmonic] * std::complex<double>(1.0,0.0);
		}
	}
}
