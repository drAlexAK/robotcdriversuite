#pragma config(Sensor, S1,     LEGOTMP,             sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * lego-temp.h provides an API for the Lego Temperature Sensor.  This program
 * demonstrates how to use that API to use the sensor in continuous mode.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Sylvain Cacheux for writing the initial drivers.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * 16 february 2010
 * version 0.1
 */

#include "lego-temp.h"

void accuracyToString(tLEGOTMPAccuracy _accuracy, string &text) {
  strcpy(text, "");
  switch (_accuracy) {
    case A_MIN:
      text = "A_MIN";
      break;
    case A_MEAN1:
      text = "A_MEAN1";
      break;
    case A_MEAN2:
      text = "A_MEAN2";
      break;
    case A_MAX:
      text = "A_MAX";
      break;
  }
}

task main() {
  float temp;
  tLEGOTMPAccuracy accuracy;
  string strAcc;

  displayCenteredTextLine(0, "LEGO");
  displayCenteredBigTextLine(1, "Temp");
  displayCenteredTextLine(3, "Test 1");
  displayCenteredTextLine(5, "Connect sensor");
  displayCenteredTextLine(6, "to S1");
  sleep(2000);
  eraseDisplay();

  // Setup the sensor for continuous mode
  LEGOTMPsetContinuous(LEGOTMP);

  //setting minimum accuracy
  accuracy = A_MIN;
  if (!LEGOTMPsetAccuracy(LEGOTMP, accuracy)) {
    displayTextLine(0, "Error setAccuracy");
    sleep(5000);
    stopAllTasks();
  }

  //reads the current accuracy of the sensor
  if (!LEGOTMPreadAccuracy(LEGOTMP, accuracy)) {
    displayTextLine(0, "Error readAccuracy");
    sleep(5000);
    stopAllTasks();
  }

  accuracyToString(accuracy, strAcc);
  displayTextLine(0, "Accuracy: %s", strAcc);

  //loop to read temp
  while (true) {
    switch(nNxtButtonPressed) {
      // If the left button is pressed, decrease the accuracy
      case kLeftButton:
        switch(accuracy) {
          case A_MIN:   accuracy = A_MAX;   break;
          case A_MEAN1: accuracy = A_MIN;   break;
          case A_MEAN2: accuracy = A_MEAN1; break;
          case A_MAX:   accuracy = A_MEAN2; break;
        }
        if (!LEGOTMPsetAccuracy(LEGOTMP, accuracy)) {
          displayTextLine(0, "Error setAccuracy");
          sleep(5000);
          stopAllTasks();
        }
        accuracyToString(accuracy, strAcc);
        displayTextLine(0, "Accuracy: %s", strAcc);

        // debounce the button
        while (nNxtButtonPressed != kNoButton) sleep(1);
        break;

      // If the right button is pressed, increase the accuracy
      case kRightButton:
        switch(accuracy) {
          case A_MIN:   accuracy = A_MEAN1; break;
          case A_MEAN1: accuracy = A_MEAN2; break;
          case A_MEAN2: accuracy = A_MAX;   break;
          case A_MAX:   accuracy = A_MIN;   break;
        }
        if (!LEGOTMPsetAccuracy(LEGOTMP, accuracy)) {
          displayTextLine(0, "Error setAccuracy");
          sleep(5000);
          stopAllTasks();
        }
        accuracyToString(accuracy, strAcc);
        displayTextLine(0, "Accuracy: %s", strAcc);

        // debounce the button
        while (nNxtButtonPressed != kNoButton) sleep(1);
        break;
    }
    if (!LEGOTMPreadTemp(LEGOTMP, temp)) {
      eraseDisplay();
      displayTextLine(0, "Temp reading pb");
      sleep(100);
      stopAllTasks();
    }

    displayCenteredBigTextLine(2, "Temp:");
    switch(accuracy) {
      case A_MIN:   displayCenteredBigTextLine(4, "%4.1f", temp); break;
      case A_MEAN1: displayCenteredBigTextLine(4, "%5.2f", temp); break;
      case A_MEAN2: displayCenteredBigTextLine(4, "%6.3f", temp); break;
      case A_MAX:   displayCenteredBigTextLine(4, "%7.4f", temp); break;
    }
  }
}
