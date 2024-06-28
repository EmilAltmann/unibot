#ifndef _PIO_TOOL_H_
#define _PIO_TOOL_H_

#include "hardware/pio.h"

/*
// This header defines a stuct for adressing and interfacing with a PIO instnce.
*/

struct pio_inst {
	uint8_t pin;
	PIO pio;
	uint8_t sm;
};

#endif