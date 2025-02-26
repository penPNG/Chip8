#pragma once
#include <time.h>
#include "bytes.h"
#include "memory.h"
#include "keyboard.h"

class CPU {
public:
	CPU();
	CPU(Memory*);

	void reset();
	BYTE getReg(BYTE);
	WORD getPC();
	void decTimer();
	bool decSound();
	void setReg(BYTE, BYTE);
	void setPC(WORD);
	void incPC();
	void compute(WORD);

public:
	BYTE m_keys[16]{ 0 };

private:
	Memory *m_ram;
	BYTE m_registers[17];
	BYTE m_soundTimer;
	BYTE m_delayTimer;
	WORD m_addressI;
	WORD m_programCounter;

// opcode functions
private:

	void op00E0();		// Clear the screen
	void op00EE();		// Return from subrtn
	void op1NNN(WORD);	// Jump to address
	void op2NNN(WORD);	// Call subrtn
	void op3XNN(BYTE, BYTE);	// Skip if VX == NN
	void op4XNN(BYTE, BYTE);	// Skip if VX != NN
	void op5XY0(BYTE, BYTE);	// Skip if VX == VY
	void op6XNN(BYTE, BYTE);	// Set VX = NN
	void op7XNN(BYTE, BYTE);	// Set VX += NN
	void op8XY0(BYTE, BYTE);	// Set VX = VY
	void op8XY1(BYTE, BYTE);	// set VX |= VY (bitwise OR)
	void op8XY2(BYTE, BYTE);	// Set VX &= VY (bitwise AND)
	void op8XY3(BYTE, BYTE);	// Set VX ^= VY (bitwise XOR)
	void op8XY4(BYTE, BYTE);	// Set VX += VY (set/unset VF if overflow)
	void op8XY5(BYTE, BYTE);	// Set VX -= VY (set/unset VF if underflow (VX >= VY))
	void op8XY6(BYTE, BYTE);	// set VX >>= 1 (store 0x0X to F)
	void op8XY7(BYTE, BYTE);	// set VX = VY - VX (set/unset VF if underflow (VY >= VX))
	void op8XYE(BYTE, BYTE);	// set VX <<= 1 (set/unset VF if it was set)
	void op9XY0(BYTE, BYTE);	// Skip if VX != VY
	void opANNN(WORD);	// Set I to address NNN
	void opBNNN(WORD);	// Jump to address NNN + V0
	void opCXNN(BYTE, BYTE);	// Set VX = rand() & NN
	void opDXYN(BYTE, BYTE, BYTE);	// Draw sprite at (VX, VY) (set VF if pixels are unset, unset otherwise)
	void opEX9E(BYTE);	// Skip if key in VX is pressed
	void opEXA1(BYTE);	// Skip if key in VX is not pressed
	void opFX07(BYTE);	// Set VX to value of delay timer
	void opFX0A(BYTE);	// Wait for keypress and store in VX (halt instruction until key event, continue delay and sound timers)
	void opFX15(BYTE);	// Set delay timer to VX
	void opFX18(BYTE);	// Set sound timer to VX
	void opFX1E(BYTE);	// I += VX
	void opFX29(BYTE);	// I = VX
	void opFX33(BYTE);	// Store BCD representation of VX: 100s in I, 10s in I+1, 1s in 1+2
	void opFX55(BYTE);	// Store from V0 to VX starting at address I (offset I for each value)
	void opFX65(BYTE);	// Fills from V0 to VX starting at address I (offset I for each value)
};