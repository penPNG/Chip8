#include "cpu.h"

CPU::CPU() {
	m_ram = NULL;
	for (int i = 0; i < 0xf; i++) m_registers[i] = 0;
	m_addressI = 0;
	m_programCounter = 0x200;
	m_delayTimer = 0;
	m_soundTimer = 0;
}

CPU::CPU(Memory *ram) {
	m_ram = ram;
	for(int i = 0; i<0xf; i++) m_registers[i] = 0;
	m_addressI = 0;
	m_programCounter = 0x200;
	m_delayTimer = 0;
	m_soundTimer = 0;
}

void CPU::reset() {
	for (int i = 0; i < 0xf; i++) m_registers[i] = 0;
	m_addressI = 0;
	m_programCounter = 0x200;
	m_delayTimer = 0;
	m_soundTimer = 0;
}

BYTE CPU::getReg(BYTE VX) {
	return m_registers[VX];
}

WORD CPU::getPC() {
	return m_programCounter;
}

void CPU::setReg(BYTE VX, BYTE data) {
	m_registers[VX] = data;
}

void CPU::setPC(WORD addr) {
	m_programCounter = addr;
}

void CPU::incPC() {
	m_programCounter += 2;
}

void CPU::compute(WORD opcode) {
	BYTE numer = (opcode & 0xF000) >> 8;
	BYTE denom = opcode & 0x000F;
	BYTE data = opcode & 0x00FF;
	WORD addr = opcode & 0x0FFF;
	BYTE VX = (opcode & 0x0F00) >> 8;
	BYTE VY = (opcode & 0x00F0) >> 4;
	/*for (int i = 0; i < 0xF; i++) {
		printf("register %x: %x\t", i, m_registers[i]);
	}printf("\n");*/

	switch (numer) {
		case 0x0000: {
			switch (addr) {
				case 0x0000: break;
				case 0x00E0: op00E0(); break;
				case 0x00EE: op00EE(); break;
				default: break;
			}
		} break;
		case 0x10: op1NNN(addr); break;
		case 0x20: op2NNN(addr); break;
		case 0x30: op3XNN(VX, data); break;
		case 0x40: op4XNN(VX, data); break;
		case 0x50: op5XY0(VX, VY); break;
		case 0x60: op6XNN(VX, data); break;
		case 0x70: op7XNN(VX, data); break;
		case 0x80: {
			switch (denom) {
				case 0x00: op8XY0(VX, VY); break;
				case 0x01: op8XY1(VX, VY); break;
				case 0x02: op8XY2(VX, VY); break;
				case 0x03: op8XY3(VX, VY); break;
				case 0x04: op8XY4(VX, VY); break;
				case 0x05: op8XY5(VX, VY); break;
				case 0x06: op8XY6(VX, VY); break;
				case 0x07: op8XY7(VX, VY); break;
				case 0x0E: op8XYE(VX, VY); break;
				default: break;
			}
		} break;
		case 0x90: op9XY0(VX, VY);
		case 0xA0: opANNN(addr); break;
		case 0xC0: opCXNN(VX, data); break;
		case 0xD0: opDXYN(VX, VY, data); break;
		case 0xE0: {
			switch (data) {
				case 0x9E: opEX9E(VX); break;
				case 0xA1: opEXA1(VX); break;
			}
		} break;
		case 0xF0: {
			switch (data) {
				case 0x07: opFX07(VX); break;
				case 0x0A: opFX0A(VX); break;
				case 0x15: opFX15(VX); break;
				case 0x18: opFX18(VX); break;
				case 0x1E: opFX1E(VX); break;
				case 0x29: opFX29(VX); break;
				case 0x33: opFX33(VX); break;
				case 0x55: opFX55(VX); break;
				case 0x65: opFX65(VX); break;
			}

		} break;
		default: printf("badop\n"); break;
	}
}

// Clear the screen
void CPU::op00E0() {
	printf("00E0\n");
	m_ram->clearScreen();
}

// Return from subrtn
void CPU::op00EE() {
	printf("00EE\n");
	m_programCounter = m_ram->pop();
}

