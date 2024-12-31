#include <stdint.h>

typedef enum { BUSY, FREE } AVAILABLE;

typedef enum { CONTROLLER, RAM } REGSEL;

AVAILABLE isLcdBusy();

void busyWait();

void lcdDataWrite(uint8_t data, REGSEL selregister);

void initLcd();

void ledBlink();

void lcdClear();
