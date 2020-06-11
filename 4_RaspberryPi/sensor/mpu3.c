#include <stdio.h>
#include <math.h>
#include <wiringPiI2C.h>
#define LOOPCOUNT 10000
#define BINNUMBER 100 

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
        int binX[BINNUMBER]; 
        int binY[BINNUMBER]; 
        int num;

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

        float aNumX = averageX - 4 * sdX;
        float bNumX = averageX + 4 * sdX;
        float aNumY = averageY - 4 * sdY;
        float bNumY = averageY + 4 * sdY;

        for (int k = 0; k < LOOPCOUNT; k++) {
                num = ((dataX[k] - aNumX) / (bNumX - aNumX)) * BINNUMBER;
                binX[num] += 1;
                num = ((dataY[k] - aNumY) / (bNumY - aNumY)) * BINNUMBER;
                binY[num] += 1; 
        }

        for (int l = 0; l < BINNUMBER; l++) {
                printf("%d, %d, %d\n",l+1 ,binX[l] ,binY[l]);
        } 

	return 0;
}
