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
  config->monochrome = 0;//0:カラー画像入力、1:濃淡画像入力
  RaspiCamCvCapture *capture =
    (RaspiCamCvCapture *) raspiCamCvCreateCameraCapture2(0,config);
  free(config);
  
  //画像を表示するためのウインドウを定義する
  cv::namedWindow("capture", CV_WINDOW_AUTOSIZE);

  //画像を保存するための変数
  cv::Mat src_img, gray_img;
  
  //フレームレートを測るための準備。
  struct timeval start,end;
  gettimeofday(&start,NULL);
  float fnum = 0.0f;

  //位置決めに用いる4つのテンプレート画像を入力する
  cv::Mat tmp1_img = cv::imread("template1.png",0);//左上用。0:グレースケール画像入力
  cv::Mat tmp2_img = cv::imread("template2.png",0);//右上用
  cv::Mat tmp3_img = cv::imread("template3.png",0);//左下用
  cv::Mat tmp4_img = cv::imread("template4.png",0);//右下用
  if (tmp1_img.empty() || tmp2_img.empty() ||
      tmp3_img.empty() || tmp4_img.empty()) {
    printf("template file open error\n");
    return 0;
  }
  
  while (true) {
    //カメラモジュールから画像を取り込む
    src_img = raspiCamCvQueryFrame(capture);
    //カラー画像を濃淡画像に変換する
    cv::cvtColor(src_img,gray_img,CV_RGB2GRAY);

    //gray_imgを4つの領域に分ける
    cv::Mat gray1_img = gray_img(cv::Rect(  0,   0, 320, 240));
    cv::Mat gray2_img = gray_img(cv::Rect(320,   0, 320, 240));
    cv::Mat gray3_img = gray_img(cv::Rect(  0, 240, 320, 240));
    cv::Mat gray4_img = gray_img(cv::Rect(320, 240, 320, 240));

    //テンプレートマッチング結果を保存する変数
    cv::Mat result_img;
    cv::Point min_pt;
    double minVal;
    cv::Rect match_rect1(0, 0, tmp1_img.cols, tmp1_img.rows);//マッチングした位置
    cv::Rect match_rect2(0, 0, tmp2_img.cols, tmp2_img.rows);
    cv::Rect match_rect3(0, 0, tmp3_img.cols, tmp3_img.rows);
    cv::Rect match_rect4(0, 0, tmp4_img.cols, tmp4_img.rows);

    //テンプレートマッチング1、左上
    cv::matchTemplate(gray1_img, tmp1_img, result_img, CV_TM_SQDIFF);
    cv::minMaxLoc(result_img, &minVal, NULL, &min_pt, NULL);
    match_rect1.x = min_pt.x;
    match_rect1.y = min_pt.y;
    
    //テンプレートマッチング2、右上
    cv::matchTemplate(gray2_img, tmp2_img, result_img, CV_TM_SQDIFF);
    cv::minMaxLoc(result_img, &minVal, NULL, &min_pt, NULL);
    match_rect2.x = min_pt.x + 320;
    match_rect2.y = min_pt.y;

    //テンプレートマッチング3、左下
    cv::matchTemplate(gray3_img, tmp3_img, result_img, CV_TM_SQDIFF);
    cv::minMaxLoc(result_img, &minVal, NULL, &min_pt, NULL);
    match_rect3.x = min_pt.x;
    match_rect3.y = min_pt.y + 240;

    //テンプレートマッチング4、右下
    cv::matchTemplate(gray4_img, tmp4_img, result_img, CV_TM_SQDIFF);
    cv::minMaxLoc(result_img, &minVal, NULL, &min_pt, NULL);
    match_rect4.x = min_pt.x + 320;
    match_rect4.y = min_pt.y + 240;

    //マッチングした位置を入力画像に重ね書きする
    cv::rectangle(gray_img, match_rect1, cv::Scalar(255),2);
    cv::rectangle(gray_img, match_rect2, cv::Scalar(255),2);
    cv::rectangle(gray_img, match_rect3, cv::Scalar(255),2);
    cv::rectangle(gray_img, match_rect4, cv::Scalar(255),2);
    
    //その画像をウインドウに表示する。
    //但し，ディスプレイへの表示はcvWaitKey()関数を実行したときに行われる
    cv::imshow("capture", gray_img);
    
    //'q'キーが押されれば、ファイルを保存、幾何変換などを行い終了する
    if (cvWaitKey(1) == 'q') {
      //入力画像を保存する
      imwrite("src_img.png",src_img);
      imwrite("gray_img.png",gray_img);

      //検出した4ヶ所のマーカ座標を求める
      float x1 = match_rect1.x + match_rect1.width /2.0f;
      float y1 = match_rect1.y + match_rect1.height/2.0f;
      float x2 = match_rect2.x + match_rect2.width /2.0f;
      float y2 = match_rect2.y + match_rect2.height/2.0f;
      float x3 = match_rect3.x + match_rect3.width /2.0f;
      float y3 = match_rect3.y + match_rect3.height/2.0f;
      float x4 = match_rect4.x + match_rect4.width /2.0f;
      float y4 = match_rect4.y + match_rect4.height/2.0f;

      //マーカー座標をsrc、変換後の座標をdstにセットする
      const cv::Point2f src[] = {cv::Point2f(x1, y1), cv::Point2f(x2, y2),
				 cv::Point2f(x3, y3), cv::Point2f(x4, y4)};
      const cv::Point2f dst[] = {cv::Point2f(-30, 629), cv::Point2f(-30, -30),
				 cv::Point2f(629, 629), cv::Point2f(629, -30)};
      //3×3の投影変換行列を求める
      const cv::Mat matrix = cv::getPerspectiveTransform(src, dst);

      //入力画像を変換して、保存する
      cv::Mat dst_img;
      cv::warpPerspective(src_img, dst_img, matrix, cv::Size(600,600));
      imwrite("dst_img.png",dst_img);
      
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
