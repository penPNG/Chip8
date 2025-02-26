#pragma once
#include <vector>
#include <time.h>
#include "cpu.h"
#include "memory.h"
#include "keyboard.h"
#include "screen.h"
#include "bytes.h"


class Chip8 {
public:
	Chip8();
	void reset();
	bool playSound();
	BYTE* getNextOpcode();
	void sendKeyboard(SDL_Event*);
	Memory m_ram;

private:
	CPU m_cpu;
};