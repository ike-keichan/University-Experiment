#include <stdio.h>
#include <wiringPi.h>

#define GPIO21 21

int main() {
  //wiringPiの初期化
  if (wiringPiSetupGpio() == -1) {
    printf("error: wiringPiSetupGpio()\n");
    return 1;
  }
  
  //GPIO21を出力に設定する
  pinMode(GPIO21, OUTPUT);
  
  //周期的にLEDを点滅する
  int onTime  = 1000000;// 1000000で1.0sec、100000で0.1sec
  int offTime = 100000;
  while (1) {
    //LEDを点燈する
    digitalWrite(GPIO21, 1);
    delayMicroseconds(onTime);
    
    //LEDを消す
    digitalWrite(GPIO21, 0);
    delayMicroseconds(offTime);
  }
}
