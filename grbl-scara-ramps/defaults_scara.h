/*
  defaults_generic.h - defaults settings configuration file
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
 
  $0=10 (step pulse, usec)
  $1=25 (step idle delay, msec)
  $2=0 (step port invert mask:00000000)
  $3=0 (dir port invert mask:00000000)
  $4=0 (step enable invert, bool)
  $5=0 (limit pins invert, bool)
  $6=0 (probe pin invert, bool)
  $10=3 (status report mask:00000011)
  $11=0.020 (junction deviation, mm)
  $12=0.002 (arc tolerance, mm)
  $13=0 (report inches, bool)
  $20=0 (soft limits, bool)
  $21=0 (hard limits, bool)
  $22=0 (homing cycle, bool)
  $23=0 (homing dir invert mask:00000000)
  $24=0.000 (homing feed, mm/min)
  $25=0.000 (homing seek, mm/min)
  $26=0 (homing debounce, msec)
  $27=0.000 (homing pull-off, mm)
  $100=80.000 (x, step/mm)
  $101=80.000 (y, step/mm)
  $102=400.000 (z, step/mm)
  $103=8.888 (a, step/mm)
  $110=15000.000 (x max rate, mm/min)
  $111=15000.000 (y max rate, mm/min)
  $112=1500.000 (z max rate, mm/min)
  $113=15000.000 (a max rate, mm/min)
  $120=1500.000 (x accel, mm/sec^2)
  $121=1500.000 (y accel, mm/sec^2)
  $122=500.000 (z accel, mm/sec^2)
  $123=1500.000 (a accel, mm/sec^2)
  $130=320.000 (x max travel, mm)
  $131=200.000 (y max travel, mm)
  $132=50.000 (z max travel, mm)
  $133=360.000 (a max travel, mm)

*/
 
#ifndef defaults_h
#define defaults_h

// Grbl generic default settings. Should work across different machines.
#define DEFAULT_X_STEPS_PER_MM 48.8
#define DEFAULT_Y_STEPS_PER_MM 48.8
#define DEFAULT_Z_STEPS_PER_MM 48.8
#define DEFAULT_A_STEPS_PER_MM 48.8

#define DEFAULT_X_MAX_RATE 2000.0 // mm/min
#define DEFAULT_Y_MAX_RATE 2000.0 // mm/min
#define DEFAULT_Z_MAX_RATE 2000.0 // mm/min
#define DEFAULT_A_MAX_RATE 2000.0 // mm/min

#define DEFAULT_X_ACCELERATION 100     //(10.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
#define DEFAULT_Y_ACCELERATION 100  //(10.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
#define DEFAULT_Z_ACCELERATION 100  //(10.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
#define DEFAULT_A_ACCELERATION 100  //(10.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2

#define DEFAULT_X_MAX_TRAVEL 320.0 // mm
#define DEFAULT_Y_MAX_TRAVEL 220.0 // mm
#define DEFAULT_Z_MAX_TRAVEL 220.0 // mm
#define DEFAULT_A_MAX_TRAVEL 220.0 // mm

#define DEFAULT_STEP_PULSE_MICROSECONDS 10
#define DEFAULT_STEPPING_INVERT_MASK 0
#define DEFAULT_DIRECTION_INVERT_MASK 3
#define DEFAULT_STEPPER_IDLE_LOCK_TIME 150 // msec (0-254, 255 keeps steppers enabled)
#define DEFAULT_STATUS_REPORT_MASK ((BITFLAG_RT_STATUS_MACHINE_POSITION)|(BITFLAG_RT_STATUS_WORK_POSITION))
#define DEFAULT_JUNCTION_DEVIATION 0.01 // mm
#define DEFAULT_ARC_TOLERANCE 0.002 // mm
#define DEFAULT_REPORT_INCHES 0 // false
#define DEFAULT_INVERT_ST_ENABLE 0 // false
#define DEFAULT_INVERT_LIMIT_PINS 1 // false
#define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
#define DEFAULT_HARD_LIMIT_ENABLE 0  // false
#define DEFAULT_HOMING_ENABLE 1  // false
#define DEFAULT_HOMING_DIR_MASK 3 // move positive dir
#define DEFAULT_HOMING_FEED_RATE 100.0 // mm/min
#define DEFAULT_HOMING_SEEK_RATE 1000.0 // mm/min
#define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
#define DEFAULT_HOMING_PULLOFF 1.0 // mm
#define DEFAULT_SCARA_ARM1 200.0 // mm
#define DEFAULT_SCARA_ARM2 200.0 // mm
#define DEFAULT_SCARA_THETA 45.43 
#define DEFAULT_SCARA_PSI 95.67 

#endif