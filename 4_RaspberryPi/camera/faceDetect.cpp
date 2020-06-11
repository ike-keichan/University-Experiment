#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <objdetect/objdetect.hpp>
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
  cv::Mat src_img,gray_img;

  //実際に顔検出を行う画像の縮小率
  double scale = 4.0;

  //分類器の読み込み
  std::string cascadeName = "haarcascades/haarcascade_frontalface_alt.xml";
  cv::CascadeClassifier cascade;
  if (!cascade.load(cascadeName)) {
    printf("CascadeClassifier read error.\n");
    return 0;
  }
  std::vector<cv::Rect> faces;//検出した顔の位置を保存するベクター
  
  //フレームレートを測るための準備。
  struct timeval start,end;
  gettimeofday(&start,NULL);
  float fnum = 0.0f;
  
  while (true) {
    //カメラモジュールから画像を取り込む
    src_img = raspiCamCvQueryFrame(capture);
    cv::cvtColor(src_img, gray_img, CV_RGB2GRAY);

    //所持時間を短縮するために画像を縮小し、ヒストグラム平坦化する
    cv::resize(gray_img,gray_img,cv::Size(640/scale,480/scale),0,0,cv::INTER_LINEAR);
    cv::equalizeHist(gray_img,gray_img);

    //マルチスケール顔探索
    cascade.detectMultiScale(gray_img, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE, cv::Size(30,30));

    //結果の描画
    std::vector<cv::Rect>::const_iterator r=faces.begin();
    for (; r!=faces.end(); r++) {
      cv::Point center;
      int radius;
      center.x = cv::saturate_cast<int>((r->x + r->width*0.5)*scale);
      center.y = cv::saturate_cast<int>((r->y + r->height*0.5)*scale);
      radius = cv::saturate_cast<int>((r->width + r->height)*0.25*scale);
      cv::circle(src_img, center, radius, cv::Scalar(80,80,255),3,8,0);
    }
    
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
