#pragma once
#include "bytes.h"
#include <vector>

class Memory {
public:
	Memory();

	void reset(FILE*);
	void set(WORD, BYTE);
	void push(BYTE);
	void setScreen(BYTE, BYTE, BYTE);
	BYTE get(WORD);
	BYTE pop();
	BYTE getScreen(BYTE, BYTE);


private:
	BYTE m_gameMemory[0xFFF];
	std::vector<WORD> m_stack;
	BYTE m_screenData[64][32];
};