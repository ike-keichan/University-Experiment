#include <stdio.h>
#include <math.h>
#include <wiringPiI2C.h>
#define LOOPCOUNT 10000 

//センサからの生データを読み取る関数
float raw_data(int fd, int adr) {
	int high = wiringPiI2CReadReg8(fd, adr);
	int low  = wiringPiI2CReadReg8(fd, adr+1);
	int val = (high<<8) + low;
	if (val >= 0x8000) val = -((65535 - val) +1);
	return ((float)val);
}

int main() {
	const int mpu6050 = 0x68;		//センサー自身のアドレス
	const int power_mgmt = 0x6b;	//MPU6050を起動するためのアドレス
	const int ay_adr = 0x3D;		//Y軸加速度データのアドレス
	const int gx_adr = 0x43;		//X軸角速度データのアドレス

        float dataX[LOOPCOUNT];
        float dataY[LOOPCOUNT];        
        float sumX = 0, sumY = 0;
        float averageX = 0, averageY = 0;
        float dispersionX = 0, dispersionY = 0;
        float sdX = 0, sdY = 0;
        int count1 = 0, count2 = 0, count3 = 0, count4 = 0; 

	//I2Cインタフェースを初期化する 
	int fd = wiringPiI2CSetup(mpu6050);
	if (fd == -1) return -1;

	//MPU-6050を起動する
	if (wiringPiI2CWriteReg8(fd, power_mgmt, 0) == -1) return -1;

	for (int i = 0; i < LOOPCOUNT; i++) {
		//加速度を重力加速度を単位として読み取る
		float ay = raw_data(fd,ay_adr)/16384.0f;

		//角速度をラジアン/sec単位で読み取る
		float gx = raw_data(fd,gx_adr)/131.0f/180.0f*M_PI;

		printf("%d. ay:%+5.4f, gx:%+5.4f\n",i ,ay,gx);
                sumX += gx;
                sumY += ay;
                dataX[i] = gx;
                dataY[i] = ay;  

	}

        averageX = sumX / LOOPCOUNT;
        averageY = sumY / LOOPCOUNT;

        for (int j = 0; j < LOOPCOUNT; j++) {
                dispersionX += (dataX[j] - averageX) * (dataX[j] - averageX);
                dispersionY += (dataY[j] - averageY) * (dataY[j] - averageY); 
        }

        dispersionX = dispersionX / LOOPCOUNT;
        dispersionY = dispersionY / LOOPCOUNT; 
        sdX = sqrtf(dispersionX);
        sdY = sqrtf(dispersionY); 

        for (int k = 0; k < LOOPCOUNT; k++) {
                if((dataX[k] <= (averageX + sdX))&&(dataX[k] >= (averageX - sdX))){
                  count1++;
                }
                if((dataY[k] <= (averageY + sdY))&&(dataY[k] >= (averageY - sdY))){
                  count2++;
                }
                if((dataX[k] <= (averageX + 3*sdX))&&(dataX[k] >= (averageX - 3*sdX))){
                  count3++;
                }
                if((dataY[k] <= (averageY + 3*sdY))&&(dataY[k] >= (averageY - 3*sdY))){
                  count4++;
                }
        }    

        printf("sumX:%+5.4f, sumY:%+5.4f\n",sumX ,sumY);
        printf("aveX:%+5.6f. aveY:%+5.6f\n",averageX ,averageY); 
        printf("disX:%+5.8f, disY:%+5.8f\n",dispersionX ,dispersionY);
        printf("sdX :%+5.6f, sdY :%+5.6f\n",sdX ,sdY); 
        printf("x+3o:%d, x+o:%d\n",count3 ,count1);
        printf("y+3o:%d, y+o:%d\n",count4 ,count2);   

	return 0;
}
