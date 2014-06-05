

/**
 * hitechnic-angle.h provides an API for the HiTechnic Angle Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Removed common.h from includes
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * date 20 February 2011
 * version 0.2
 */

#include "hitechnic-angle.h"

task main () {
  nNxtButtonTask  = -2;
  displayCenteredTextLine(0, "HiTechnic");
  displayCenteredBigTextLine(1, "Angle");
  displayCenteredTextLine(3, "Test 1");
  displayCenteredTextLine(5, "Connect sensor");
  displayCenteredTextLine(6, "to S1");
  sleep(2000);

  eraseDisplay();
  displayCenteredTextLine(0, "HiTechnic Angle");
  displayTextLine(1, "-------------------");
  displayTextLine(5, "-------------------");

  // Create struct to hold sensor data
  tHTANG angleSensor;

  // Initialise and configure struct and port
  initSensor(&angleSensor, S1);

  while (true) {

    // Reset all the values in the sensor
    if (nNxtButtonPressed == kEnterButton) {
      resetSensor(&angleSensor);
      while (nNxtButtonPressed != kNoButton) EndTimeSlice();
    }

    // If the left button is pressed, set the 0 point to the current angle
    else if (nNxtButtonPressed == kLeftButton) {
      resetAngle(&angleSensor);
      while (nNxtButtonPressed != kNoButton) EndTimeSlice();

    // Reset the total accumulated angle to 0
    } else if (nNxtButtonPressed == kRightButton) {
       resetAccmulatedAngle(&angleSensor);
      while (nNxtButtonPressed != kNoButton) EndTimeSlice();
    }

    // Read the data from the sensor
    readSensor(&angleSensor);
    displayTextLine(2, "Ang: %7d deg", angleSensor.angle);
    displayTextLine(3, "Tot: %7d deg", angleSensor.accumlatedAngle);
    displayTextLine(4, "RPM: %7d", angleSensor.rpm);
    displayTextLine(6, " < Set angle");
    displayTextLine(7, "   Reset total >");
    sleep(50);
  }
}
