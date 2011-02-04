#include<mode.hh>

mode current_mode;

void set_mode(mode m) {
	current_mode = m;
	display_set_mode(m);
	input_set_mode(m);
	update_set_mode(m);
}

mode get_current_mode() {
	return current_mode;
}