// Jump to address
void CPU::op1NNN(WORD addr) {
	//printf("1NNN: %x\n", addr);
	m_programCounter = addr;
}

// Call subrtn
void CPU::op2NNN(WORD addr) {
	printf("2NNN: %x\n", addr);
	m_ram->push(m_programCounter);
	m_programCounter = addr;
}

// Skip if VX == NN
void CPU::op3XNN(BYTE VX, BYTE data) {
	printf("3XNN: %x %x\n", VX, data);
	if (m_registers[VX] == data) {
		m_programCounter += 2;
	}
}

// Skip if VX != NN
void CPU::op4XNN(BYTE VX, BYTE data) {
	printf("4XNN: %x %x\n", VX, data);
	if (m_registers[VX] != data) {
		m_programCounter += 2;
	}
}

// Skip if VX == VY
void CPU::op5XY0(BYTE VX, BYTE VY) {
	printf("5XY0: %x %x\n", VX, VY);
	if (m_registers[VX] == m_registers[VY]) {
		m_programCounter += 2;
	}
}

// Set VX = NN
void CPU::op6XNN(BYTE VX, BYTE data) {
	printf("6XNN: %x %x\n", VX, data);
	m_registers[VX] = data;
}

// Set VX += NN
void CPU::op7XNN(BYTE VX, BYTE data) {

	printf("7XY0: %x %x\n", VX, data);
	m_registers[VX] += data;
}

// Set VX = VY
void CPU::op8XY0(BYTE VX, BYTE VY) {
	printf("8XY0: %x %x\n", VX, VY);
	m_registers[VX] = m_registers[VY];
}

// set VX |= VY (bitwise OR)
void CPU::op8XY1(BYTE VX, BYTE VY) {
	printf("8XY1: %x %x\n", VX, VY);
	m_registers[VX] |= m_registers[VY];
}

// Set VX &= VY (bitwise AND)
void CPU::op8XY2(BYTE VX, BYTE VY) {
	printf("8XY2: %x %x\n", VX, VY);
	m_registers[VX] &= m_registers[VY];
}

// Set VX ^= VY (bitwise XOR)
void CPU::op8XY3(BYTE VX, BYTE VY) {
	printf("8XY3: %x %x\n", VX, VY);
	m_registers[VX] ^= m_registers[VY];
}

// Set VX += VY (set/unset F if overflow)
void CPU::op8XY4(BYTE VX, BYTE VY) {
	printf("8XY4: %x %x\n", VX, VY);
	m_registers[0xF] = 0;
	if ((m_registers[VX] + m_registers[VY]) | 0xF00) {
		m_registers[0xF] = 1;
	}
	m_registers[VX] += m_registers[VY];
}

// Set VX -= VY (set/unset VF if underflow (VX >= VY))
void CPU::op8XY5(BYTE VX, BYTE VY) {
	printf("8XY5: %x %x\n", VX, VY);
	m_registers[0xF] = 1;
	if (m_registers[VX] >= m_registers[VY]) {
		m_registers[0xF] = 0;
	}
	m_registers[VX] -= m_registers[VY];
}

// set VX >>= 1 (store 0x0X to VF)
void CPU::op8XY6(BYTE VX, BYTE VY) {
	printf("8XY6: %x %x\n", VX, VY);
	m_registers[0xF] = m_registers[VX] & 0b00000001;
	m_registers[VX] >>= 1;
}

// set VX = VY - VX (set/unset VF if underflow (VY >= VX))
void CPU::op8XY7(BYTE VX, BYTE VY) {
	printf("8XY7: %x %x\n", VX, VY);
	m_registers[0xF] = 1;
	if (m_registers[VY] >= m_registers[VX]) {
		m_registers[0xF] = 0;
	}
	m_registers[VX] = m_registers[VY] - m_registers[VX];
}

// set VX <<= 1 (set/unset VF if it was set)
void CPU::op8XYE(BYTE VX, BYTE VY) {
	printf("8XYE: %x %x\n", VX, VY);
	m_registers[0xF] = m_registers[VX] & 0b10000000;
	m_registers[VX] <<= 1;
}

