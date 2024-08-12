#include "MKS57_CAN.h"

MKS57_CAN::MKS57_CAN(int txPin, int rxPin, long baudRate, int txBuffer, int rxBuffer)
    : _txPin(txPin), _rxPin(rxPin), _baudRate(baudRate), _txBuffer(txBuffer), _rxBuffer(rxBuffer) {}

    bool MKS57_CAN::begin() {
      ESP32Can.setPins(_txPin, _rxPin);
      ESP32Can.setRxQueueSize(_rxBuffer);
      ESP32Can.setTxQueueSize(_txBuffer);
      ESP32Can.setSpeed(ESP32Can.convertSpeed(_baudRate));

      return ESP32Can.begin(ESP32Can.convertSpeed(_baudRate), _txPin, _rxPin, _rxBuffer, _txBuffer);
    }

    byte  MKS57_CAN::calculateChecksum(byte id, byte* message, int length){

      byte  crc = id;

      for (int  i = 0;  i < length  - 1;  i++){
        crc +=  message[i];
      }

      return  crc & 0xFF;
    }

    void  MKS57_CAN::sendPositionMode2Message(int id, uint16_t speed, uint8_t acc, int32_t pulses){

      message.identifier  = id;
      message.extd  = 0;
      message.data_length_code  = 8;
      message.data[0] = 0xFE;
      message.data[1] = (speed >> 8) & 0xFF;
      message.data[2] = speed & 0xFF;
      message.data[3] = acc;
      message.data[4] = (pulses >> 16) & 0xFF;
      message.data[5] = (pulses >> 8) & 0xFF;
      message.data[6] = pulses & 0xFF;
      message.data[7] = calculateChecksum(id, message.data, 8);
      ESP32Can.writeFrame(&message);
      }

      void  MKS57_CAN::sendPositionMode4Message(int id, uint16_t speed, uint8_t acc, int32_t absAxis){

      message.identifier  = id;
      message.extd  = 0;
      message.data_length_code  = 8;
      message.data[0] = 0xF5;
      message.data[1] = (speed >> 8) & 0xFF;
      message.data[2] = speed & 0xFF;
      message.data[3] = acc;
      message.data[4] = (absAxis >> 16) & 0xFF;
      message.data[5] = (absAxis >> 8) & 0xFF;
      message.data[6] = absAxis & 0xFF;
      message.data[7] = calculateChecksum(id, message.data, 8);
      ESP32Can.writeFrame(&message);
      }

      void  MKS57_CAN::setZero(int id){

        message.identifier  = id;
        message.extd  = 0;
        message.data_length_code  = 2;
        message.data[0] = 0x92;
        message.data[1] = calculateChecksum(id, message.data, 2);
        ESP32Can.writeFrame(&message);

      }

      void  MKS57_CAN::goHome(int id){

        message.identifier  = id;
        message.extd  = 0;
        message.data_length_code  = 2;
        message.data[0] = 0x91;
        message.data[1] = calculateChecksum(id, message.data, 2);
        ESP32Can.writeFrame(&message);

      }

      void MKS57_CAN::emergencyStop(int id){

        message.identifier  = id;
        message.extd  = 0;
        message.data_length_code  = 2;
        message.data[0] = 0xF7;
        message.data[1] = calculateChecksum(id, message.data, 2);
        ESP32Can.writeFrame(&message);

      }

      void MKS57_CAN::enableMotor(int id, byte state){

        message.identifier  = id;
        message.extd  = 0;
        message.data_length_code  = 3;
        message.data[0] = 0xF3;
        message.data[1] = state;
        message.data[3] = calculateChecksum(id, message.data, 3);
        ESP32Can.writeFrame(&message);

      }

      void  MKS57_CAN::setCanId(int id, int newId){

        message.identifier  = id;
        message.extd = 0;
        message.data_length_code  = 4;
        message.data[0] = 0x8B;
        message.data[1]  = (newId >>  8) & 0xFF;
        message.data[2] = newId & 0xFF;
        message.data[3] = calculateChecksum(id, message.data, 4);
        ESP32Can.writeFrame(&message);

      }

      void  MKS57_CAN::calibrateEncoder(int id){

        message.identifier  = id;
        message.extd  = 0;
        message.data_length_code  = 3;
        message.data[0] = 0x80;
        message.data[1] = 0x00;
        message.data[2] = calculateChecksum(id, message.data, 3);
        ESP32Can.writeFrame(&message);

      }

      void MKS57_CAN::enableProtection(int id, byte state){
        
        message.identifier  = id;
        message.extd  = 0;
        message.data_length_code  = 3;
        message.data[0] = 0x88;
        message.data[1] = state;
        message.data[2] = calculateChecksum(id, message.data, 3 );
        ESP32Can.writeFrame(&message);

      }

      void MKS57_CAN::restartDriver(int id){
        
        message.identifier  = id;
        message.extd  = 0;
        message.data_length_code  = 2;
        message.data[0] = 0x41;
        message.data[1] = calculateChecksum(id, message.data, 2);
        ESP32Can.writeFrame(&message);

      }



















