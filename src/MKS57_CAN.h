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

    MKS57_CAN(int txPin, int rxPin, long baudRate, int txBuffer, int rxBuffer);
    bool begin();
    void sendPositionMode4Message(int id, uint16_t speed, uint8_t acc, int32_t absAxis);
    void sendPositionMode2Message(int id, uint16_t speed, uint8_t acc, int32_t pulses);
    void setZero(int id);
    void goHome(int id);
    void emergencyStop(int id);
    void enableMotor(int id, byte state);
    void setCanId(int id, int newId);
    void calibrateEncoder(int id);
    void enableProtection(int id, byte state);
    void restartDriver(int id);

    int readEncoderValue(int id);
    void releaseProtectionShaft(int id);
    void saveWorkMode(int id, int mode);/*mode = 0 CR_OPEN, mode = 1 CR_CLOSE, mode = 2 CR_vFOC, mode = 3 SR_OPEN, mode = 4 SR_CLOSE,   mode = 5 SR_vFOC*/
    int getRealTimeSpeed(int id);
    

    private:

    int _txPin, _rxPin, _txBuffer, _rxBuffer;
    long  _baudRate;
    CanFrame message;
    byte calculateChecksum(byte id, byte* message, int length);
    CanFrame rxFrame;


};

#endif
