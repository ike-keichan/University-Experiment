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
  
  //GPIO21を出力に設定する
  pinMode(GPIO21, OUTPUT);
  pinMode(GPIO26, INPUT);
 
  //周期的にLEDを点滅する
  int onTime  = 0;// 1000000で1.0sec、100000で0.1sec
  int offTime = 0;
  
  int check = 0;
  int flag = 0; 
  int beforeCheck = 0; 

  while(1){
   
   check = digitalRead(GPIO26);
   if(beforeCheck == 0&&check == 1){
       
 flag++;
   }

  if(flag == 4){
    flag = 0;
  } 

  if(flag == 0){
    onTime  = 0;
    offTime = 10000;
  }else if(flag == 1){
    onTime  = 3333;
    offTime = 6667;
  }else if(flag == 2){
    onTime  = 6667;
    offTime = 3333;
  }else{
    onTime  = 10000;
    offTime = 0;
  }
 
   //LEDを点燈する
   digitalWrite(GPIO21, 1);
   delayMicroseconds(onTime);
    
   //LEDを消す
   digitalWrite(GPIO21, 0);
   delayMicroseconds(offTime);

   beforeCheck = check;
 }
}
