/*!@addtogroup mindsensors
 * @{
 * 	EV3Lights
 * @{
 */

/** \file mindsensors-ev3lights.h
 * \brief Mindsensors EV3 Lights driver
 *
 * mindsensors-ev3lights.h provides an API for the Mindsensors EV3 Lights LEDs
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to my son who push me write this file
 *   Huge thanks to Xander Soldat aka botbench for common files
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * \author andrey kudryashov aka dr
 * \date 24 September 2017
 * \version 0.1
 * \example mindsensors-ev3lights.c
 */

#pragma systemFile

#ifndef __COMMON_H__
#include "common.h"
#endif

#define EV3LIGHTS_I2C_ADDR     0x2c  /*!< EV3LIGHTS I2C device address */

#define EV3LIGHTS_RED          0x44  /*!< Intensity of RED   LEDs 0-255 */
#define EV3LIGHTS_GREEN        0x43  /*!< Intensity of GREEN LEDs 0-255 */
#define EV3LIGHTS_BLUE         0x42  /*!< Intensity of BLUE  LEDs 0-255 */

// Taken from Mindsensor's NXC lib
typedef enum tEV3LightsColor
{
	colorRed     = EV3LIGHTS_RED,
	colorGreen   = EV3LIGHTS_GREEN,
	colorBlue    = EV3LIGHTS_BLUE
} tEV3LightsColor;

tByteArray EV3LIGHTS_I2CRequest;       /*!< Array to hold I2C command data */

bool EV3Lights(tSensors link, tEV3LightsColor color, ubyte command, ubyte address = EV3LIGHTS_I2C_ADDR);


bool EV3Lights(tSensors link, tEV3LightsColor color, ubyte command, ubyte address) {
  memset(EV3LIGHTS_I2CRequest, 0, sizeof(tByteArray));

  EV3LIGHTS_I2CRequest[0] = 3;               // Number of bytes in I2C command
  EV3LIGHTS_I2CRequest[1] = address;         // I2C address of sensor
  EV3LIGHTS_I2CRequest[2] = (ubyte)color;           // Set write address to sensor mode register
  EV3LIGHTS_I2CRequest[3] = command;         // Command to be sent to the sensor

  return writeI2C(link, EV3LIGHTS_I2CRequest);
}
