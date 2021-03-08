/*
  spindle_control.c - spindle control methods
  Part of Grbl

  Copyright (c) 2012-2015 Sungeun K. Jeon
  Copyright (c) 2009-2011 Simen Svale Skogsrud

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

#include "grbl.h"


void spindle_init()
{    
  // Configure variable spindle PWM and enable pin, if requried. On the Uno, PWM and enable are
  // combined unless configured otherwise.

    SPINDLE_PWM_DDR |= (1<<SPINDLE_PWM_BIT); // Configure as PWM output pin.
	
	TCCR4A = (1<<COM4A1) | (1<<WGM41);
	TCCR4B = (1<<CS40) | (1<<CS42) | (1<<WGM43) | (1<<WGM42); // set to 1/1024 Prescaler
    ICR4 = 312; // set 20 msec
		
	spindle_stop();
}


void spindle_stop()
{     // On the Uno, spindle enable and PWM are shared. Other CPUs have seperate enable pin.
      #ifdef RC_SERVO_INVERT 
          OCR_REGISTER = RC_SERVO_LONG;
      #else
          OCR_REGISTER = RC_SERVO_SHORT;
      #endif    
}


void spindle_run(uint8_t direction, float rpm) 
{
  if (sys.state == STATE_CHECK_MODE) { return; }
  
  // Empty planner buffer to ensure spindle is set when programmed.
  protocol_auto_cycle_start();  //temp fix for M3 lockup
  protocol_buffer_synchronize(); 
  
  if (direction == SPINDLE_DISABLE) {

    spindle_stop();

  } else {

  
      // TODO: Install the optional capability for frequency-based output for servos.
      #define SPINDLE_RPM_RANGE (SPINDLE_MAX_RPM-SPINDLE_MIN_RPM)
      #define RC_SERVO_RANGE (RC_SERVO_LONG-RC_SERVO_SHORT)
	  
      	
       uint16_t current_pwm;

	   if ( rpm < SPINDLE_MIN_RPM ) { rpm = 0; } 
      else { 
        rpm -= SPINDLE_MIN_RPM; 
        if ( rpm > SPINDLE_RPM_RANGE ) { rpm = SPINDLE_RPM_RANGE; } // Prevent integer overflow
      }
	  
      #ifdef RC_SERVO_INVERT 
          current_pwm = floor( RC_SERVO_LONG - rpm*(RC_SERVO_RANGE/SPINDLE_RPM_RANGE));
          OCR_REGISTER = current_pwm;
      #else
         current_pwm = floor( rpm*(RC_SERVO_RANGE/SPINDLE_RPM_RANGE) + RC_SERVO_SHORT);
          OCR_REGISTER = current_pwm;
      #endif    
	  #ifdef MINIMUM_SPINDLE_PWM
        if (current_pwm < MINIMUM_SPINDLE_PWM) { current_pwm = MINIMUM_SPINDLE_PWM; }
	     OCR_REGISTER = current_pwm;
      #endif  
  }
}
spindle_set_state(uint8_t state, float rpm){
}
