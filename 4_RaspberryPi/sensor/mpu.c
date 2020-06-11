#include <stdio.h>
#include <math.h>
#include <wiringPiI2C.h>

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

	//I2Cインタフェースを初期化する 
	int fd = wiringPiI2CSetup(mpu6050);
	if (fd == -1) return -1;

	//MPU-6050を起動する
	if (wiringPiI2CWriteReg8(fd, power_mgmt, 0) == -1) return -1;

	while (1) {
		//加速度を重力加速度を単位として読み取る
		float ay = raw_data(fd,ay_adr)/16384.0f;

		//角速度をラジアン/sec単位で読み取る
		float gx = raw_data(fd,gx_adr)/131.0f/180.0f*M_PI;

		printf("ay:%+5.4f, gx:%+5.4f\n",ay,gx);
	}

	return 0;
}
