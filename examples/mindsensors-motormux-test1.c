#pragma config(Sensor, S1,     MSMMUX,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * mindsensors-motormux.h provides an API for the Mindsensors Motor MUX. This program
 * demonstrates how to use that API to control the motors attached to the MUX.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * 05 April 2010
 * version 0.1
 */

#include "mindsensors-motormux.h"

task main () {
  long encA  = 0;
  long encB  = 0;

  string motorAstatus = "";
  string motorBstatus = "";

  eraseDisplay();
  MSMMUXinit();

  MSMotorStop(mmotor_S1_1);
  MSMotorStop(mmotor_S1_2);
  playSound(soundBeepBeep);
  sleep(500);

  // Reset the encoders.  This can be done individually or all at once.
  // You should do this at the start of your program.
  MSMMotorEncoderResetAll(MSMMUX);

  // These are actually the default values for the PID controller
  MSMMUXsetPID(MSMMUX, 0x1B58, 0x0000, 0x927C, 0x3A98, 0x012c, 0x1D4C, 0x10, 0x80);

  // Reset the encoders for each motor
  MSMMotorEncoderReset(mmotor_S1_1);
  MSMMotorEncoderReset(mmotor_S1_2);

  // You can specify the type of braking that should be used when the motors
  // are sent the stop command.  The default is to use brake.
  MSMMotorSetBrake(mmotor_S1_1);
  MSMMotorSetBrake(mmotor_S1_2);

  // Specify a target for the motors to run to.  This can be number of
  // rotations, seconds or degrees (encoder count).  Rotations and seconds
  // may be specified in increments of 0.01.
  //MSMMotorSetEncoderTarget(mmotor_S1_1, 360);
  //MSMMotorSetTimeTarget(mmotor_S1_2, 3);

  //sleep(2000);
  // Tell the motors to start moving.
  MSMMotor(mmotor_S1_1, 50);
  MSMMotor(mmotor_S1_2, 90);

  while (true) {
    switch(nNxtButtonPressed) {
      case kLeftButton:
        MSMMotorEncoderReset(mmotor_S1_1);
        while(nNxtButtonPressed != kNoButton) EndTimeSlice();
        break;
      case kRightButton:
        MSMMotorEncoderReset(mmotor_S1_2);
        while(nNxtButtonPressed != kNoButton) EndTimeSlice();
        break;
      case kEnterButton:
        MSMMotorEncoderResetAll(MSMMUX);
        while(nNxtButtonPressed != kNoButton) EndTimeSlice();
        break;
    }

    // Retrieve the motor-MUX's status info and encoder counts
    encA = MSMMotorEncoder(mmotor_S1_1);
    encB = MSMMotorEncoder(mmotor_S1_2);

    // Use the MSMMotorBusy() function to see if a motor is busy or idle.
    motorAstatus = MSMMotorBusy(mmotor_S1_1) ? "busy" : "idle";
    motorBstatus = MSMMotorBusy(mmotor_S1_2) ? "busy" : "idle";

    // Display the info.
    displayTextLine(5, "A: %5d (%s)", encA, motorAstatus);
    displayTextLine(6, "B: %5d (%s)", encB, motorBstatus);
    sleep(20);
  }

  while(true) EndTimeSlice();
}
