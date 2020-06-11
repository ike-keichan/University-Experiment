#include <stdio.h>
#include <math.h>
#include <wiringPiI2C.h>
#include <time.h>
#include <sys/time.h>

//センサからの生データを読み取る関数
float raw_data(int fd, int adr) {
	int high = wiringPiI2CReadReg8(fd, adr);
	int low  = wiringPiI2CReadReg8(fd, adr+1);
	int val = (high<<8) + low;
	if (val >= 0x8000) val = -((65535 - val) +1);
	return ((float)val);
}

//センサのオフセットを計算する関数
float compute_offset(int fd, int adr) {
	int i;
	float offset = 0.0f;

	for (i = 0; i < 1000; i++) {
		offset += raw_data(fd,adr);
	}
	offset /= 1000.0f;
	return (offset);
}

int main() {
	const int mpu6050 = 0x68;		//センサー自身のアドレス
	const int power_mgmt = 0x6b;		//MPU6050を起動するためのアドレス
	const int ay_adr = 0x3D;		//Y軸加速度データのアドレス
	const int gx_adr = 0x43;		//X軸まわり角速度のアドレス

        float beforeRad = 0.0;
        float rad = 0.0;
        float angle = 0;
        float beforeSec = 0.0;

	//I2Cインタフェースを初期化する 
	int fd = wiringPiI2CSetup(mpu6050);
	if (fd == -1) return -1;

	//MPU-6050を起動する
	if (wiringPiI2CWriteReg8(fd, power_mgmt, 0) == -1) return -1;

	//Y軸加速度とX軸角速度のオフセットを求める
	float ay_offset = compute_offset(fd,ay_adr);
	float gx_offset = compute_offset(fd,gx_adr);

	//時間を測るための準備。interval = start - endで時間を測る
	float interval,sec;
	struct timeval start,end;
	gettimeofday(&start,NULL);

	for (int i = 0; i < 10000; i++) {
		//加速度を重力加速度を単位として読み取る
		float ay = (raw_data(fd,ay_adr) - ay_offset )/16384.0f;

		//角速度をラジアン/sec単位で読み取る
		float gx = (raw_data(fd,gx_adr) - gx_offset )/131.0f/180.0f*M_PI;

		//whileループ1回の時間をintervalに求める
		gettimeofday(&end,NULL);
		interval = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;
		start = end;
                beforeSec = sec;
		sec += interval;

                beforeRad = rad;
                rad = beforeRad + (gx * (beforeSec - sec));  
                angle = rad / M_PI * 180; 

		printf("%d. sec: %+3.1f, ay: %+5.4f, gx: %+5.4f, angle: %2.2f\n",i,sec,ay,gx,angle);
	}

	return 0;
}
