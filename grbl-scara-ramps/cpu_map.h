/*
  cpu_map.h - CPU and pin mapping configuration file
  Part of Grbl

  Copyright (c) 2012-2015 Sungeun K. Jeon

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef GRBL_PLATFORM
#error "cpu_map already defined: GRBL_PLATFORM=" GRBL_PLATFORM
#endif

#define GRBL_PLATFORM "Atmega2560"

// Serial port pins
#define SERIAL_RX USART0_RX_vect
#define SERIAL_UDRE USART0_UDRE_vect


// Define AXIS pinout RAMPS 1.4 see stepper.c
#define X_STP_BIT	0 // MEGA 2560 A0
#define Y_STP_BIT	6 // MEGA 2560 A6
#define XY_STP_DDR	DDRF
#define XY_STP_PIN	PINF
#define XY_STP_PORT	PORTF
#define XY_STP_MASK ((1<<X_STP_BIT)|(1<<Y_STP_BIT))

#define X_DIR_BIT	1 // MEGA 2560 A1
#define Y_DIR_BIT	7 // MEGA 2560 A7
#define XY_DIR_DDR	DDRF
#define XY_DIR_PIN	PINF
#define XY_DIR_PORT	PORTF
#define XY_DIR_MASK ((1<<X_DIR_BIT)|(1<<Y_DIR_BIT))

#define X_ENA_DDR	DDRD
#define X_ENA_PORT	PORTD
#define X_ENA_BIT	7 // MEGA 2560 D38

#define Y_ENA_DDR	DDRF
#define Y_ENA_PORT  PORTF
#define Y_ENA_BIT   2 // MEGA 2560 A2

#define Z_STP_DDR   DDRL
#define Z_STP_PIN   PINL
#define Z_STP_PORT  PORTL
#define Z_STP_BIT   3 // MEGA 2560 D46

#define Z_DIR_DDR	DDRL
#define Z_DIR_PIN	PINL
#define Z_DIR_PORT	PORTL
#define Z_DIR_BIT	  1 // MEGA 2560 D48

#define Z_ENA_DDR   DDRK
#define Z_ENA_PORT  PORTK
#define Z_ENA_BIT   0 // MEGA 2560 A8

#define A_STP_DDR   DDRA
#define A_STP_PIN   PINA
#define A_STP_PORT  PORTA
#define A_STP_BIT   4 // MEGA 2560 D26

#define A_DIR_DDR	DDRA
#define A_DIR_PIN	PINA
#define A_DIR_PORT	PORTA
#define A_DIR_BIT	6 // MEGA 2560 D28

#define A_ENA_DDR   DDRA
#define A_ENA_PORT  PORTA
#define A_ENA_BIT   2 // MEGA2560 D24

// RAMPS D9 MOSFET GCODE M8-ON/M9-OFF
#define COOLANT_FLOOD_DDR   DDRH
#define COOLANT_FLOOD_PORT  PORTH
#define COOLANT_FLOOD_BIT   6 // MEGA 2560 D9

// RAMPS D10 MOSFET GCODE M7-ON/M9-OFF
#define COOLANT_MIST_DDR	DDRB
#define COOLANT_MIST_PORT   PORTB
#define COOLANT_MIST_BIT    4 // MEGA 2560 D10


// Start of PWM & Stepper Enabled Spindle / Laser M3SXXX / M5
#ifdef VARIABLE_SPINDLE
	#define PWM_MAX_VALUE     	65535.0
	#define OCR_REGISTER		OCR4A  // D6
	#define COMB_BIT			COM4A1 
	#define SPINDLE_PWM_DDR		DDRH
	#define SPINDLE_PWM_BIT		3   // MEGA 2560 D6, see spindle_control.c
	#define RC_SERVO_SHORT     13   // Pen down  (min - 9 for 0.6ms)
    #define RC_SERVO_LONG      28   // Pen up   (max - 39 for 2.5ms) 
	#define RC_SERVO_INVERT     1   //invert servo direction
#endif // End of VARIABLE_SPINDLE

// Define homing/hard limit switch input pins and limit interrupt vectors. 
// NOTE: All limit bit pins must be on the same port
#define LIMIT_DDR       DDRE
#define LIMIT_PORT      PORTE
#define LIMIT_PIN       PINE
#define X_LIMIT_BIT     5   	// MEGA2560 A9
#define Y_LIMIT_BIT     4   	// MEGA2560 A10
#define Z_LIMIT_BIT     3   	// MEGA2560 A11
#define LIMIT_INT       PCIE0   // Pin change interrupt enable pin
#define LIMIT_INT_vect  PCINT0_vect 
#define LIMIT_PCMSK     PCMSK0  // Pin change interrupt register
#define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)) // All limit bits

// Define probe switch input pin.
#define PROBE_DDR       DDRH
#define PROBE_PIN       PINH
#define PROBE_PORT      PORTH
#define PROBE_BIT       4  // MEGA2560 D6
#define PROBE_MASK      (1<<PROBE_BIT)

// Define user-control CONTROLs (cycle start, reset, feed hold) input pins.
// NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
#define CONTROL_DDR       DDRB
#define CONTROL_PIN       PINB
#define CONTROL_PORT      PORTB
#define RESET_BIT         3    // MEGA2560 D10
#define FEED_HOLD_BIT     5    // MEGA2560 D11
#define CYCLE_START_BIT   6    // MEGA2560 D12
#define SAFETY_DOOR_BIT   7    // MEGA2560 D13
#define CONTROL_INT       PCIE2   // Pin change interrupt enable pin
#define CONTROL_INT_vect  PCINT2_vect
#define CONTROL_PCMSK     PCMSK2  // Pin change interrupt register
#define CONTROL_MASK ((1<<RESET_BIT)|(1<<FEED_HOLD_BIT)|(1<<CYCLE_START_BIT)|(1<<SAFETY_DOOR_BIT))
#define CONTROL_INVERT_MASK CONTROL_MASK // May be re-defined to only invert certain control pins.

