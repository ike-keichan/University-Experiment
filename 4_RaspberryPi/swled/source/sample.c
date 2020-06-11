#include <stdio.h>
#include <wiringPi.h>

#define GPIO21 21
#define GPIO26 26

int main() {
  //wiringPiの初期化
  if (wiringPiSetupGpio() == -1) {
    printf("error: wiringPiSetupGpio()\n");
    return 1;
  }
  
  //GPIO21を出力に、GPIO26を入力に設定する
  pinMode(GPIO21, OUTPUT);
  pinMode(GPIO26, INPUT);
  
  //GPIO21に1を出力し、GPIO26の信号を読み取り表示する。
  digitalWrite(GPIO21, 0);
  int sw = digitalRead(GPIO26);
  printf("GPIO26: %d\n", sw);
}
