#include<mode.hh>

void set_mode(mode m) {
	display_set_mode(m);
	input_set_mode(m);
	update_set_mode(m);
}
