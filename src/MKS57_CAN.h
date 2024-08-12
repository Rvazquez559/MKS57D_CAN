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

    private:

    int _txPin, _rxPin, _txBuffer, _rxBuffer;
    long  _baudRate;
    CanFrame message;
    byte calculateChecksum(byte id, byte* message, int length);


};

#endif