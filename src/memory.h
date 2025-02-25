#pragma once
#include "bytes.h"
#include "screen.h"
#include <vector>

class Memory {
public:
	Memory();

	void reset(FILE*);
	void set(WORD, BYTE);
	void push(BYTE);
	void setScreen(BYTE, BYTE, BYTE);
	void clearScreen();
	BYTE get(WORD);
	BYTE pop();
	Screen getScreen();
	BYTE getScreen(BYTE, BYTE);


private:
	BYTE m_gameMemory[0xFFF];
	std::vector<WORD> m_stack;
	Screen m_screenData;
};