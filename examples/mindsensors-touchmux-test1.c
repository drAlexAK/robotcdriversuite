#pragma config(Sensor, S1,     MSTMUX,              sensorLightInactive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * mindsensors-touchmux.h provides an API for the Mindsensors Touch Sensor MUX.  This program
 * demonstrates how to use that API.
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
 * 11-May-2010
 * version 0.1
 */

#include "mindsensors-touchmux.h"

task main () {
  displayCenteredTextLine(0, "Mindsensors");
  displayCenteredBigTextLine(1, "TMUX");
  displayCenteredTextLine(3, "Test 1");
  displayCenteredTextLine(5, "This is for the");
  displayCenteredTextLine(6, "Touch MUX");
  sleep(2000);
  while (true) {
    eraseDisplay();
    displayTextLine(0, "MS Touch MUX");

    // Get the raw data from the sensor, this is not processed
    // by the driver in any way.
    displayTextLine(1, "Raw: %d", SensorRaw[MSTMUX]);

    // Go through each possible touch switch attached to the TMUX
    // and display whether or not is active (pressed)
    for (short i = 1; i < 4; i++) {
      if (MSTMUXisActive(MSTMUX, i))
        displayTextLine(i+2, "Touch %d: on", i);
      else
        displayTextLine(i+2, "Touch %d: off", i);
    }

    // Display the binary value of the active touch switches
    // 0 = no touch, 1 = touch 1 active, 2 = touch 2 active, etc.
    // touch 1 + touch 2 active = 1 + 2 = 3.
    displayTextLine(7, "Status: %d", MSTMUXgetActive(MSTMUX));
    sleep(50);
  }
}
