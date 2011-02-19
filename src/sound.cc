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
short test_buffer[100000];
double temp_buffer[100000];
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

//	double max_amp = 0.0;
//	double freq = 261.6;
//	for(int i = 0; i<100000; i++) {
//		temp_buffer[i] = 0;
//		
//		if(12*i/sample_rate != 12*(i-1)/sample_rate) {
//			if(rand()%2) {
//				freq *= semitone;
//			} else {
//				freq /= semitone;
//			}
//		}
//		for(int harmonic = 1; harmonic<10; harmonic++) {
//			temp_buffer[i] += harmonic*harmonic*exp(-harmonic)*sin(2*pi*i*freq*harmonic/sample_rate);
//		}
//		//freq = sqrt(220*330.);
//		//for(int harmonic = 1; harmonic<100; harmonic++) {
//		//	temp_buffer[i] += harmonic*exp(-harmonic)*sin(2*pi*i*freq*harmonic/sample_rate);
//		//}
//		//freq = 165.;
//		//for(int harmonic = 1; harmonic<100; harmonic++) {
//		//	temp_buffer[i] += harmonic*exp(-harmonic)*sin(2*pi*i*freq*harmonic/sample_rate);
//		//}
//		
//		if(abs(temp_buffer[i]) > max_amp) {
//			max_amp = abs(temp_buffer[i]);
//		}
//	}
//	for(int i = 0; i < 100000; i++) {
//		test_buffer[i] = (short)((32767./max_amp)*temp_buffer[i]);
//	}

	for(int i = 0; i<131072; i++) {
		temp_prebuf[i] = std::complex<double>(0.0,0.0);
	}
	double freq = 261.6;
	temp_prebuf[(int)(freq * 131072. / sample_rate)] = std::complex<double>(1.0,0.0);
	temp_prebuf[(int)(1.5*freq * 131072. / sample_rate)] = std::complex<double>(1.0,0.0);
	printf("%d\n",(int)(freq * 131072. / sample_rate));
	fft(temp_prebuf,131072);
	double max_amp = 0.0;
	for(int i = 0; i<100000; i++) {
		temp_buffer[i] = temp_prebuf[i].real();
	//	printf("%lf\n",temp_buffer[i]);
		if(abs(temp_buffer[i]) > max_amp) {
			max_amp = abs(temp_buffer[i]);
		}
	}
	for(int i = 0; i<100000; i++) {
		test_buffer[i] = (short)((32767./max_amp)*temp_buffer[i]);
	}

	alGenBuffers(1, &test_buffer_name);
	alBufferData(test_buffer_name, AL_FORMAT_MONO16, test_buffer, 200000, sample_rate);
	alSourceQueueBuffers(global_sound_source,1,&test_buffer_name);

	alSourcePlay(global_sound_source);
}
