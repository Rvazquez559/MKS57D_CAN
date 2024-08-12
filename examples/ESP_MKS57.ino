#include <MKS57_CAN.h>


#define TXPIN 4
#define RXPIN 5
#define SPEED 1000
#define BUFFER  10


MKS57_CAN driver1(TXPIN,  RXPIN,  SPEED,  BUFFER, BUFFER);



void setup() {

  driver1.begin();

}

void loop() {
 driver1.enableMotor(0x1,0x1);
 driver1.sendPositionMode2Message(0x1, 200, 2, 0x2000);
 delay(2000);
 driver1.sendPositionMode2Message(0x1, 200, 2, -0x2000);
 delay(2000);
 driver1.enableMotor(0x1, 0x0);
 delay(3000);
}
