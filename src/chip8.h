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
	BYTE* getNextOpcode();
	void sendKeyboard();
	Memory m_ram;

private:
	CPU m_cpu;

};