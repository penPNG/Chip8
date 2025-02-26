#include "keyboard.h"

// Keypad               Keyboard
// + - + - + - + - +    + - + - + - + - +
// | 1 | 2 | 3 | C |    | 1 | 2 | 3 | 4 |
// + - + - + - + - +    + - + - + - + - +
// | 4 | 5 | 6 | D |    | Q | W | E | R |
// + - + - + - + - + => + - + - + - + - +
// | 7 | 8 | 9 | E |    | A | S | D | F |
// + - + - + - + - +    + - + - + - + - +
// | A | 0 | B | F |    | Z | X | C | V |
// + - + - + - + - +    + - + - + - + - +

unsigned char getKey(BYTE* keys) {
    // TODO: use SDL key events to return key as a 4-bit value
    for (BYTE i = 0; i < sizeof(*keys); i++) {
        if (keys[i]) {
            return i;
        }
    }
    return 0;
}