#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include "RaspiCamCV.h"

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {

  //カメラモジュールを利用できるようにするための初期設定
  RASPIVID_CONFIG *config = (RASPIVID_CONFIG*)malloc(sizeof(RASPIVID_CONFIG));
  config->width = 640;//水平画素数
  config->height = 480;//垂直画素数
  config->bitrate = 0;
  config->framerate = 0;
  config->monochrome = 0;//0:カラー画像、1:濃淡画像
  RaspiCamCvCapture *capture =
    (RaspiCamCvCapture *) raspiCamCvCreateCameraCapture2(0,config);
  free(config);
  
  //画像を表示するためのウインドウを定義する
  cv::namedWindow("capture", CV_WINDOW_AUTOSIZE);

  //画像を保存するための変数
  cv::Mat src_img;
  
  //フレームレートを測るための準備。
  struct timeval start,end;
  gettimeofday(&start,NULL);
  float fnum = 0.0f;//フレーム数
  
  while (true) {
    //カメラモジュールから画像を取り込む
    src_img = raspiCamCvQueryFrame(capture);
    
    //その画像をウインドウに表示する。
    //但し，ディスプレイへの表示はcvWaitKey()関数を実行したときに行われる
    cv::imshow("capture", src_img);
    
    //'q'キーが押されれば、ファイルを保存して終了する
    if (cvWaitKey(1) == 'q') {
      imwrite("src_img.jpg",src_img);
      break;
    }
    
    //フレームレート（1秒あたりの処理枚数）を計算して、表示する。
    gettimeofday(&end,NULL);
    float interval = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000000.0;
    fnum += 1.0f;
    float fps = fnum/interval;
    printf("%g fps\n",fps);
  }
  
  //終了時の処理
  cvDestroyWindow("capture");
  raspiCamCvReleaseCapture(&capture);
  return 0;
}
