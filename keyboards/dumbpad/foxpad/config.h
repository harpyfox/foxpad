// Copyright 2020 imchipwood
#pragma once

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Reduce tapdance required taps from 5 to 2 */
#define TAPPING_TOGGLE 2


/* Column/Row IO definitions */
#define MATRIX_ROWS 4
#define MATRIX_COLS 5

#define MATRIX_ROW_PINS { F4, F5, F6, F7 }
#define MATRIX_COL_PINS { C6, B1, B3, B2, B6 }

/* Dual rotary encoders */
#define ENCODERS_PAD_A { B4, E6 }
#define ENCODERS_PAD_B { B5, D7 }

/* Column/Row IO definitions */
#define DIODE_DIRECTION COL2ROW

/* Configure SPI peripheral */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP22
#define SPI_MISO_PIN GP20
#define SPI_MOSI_PIN GP23
// can use GP21 as slave pin.

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED 17U