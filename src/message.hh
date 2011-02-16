#ifndef MESSAGE_H
#define MESSAGE_H

void init_message(char*);
void restore_state();
void draw_message();
void push_message(char*); // draws on the second frame after pushing (to allow for drawing of a different mode, for example)
char* front_message();
void pop_message();

#endif
