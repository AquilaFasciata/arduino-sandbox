#include <stdint.h>

typedef enum { BUSY, FREE } AVAILABLE;
typedef enum { CONTROLLER, RAM } REGSEL;
typedef enum { LEFT, RIGHT } CURSORDIR;

AVAILABLE isLcdBusy();
void busyWait();
void lcdDataWrite(uint8_t data, REGSEL selregister);
void initLcd();
void ledBlink();
void lcdClear();
void lcdShiftCursor(int positions, CURSORDIR direction);
