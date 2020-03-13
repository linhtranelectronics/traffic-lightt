/*
 Name:    traffic_lights.ino
 Created: 3/5/2020 10:42:08 AM
 Author:  linh
*/

#include"trafficLight_library.h"
trafficLight land1;
trafficLight land2;
#define red1 16
#define yellow1 14
#define green1 15
#define red2 19
#define yellow2 17
#define green2 18
#define led1 5
#define led2 4  
#define led3 3
#define led4 2
uint16_t process_time_ms = 0;
bool stateLand = 0;
uint32_t nowMili, lastMiliScan, lastMilicount;
uint8_t numLed7seg;
const int Seg[11] = {
  0b11000000,//0 
  0b11111001,//1 
  0b10100100,//2
  0b10110000,//3
  0b10011001,//4
  0b10010010,//5
  0b10000010,//6
  0b11111000,//7
  0b10000000,//8
  0b10010000,//9
  0b11111111,
};
void scanCathode(uint8_t byte);
void scanAnode(uint8_t numLed);
void scan7seg(uint16_t ms);

void count_time() {
  process_time_ms++;
  if (process_time_ms == 3000) {
    process_time_ms = 0;
    stateLand = !stateLand;
  }
}
// the setup function runs once when you press reset or power the board
void setup() {
  land1.begin(red1, green1, yellow1);
  land2.begin(red2, green2, yellow2);
  for (uint8_t i =2; i < 18; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  Serial.begin(115200);
  
}
uint8_t i;
// the loop function runs over and over again until power down or reset
void loop() {
  land1.update(process_time_ms, stateLand);
  land2.update(process_time_ms, !stateLand);
  scan7seg(2);
  nowMili = millis();
  if ((uint32_t) (nowMili - lastMilicount) >= 10) {
    count_time();
    lastMilicount = nowMili;
  }

}
void scanCathode(uint8_t byte) {
  for (uint8_t i = 6; i < 13; i++) {
    digitalWrite(i, !bitRead(byte, i - 6));
    
  }
}
void scanAnode(uint8_t numLed) {
  switch (numLed) {
  case 1:
    digitalWrite(led4, HIGH);
    digitalWrite(led1, LOW);
    break;
  case 2:
    
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    break;
  case 3:
    
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    break;
  case 4: 
    
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    break;
  default:
    break;
  }
}
void scan7seg(uint16_t ms)  {
  bool scan = false;
  nowMili = millis();
  if ((uint32_t)(nowMili - lastMiliScan) >= ms) {
    lastMiliScan = nowMili;
    scan = true;
    numLed7seg++;
    if (numLed7seg == 4) {
      numLed7seg = 0;
    }
  }
  if (scan) {
    switch (numLed7seg) {
    case 0:
      scanCathode(Seg[land1.time_left() / 10]);
      
      scanAnode(1);
      break;
    case 1:
      scanCathode(Seg[land1.time_left() % 10]);
      
      scanAnode(2);
      break;
    case 2:
      scanCathode(Seg[land2.time_left() / 10]);
      scanAnode(3);
      break;
    case 3:
      scanCathode(Seg[land2.time_left() % 10]);
      scanAnode(4);
      break;
      default:
      break;
    }
  }
}
