#ifndef NOTE_HH
#define NOTE_HH

#include<AL/al.h>
#include<AL/alc.h>

void init_notes(double base_freq, double tempo, int noctaves, int sample_rate);
ALuint create_note(double freq, double duration, int sample_rate);
ALuint get_note(int tone, int duration);
ALuint create_rest(double duration, int sample_rate);

#endif
