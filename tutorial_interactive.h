#ifndef TUTORIAL_INTERACTIVE_H
#define TUTORIAL_INTERACTIVE_H

#include <stdbool.h>

/*
 * A step-based interactive tutorial that guides new users 
 * through the painting features.
 */

void tutorial_init();
void tutorial_next_step();
bool tutorial_is_done();

#endif
