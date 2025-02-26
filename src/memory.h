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
	BYTE* getScreen();
	BYTE getScreen(BYTE, BYTE);
	BYTE m_screenData[64 * 32]{};
	BYTE m_gameMemory[0xFFF];


private:
	std::vector<WORD> m_stack;
};