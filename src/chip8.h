#pragma once
#include <vector>
#include <time.h>
#include "cpu.h"
#include "memory.h"
#include "keyboard.h"
#include "bytes.h"


class Chip8 {
public:
	Chip8();
	void reset();
	void getNextOpcode();

private:
	Memory m_ram;
	CPU m_cpu;

};