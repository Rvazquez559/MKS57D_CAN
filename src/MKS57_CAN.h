/* 
 * This file is part of the distribution (https://github.com/Rvazquez559/MKS57D_CAN).
 * Copyright (c) 2024 Roberto Vazquez.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MKS57_CAN_H
#define MKS57_CAN_H

#include <Arduino.h>
#include <ESP32-TWAI-CAN.hpp>

class MKS57_CAN{

    public:
//Constructor  set TX, RX, Baudrate & buffer size
    MKS57_CAN(int txPin, int rxPin, long baudRate, int txBuffer, int rxBuffer);

//Auxiliary functions

//Initialize interface with CAN and the MKS driver
    bool begin();
//Send position mode 4 command, indicate CAN id, speed, acceleration, absolute position in degrees
    void sendPositionMode4Message(int id, uint16_t speed, uint8_t acc, int32_t absAxis);
//Send position mode 2 command, indicate CAN id, speed, acceleration,    absolute position in pulses
    void sendPositionMode2Message(int id, uint16_t speed, uint8_t acc, int32_t pulses);
//Set current position a home position, this will reset any count
    void setZero(int id);
//Go back to zero position
    void goHome(int id);
//Stop the stepper motor, interrupt any action
    void emergencyStop(int id);
//Enable or disable motor control
    void enableMotor(int id, byte state);
//Change driver CAN id, specify target id and new id to be set
    void setCanId(int id, int newId);
//Send command to calibrate encoder
    void calibrateEncoder(int id);
//Set obstruction protection enabled or disabled. This will stop driver is there is too much physical resistance
    void enableProtection(int id, byte state);
//Restart driver
    void restartDriver(int id);
//Read current encoder value
    int readEncoderValue(int id);
//Release protection mode after trigger
    void releaseProtectionShaft(int id);
//Set working mode 
    void saveWorkMode(int id, int mode);/*mode = 0 CR_OPEN, mode = 1 CR_CLOSE, mode = 2 CR_vFOC, mode = 3 SR_OPEN, mode = 4 SR_CLOSE,   mode = 5 SR_vFOC*/
//Get current motor speed
    int getRealTimeSpeed(int id);
    

    private:

//Define CAN interface variables
    int _txPin, _rxPin, _txBuffer, _rxBuffer;
    long  _baudRate;
    CanFrame message;
    byte calculateChecksum(byte id, byte* message, int length);
    CanFrame rxFrame;


};

#endif
