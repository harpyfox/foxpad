/*
Copyright 2020 imchipwood
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once


/* Column/Row IO definitions */
#define MATRIX_ROWS 4
#define MATRIX_COLS 5

#define MATRIX_ROW_PINS { F4, F5, F6, F7 }
#define MATRIX_COL_PINS { C6, B1, B3, B2, B6 }

/* Dual rotary encoders */
#define ENCODERS_PAD_A { B4, E6 }
#define ENCODERS_PAD_B { B5, D7 }

// UNMAPPED PINS:
// D1, D8?, D4, D2, D3

/* Column/Row IO definitions */
#define DIODE_DIRECTION COL2ROW

/* Configure SPI peripheral */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP22
#define SPI_MISO_PIN GP20
#define SPI_MOSI_PIN GP23
// can use GP21 as slave pin.

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED 17U