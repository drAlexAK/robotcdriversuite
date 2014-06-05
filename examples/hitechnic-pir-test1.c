#pragma config(Sensor, S1,     HTPIR,                sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * hitechnic-pir.h provides an API for the HiTechnic PIR Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * 26 August 2012
 * version 0.1
 */

#include "hitechnic-pir.h"

// Draw a little stick figure
void drawStickFigure(short offset)
{
  eraseRect(0, 0, 99, 50);
  drawCircle(offset + 43, 40, 15);
  drawLine(offset + 50,25,offset + 50,10);
  drawLine(offset + 43, 22, offset + 58, 22);
  drawLine(offset + 43, 0, offset + 50, 10);
  drawLine(offset + 50, 10, offset + 58, 0);
}

task main () {
  short reading = 0;
  short x = 0;
  short deadband = HTPIR_DEFAULT_DEADBAND;

  displayCenteredTextLine(0, "HiTechnic");
  displayCenteredBigTextLine(1, "PIR");
  displayCenteredTextLine(3, "Test 1");
  displayCenteredTextLine(6, "L/ENTER/R");
  displayCenteredTextLine(7, "change deadband");

  sleep(2000);
  eraseDisplay();

  while(true) {
    if (nNxtButtonPressed != kNoButton)
    {
      switch (nNxtButtonPressed)
      {
        case kRightButton: deadband++; break;
        case kLeftButton:  deadband--; break;
        case kEnterButton: deadband = HTPIR_DEFAULT_DEADBAND; break;
      }

      // Make sure the value stays between 0 and 47
      deadband = clip(deadband, 0, 47);

      // Debounce
      while (nNxtButtonPressed != kNoButton) EndTimeSlice();

      // Set the new dead band value.
      HTPIRsetDeadband(HTPIR, deadband);
    }

    // Get the IR levels from the PIR sensor
    reading = HTPIRreadSensor(HTPIR);
    displayTextLine(0, "HT PIR %d / %d", deadband, reading);

    // Draw a cool little stick figure
    x = (40 * reading) / 100;
    drawStickFigure(x);
    sleep(50);

  }
}
