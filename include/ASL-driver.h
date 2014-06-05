/*!@addtogroup Lizard
 * @{
 * @defgroup ASLc <SENSOR> Sensor
 * Lizard Technologies <SENSOR>
 * @{
 */

#ifndef __ASL_H__
#define __ASL_H__
/** \file ASL-driver.h
 * \brief <DESCRIPTION> Sensor driver
 *
 * ASL-driver.h provides an API for the <SENSOR> Sensor.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to <MANUFACTURER> for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * \author Xander Soldaat (xander_at_botbench.com)
 * \date 04 February 2012
 * \version 0.1
 * \example ASL-test1.c
 */

#pragma systemFile

#ifndef __COMMON_H__
#include "common.h"
#endif

#define ASL_ADDRESS 0x10
#define REG_DYN_ANGLE 66
#define REG_STAT_ANGLE 69

#define ASL_I2C_ADDR        0x10      /*!< ASL I2C device address */
#define ASL_REG_DYN_ANGLE   0x42      /*!< XXXXXXXXXXX */
#define ASL_REG_STAT_ANGLE  0x45      /*!< XXXXXXXXXXX */
#define ASL_REG_RIGHT_MIC   0x48      /*!< XXXXXXXXXXX */
#define ASL_REG_LEFT_MIC    0x49      /*!< XXXXXXXXXXX */
#define ASL_REG_COMBO_MIC   0x4A      /*!< XXXXXXXXXXX */

short ASLreadStaticAngle(tSensors link, bool reversed=false);
short ASLreadDynamicAngle(tSensors link, bool reversed=false);
short ASLreadThresholdAngle(tSensors link, ubyte threshold, bool reversed=false);
short ASLreadAngle(tSensors link, byte reg, bool reversed=false);
bool ASLreadMICS(tSensors link, short &rmic, short &lmic, short &bmic, bool reversed=false);

short ASLoldAngle[4] = {0, 0, 0, 0};

tByteArray ASL_I2CRequest;    /*!< Array to hold I2C command data */
tByteArray ASL_I2CReply;      /*!< Array to hold I2C reply data */

/**
 * Read the angle value, 90 indicates no sound or sound straight ahead.
 * @param link the ASL port number
 * @param reversed indicate whether L and R should be reversed (if the sensor is mounted upside down)
 * @return the angle of the sound direction.
 */
short ASLreadAngle(tSensors link, byte reg, bool reversed) {
  short angle = 0;
  memset(ASL_I2CRequest, 0, sizeof(tByteArray));

  ASL_I2CRequest[0] = 2;                // Message size
  ASL_I2CRequest[1] = ASL_I2C_ADDR;     // I2C Address
  ASL_I2CRequest[2] = reg;              // register to read

  if (!writeI2C(link, ASL_I2CRequest, ASL_I2CReply, 1))
    return -1;

  angle = (short)ASL_I2CReply[0] & 0xFF;
  if (reversed)
    angle = 180 -angle;
  return angle;
}

/**
 * Read the static angle value, 90 indicates no sound or sound straight ahead.
 * @param link the ASL port number
 * @param reversed indicate whether L and R should be reversed (if the sensor is mounted upside down)
 * @return the angle of the sound direction.
 */
short ASLreadStaticAngle(tSensors link, bool reversed) {
  return ASLreadAngle(link, ASL_REG_STAT_ANGLE, reversed);
}

/**
 * Read the dynamic angle value, 90 indicates no sound or sound straight ahead.
 * @param link the ASL port number
 * @param reversed indicate whether L and R should be reversed (if the sensor is mounted upside down)
 * @return the angle of the sound direction.
 */
short ASLreadDynamicAngle(tSensors link, bool reversed) {
  return ASLreadAngle(link, ASL_REG_DYN_ANGLE, reversed);
}

short ASLreadThresholdAngle(tSensors link, ubyte threshold, bool reversed)
{
  short angle = 0;

  ASL_I2CRequest[0] = 2;                 // Message size
  ASL_I2CRequest[1] = ASL_I2C_ADDR;      // I2C Address
  ASL_I2CRequest[2] = ASL_REG_COMBO_MIC;

  if (!writeI2C(link, ASL_I2CRequest, ASL_I2CReply, 1))
    return 0;

  writeDebugStreamLine("level: %d, %d", ASL_I2CReply[0], threshold);
  if (ASL_I2CReply[0] > threshold)
    return ASLreadDynamicAngle(link, reversed);

  return -1;
}

/**
 * Read the mic values.
 * @param link the ASL port number
 * @param reversed indicate whether L and R should be reversed (if the sensor is mounted upside down)
 * @return the angle of the sound direction.
 */
bool ASLreadMICS(tSensors link, short &rmic, short &lmic, short &bmic, bool reversed)
{
  short angle = 0;
  short micvalues[3] = {0, 0, 0};

  memset(ASL_I2CRequest, 0, sizeof(tByteArray));

  ASL_I2CRequest[0] = 2;                 // Message size
  ASL_I2CRequest[1] = ASL_I2C_ADDR;      // I2C Address

  // You can only read one byte at a time.
  for (short i = 0; i < 3; i++) {
    ASL_I2CRequest[2] = ASL_REG_RIGHT_MIC + i; // Read the appropriate mic register

    if (!writeI2C(link, ASL_I2CRequest, ASL_I2CReply, 1))
      return false;

    micvalues[i] = (short)ASL_I2CReply[0] & 0xFF;
  }

  rmic = (reversed) ? micvalues[1] : micvalues[0];
  lmic = (reversed) ? micvalues[0] : micvalues[1];
  bmic = micvalues[2];
  return true;
}

short ASLcalibrateLevel(tSensors link)
{
  long total = 0;

  memset(ASL_I2CRequest, 0, sizeof(tByteArray));

  ASL_I2CRequest[0] = 2;                 // Message size
  ASL_I2CRequest[1] = ASL_I2C_ADDR;      // I2C Address
  ASL_I2CRequest[2] = ASL_REG_COMBO_MIC; // Read the appropriate mic register

  for (short i = 0; i < 100; i++) {
    if (!writeI2C(link, ASL_I2CRequest, ASL_I2CReply, 1))
      return 0;

    total += (short)ASL_I2CReply[0] & 0xFF;
    sleep(5);
  }
  return total / 100;
}

#endif // __ASL_H__

/* @} */
/* @} */
