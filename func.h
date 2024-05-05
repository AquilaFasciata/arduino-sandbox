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
