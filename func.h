typedef enum {
	BUSY,
	FREE
} AVAILABLE;

AVAILABLE isLcdBusy();

void busyWait();
