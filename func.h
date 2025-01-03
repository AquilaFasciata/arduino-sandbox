#include <stddef.h>
#include <stdint.h>

typedef enum { BUSY, FREE } AVAILABLE;
typedef enum { CONTROLLER, RAM } REGSEL;
typedef enum { LEFT, RIGHT } CURSORDIR;

static AVAILABLE isLcdBusy();
void busyWait();
void lcdDataWrite(uint8_t data, REGSEL selregister);
void initLcd();
void ledBlink();
void lcdClear();
void lcdShiftCursor(int positions, CURSORDIR direction);
void lcdPrintn(char *str, size_t num);
