#ifndef __TETRIS_DEBUG_H_
#define __TETRIS_DEBUG_H_
#include<stdlib.h>
#define TETRIS_ASSERT(cond, msg) {if (cond) {abort();}};
#endif