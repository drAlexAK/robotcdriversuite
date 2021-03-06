#pragma config(Sensor, S1,     MSSMUX,         sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * mindsensors-sensormux.h provides an API for the Mindsensors SensorMUX Sensor.
 * This program demonstrates how to create a small disco party in your LEGO room
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
 * 30 March 2010
 * version 0.1
 */

// Copy these to your brick
#define MONNKEY01 "monkey01.ric"
#define MONNKEY02 "monkey02.ric"
#define MONNKEY03 "monkey03.ric"
#define MONNKEY04 "monkey04.ric"
#define MONNKEY05 "monkey05.ric"
#define MONNKEY06 "monkey06.ric"
#define MONNKEY07 "monkey07.ric"

#include "mindsensors-sensormux.h"

tSensors disco[] = {sensorColorNxtGREEN, sensorColorNxtBLUE, sensorColorNxtRED};

task danceMOnkeyDance()
{
  const short X_COORD = 30;
  const short Y_COORD = 0;
  const short WAITTIME = 100;

  while (true) {
    displayRICFile(X_COORD,Y_COORD, MONNKEY01);
    sleep(WAITTIME);
    displayRICFile(X_COORD,Y_COORD, MONNKEY02);
    sleep(WAITTIME);
    displayRICFile(X_COORD,Y_COORD, MONNKEY03);
    sleep(WAITTIME);
    displayRICFile(X_COORD,Y_COORD, MONNKEY04);
    sleep(WAITTIME);
    displayRICFile(X_COORD,Y_COORD, MONNKEY05);
    sleep(WAITTIME);
    displayRICFile(X_COORD,Y_COORD, MONNKEY06);
    sleep(WAITTIME);
    displayRICFile(X_COORD,Y_COORD, MONNKEY07);
    sleep(WAITTIME);
  }
}

task main()
{
  long counter = 0;
  displayCenteredTextLine(0, "Mindsensors");
  displayCenteredBigTextLine(1, "SnsrMUX");
  displayCenteredTextLine(3, "Test 2");
  displayCenteredTextLine(5, "Connect LEGO");
  displayCenteredTextLine(6, "Color Sensors");
  displayCenteredTextLine(7, "to ports 1-4");

  sleep(2000);
  eraseDisplay();
  startTask(danceMOnkeyDance);

  // Let's get the party started!
  while(true)
  {
    // Set the channel to a random one
    MSSMUXsetChan(MSSMUX, (counter++%4) + 1);
    // Set the sensor to a random colour, R, G or B
    SensorType[MSSMUX] = disco[abs(rand() % 3)];
    // Wait a random time before switching
    sleep(abs(rand() % 100) + 100);
    // Do a little dance!
  }
}
