#pragma once
#include "bytes.h"

// I so didn't want to do this, but I don't know how to return a double array the way I want/need it
struct Screen {
	BYTE pixels[64][32];
};