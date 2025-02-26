#include "memory.h"

uint8_t fontset[80] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


Memory::Memory() {
	memset(m_gameMemory, 0, sizeof(m_gameMemory));
	m_stack.clear();
	for (int i = 0; i < 64*32; i++) {
		m_screenData[i] = 0;
	}
}

void Memory::reset(FILE* in) {
	memset(m_gameMemory, 0, sizeof(m_gameMemory));
	m_stack.clear();
	for (int i = 0; i < 64*32; i++) {
		m_screenData[i] = 0;
	}
	for (unsigned int i = 0; i < 80; ++i) {
		m_gameMemory[0x50 + i] = fontset[i];
	}
	fread(&m_gameMemory[0x200], 0xfff, 1, in);
	fclose(in);
}

void Memory::set(WORD addr, BYTE data) {
	m_gameMemory[addr] = data;
}

void Memory::setScreen(BYTE X, BYTE Y, BYTE height) {
	m_screenData[X+Y*64] = height;
}

void Memory::clearScreen() {
	for (int i = 0; i < 64*32; i++) {
		m_screenData[i] = 0;
	}
}

void Memory::push(WORD data) {
	m_stack.push_back(data);
}

BYTE Memory::get(WORD addr) {
	return m_gameMemory[addr];
}

WORD Memory::pop() {
	WORD data = m_stack.back(); 
	m_stack.pop_back();
	return data;
}

BYTE* Memory::getScreen() {
	return m_screenData;
}

BYTE Memory::getScreen(BYTE X, BYTE Y) {
	return m_screenData[X*Y];
}