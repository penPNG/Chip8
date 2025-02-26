#include "chip8.h"

Chip8::Chip8() {
	m_ram = Memory();
	m_cpu = CPU(&m_ram);
}

// please put whatever rom file you use here!
// vs directory shenanigans below
void Chip8::reset() {
	m_cpu.reset();
	m_ram.reset(fopen("../../../Tetris.ch8", "rb"));

	return;
}

bool Chip8::playSound() {
	if (m_cpu.decSound()) {
		return true;
	}
	return false;
}

BYTE* Chip8::getNextOpcode() {
	WORD res = 0;
	res = m_ram.get(m_cpu.getPC());
	res <<= 8;
	res |= m_ram.get(m_cpu.getPC() + 1);
	//printf("%x\n", res);
	m_cpu.compute(res);
	m_cpu.decTimer();
	m_cpu.decSound();
	return m_ram.getScreen();
}

void Chip8::sendKeyboard(SDL_Event* event) {
	switch (event->type) {
		case SDL_EVENT_KEY_DOWN: {
			switch (event->key.key) {
				case SDLK_1: printf("1\n"); m_cpu.m_keys[0x1] = 1; break;
				case SDLK_2: m_cpu.m_keys[0x2] = 1; break;
				case SDLK_3: m_cpu.m_keys[0x3] = 1; break;
				case SDLK_4: m_cpu.m_keys[0xC] = 1; break;
				case SDLK_Q: m_cpu.m_keys[0x4] = 1; break;
				case SDLK_W: m_cpu.m_keys[0x5] = 1; break;
				case SDLK_E: m_cpu.m_keys[0x6] = 1; break;
				case SDLK_R: m_cpu.m_keys[0xD] = 1; break;
				case SDLK_A: m_cpu.m_keys[0x7] = 1; break;
				case SDLK_S: m_cpu.m_keys[0x8] = 1; break;
				case SDLK_D: m_cpu.m_keys[0x9] = 1; break;
				case SDLK_F: m_cpu.m_keys[0xE] = 1; break;
				case SDLK_Z: m_cpu.m_keys[0xA] = 1; break;
				case SDLK_X: m_cpu.m_keys[0x0] = 1; break;
				case SDLK_C: m_cpu.m_keys[0xC] = 1; break;
				case SDLK_V: m_cpu.m_keys[0xF] = 1; break;
			}
		} break;
		case SDL_EVENT_KEY_UP: {
			switch (event->key.key) {
				case SDLK_1: m_cpu.m_keys[0x1] = 0; break;
				case SDLK_2: m_cpu.m_keys[0x2] = 0; break;
				case SDLK_3: m_cpu.m_keys[0x3] = 0; break;
				case SDLK_4: m_cpu.m_keys[0xC] = 0; break;
				case SDLK_Q: m_cpu.m_keys[0x4] = 0; break;
				case SDLK_W: m_cpu.m_keys[0x5] = 0; break;
				case SDLK_E: m_cpu.m_keys[0x6] = 0; break;
				case SDLK_R: m_cpu.m_keys[0xD] = 0; break;
				case SDLK_A: m_cpu.m_keys[0x7] = 0; break;
				case SDLK_S: m_cpu.m_keys[0x8] = 0; break;
				case SDLK_D: m_cpu.m_keys[0x9] = 0; break;
				case SDLK_F: m_cpu.m_keys[0xE] = 0; break;
				case SDLK_Z: m_cpu.m_keys[0xA] = 0; break;
				case SDLK_X: m_cpu.m_keys[0x0] = 0; break;
				case SDLK_C: m_cpu.m_keys[0xC] = 0; break;
				case SDLK_V: m_cpu.m_keys[0xF] = 0; break;
			}
		} break;
	}
}