#include "memory.h"

Memory::Memory() {
	memset(m_gameMemory, 0, sizeof(m_gameMemory));
	m_stack.clear();
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 32; j++) {
			m_screenData.pixels[i][j] = 0;
		}
	}
}

void Memory::reset(FILE* in) {
	memset(m_gameMemory, 0, sizeof(m_gameMemory));
	m_stack.clear();
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 32; j++) {
			m_screenData.pixels[i][j] = 0;
		}
	}
	fread(&m_gameMemory[0x200], 0xfff, 1, in);
	fclose(in);
}

void Memory::set(WORD addr, BYTE data) {
	m_gameMemory[addr] = data;
}

void Memory::setScreen(BYTE X, BYTE Y, BYTE height) {
	m_screenData.pixels[X][Y] = height;
}

void Memory::clearScreen() {
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 32; j++) {
			m_screenData.pixels[i][j] = 0;
		}
	}
}

void Memory::push(BYTE data) {
	m_stack.push_back(data);
}

BYTE Memory::get(WORD addr) {
	return m_gameMemory[addr];
}

BYTE Memory::pop() {
	BYTE data = m_stack.back(); 
	m_stack.pop_back();
	return data;
}

Screen Memory::getScreen() {
	return m_screenData;
}

BYTE Memory::getScreen(BYTE X, BYTE Y) {
	return m_screenData.pixels[X][Y];
}