#include <MKS57_CAN.h>


#define TXPIN 4  //CAN chip tx pin
#define RXPIN 5  //CAN chip rx pin
#define SPEED 1000  //Communication speed bit rate
#define BUFFER  10  //Message buffer


MKS57_CAN driver1(TXPIN,  RXPIN,  SPEED,  BUFFER, BUFFER);  //Declare object name, set tx/rx pins, bit rate, tx/rx buffer size



void setup() {

  driver1.begin();  //Initialize driver interface

}

void loop() {
 driver1.enableMotor(0x1,0x1);  //Enable motor (id,  enable/diable)
 driver1.sendPositionMode2Message(0x1, 200, 2, 0x2000);  //Absolute pulse mode command  (node id, speed,  acceleration,  number of pulses)
 delay(2000);
 driver1.sendPositionMode2Message(0x1, 200, 2, -0x2000);
 delay(2000);
 driver1.enableMotor(0x1, 0x0);
 delay(3000);
}
