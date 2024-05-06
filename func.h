typedef enum {
	BUSY,
	FREE
} AVAILABLE;

typedef enum {
  CONTROLLER,
  LCDRAM
} REGSEL;

AVAILABLE isLcdBusy();

void busyWait();

void lcdDataWrite(uint8_t data, REGSEL selregister);

void initLcd();