// Skip if VX != VY
void CPU::op9XY0(BYTE VX, BYTE VY) {
	printf("9XY0: %x %x\n", VX, VY);
	if (m_registers[VX] != m_registers[VY]) {
		m_programCounter += 2;
	}
}

// Set I to address NNN
void CPU::opANNN(WORD addr) {
	m_addressI = addr;
	printf("ANNN: %x\n", addr);
}

// Jump to address NNN + V0
void CPU::opBNNN(WORD addr) {
	printf("BNNN: %x\n", addr);
	m_programCounter = addr + m_registers[0];
}

// Set VX = rand() & NN
void CPU::opCXNN(BYTE VX, BYTE data) {
	srand(time(NULL));
	m_registers[VX] = rand() & data;
	printf("CXNN %x\n", m_registers[VX]);
}

// Draw sprite at (VX, VY) (set VF if pixels are unset, unset otherwise)
void CPU::opDXYN(BYTE VX, BYTE VY, BYTE height) {
	BYTE x = m_registers[VX]%64;
	BYTE y = m_registers[VY]%32;
	m_registers[0xF] = 0;

	for (unsigned int row = 0; row < height; row++) {

		BYTE spriteByte = m_ram->get(m_addressI + row);

		for (int col = 0; col < 8; col++) {
			
			BYTE spritePixel = spriteByte & (0x80 >> col);
			BYTE screenPixel = m_ram->getScreen(x+col, y+row);

			if (spritePixel) {
				if (screenPixel == 0xFFFF) {
					m_registers[0xF] = 1;
				}
			}

			m_ram->setScreen(x+col, y+row, screenPixel ^= 0xFFFF);
		}
	}
	printf("DXYN: %x %x %x\n", VX, VY, height);
	for (int i = 0x200; i < 0xFFF; i++) {
		printf("%x", m_ram->get(i));
	}
	printf("\n");
}

// Skip if key in VX is pressed
void CPU::opEX9E(BYTE VX) {
	printf("EX9E: %x\n", VX);
}

// Skip if key in VX is not pressed
void CPU::opEXA1(BYTE VX) {
	printf("EXA1: %x\n", VX);
}

// Set VX to value of delay timer
void CPU::opFX07(BYTE VX) {
	printf("FX07: %x\n", VX);
	m_registers[VX] = m_delayTimer;
}

// Wait for keypress and store in VX (halt instruction until key event, continue delay and sound timers)
void CPU::opFX0A(BYTE VX) {
	printf("FX07: %x\n", VX);
	m_registers[VX] = getKey();
}

// Set delay timer to VX
void CPU::opFX15(BYTE VX) {
	printf("FX07: %x\n", VX);
	m_delayTimer = m_registers[VX];
}

// Set sound timer to VX
void CPU::opFX18(BYTE VX) {
	printf("FX07: %x\n", VX);
	m_soundTimer = m_registers[VX];
}

// I += VX
void CPU::opFX1E(BYTE VX) {
	printf("FX07: %x\n", VX);
	m_addressI += VX;
}

// I = VX
void CPU::opFX29(BYTE VX) {
	printf("FX07: %x\n", VX);
	m_addressI = VX;
}

// Store BCD representation of VX: 100s in I, 10s in I+1, 1s in 1+2
void CPU::opFX33(BYTE VX) {
	printf("FX33: %x\n", VX);
	m_ram->set(m_addressI, m_registers[VX] / 100);			// hundreds
	m_ram->set(m_addressI+1, (m_registers[VX] / 10) % 10);	// tens
	m_ram->set(m_addressI+2, m_registers[VX] % 10);			// ones
}

// Store from V0 to VX starting at address I (offset I for each value)
void CPU::opFX55(BYTE VX) {
	printf("FX07: %x\n", VX);
	for (int i = 0; i < VX + 1; i++) {
		m_ram->set(m_addressI+i, m_registers[i]);
	}
}

// Fills from V0 to VX starting at address I (offset I for each value)
void CPU::opFX65(BYTE VX) {
	printf("FX07: %x\n", VX);
	for (int i = 0; i < VX + 1; i++) {
		m_registers[i] = m_ram->get(m_addressI + i);
	}
}