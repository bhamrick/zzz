#ifndef NOTE_HH
#define NOTE_HH

#include<AL/al.h>
#include<AL/alc.h>

void init_notes();
ALuint create_note(double freq, double duration, int sample_rate);

#endif
