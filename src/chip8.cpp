#include "chip8.h"

Chip8::Chip8() {
	m_ram = Memory();
	m_cpu = CPU(&m_ram);
}

void Chip8::reset() {
	m_cpu.reset();
	m_ram.reset(fopen("../../../testfile", "rb"));

	return;
}

void Chip8::getNextOpcode() {
	WORD res = 0;
	res = m_ram.get(m_cpu.getPC());
	res <<= 8;
	res |= m_ram.get(m_cpu.getPC() + 1);
	m_cpu.incPC();
	//printf("%x\n", res);
	m_cpu.compute(res);
}