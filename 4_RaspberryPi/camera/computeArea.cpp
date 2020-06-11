#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  //面積を測定用の画像ファイル名
  const char* file_name = "dst_img.png";

  //画像を保存するための変数
  cv::Mat src_img,gray_img,binary_img;
  
  //画像ファイルを読み込む
  src_img = cv::imread(file_name,1);//1はカラー画像として入力する。
  if (src_img.empty()) {
    printf("%s open error\n", file_name);
    return 0;
  }
  
  //カラー画像を濃淡画像に変換する
  cv::cvtColor(src_img,gray_img,CV_RGB2GRAY);

  //濃淡画像を二値化する
  cv::threshold(gray_img, binary_img,0,255,cv::THRESH_OTSU);
  
  //濃淡画像と二値画像をウインドウに表示する。
  //実際の表示はcvWaitKey()関数を実行したときに行われる
  cv::imshow("input image", gray_img);
  cv::imshow("binary image",binary_img);
  cvWaitKey(500);//cvWaitKey()の引数が小さいと、表示されない場合がある。
  
  while (true) {
    
    //濃淡画像を二値化するためのしきい値を入力する
    int thresh;
    char buf[256];
    do {
      printf("二値化のしきい値(1から255の数値, 0で終了):");
      scanf("%s", buf);
      thresh = atoi(buf);//bufが数値ではない文字列であれば0
      if (thresh == 0) {//0でプログラムを終了する
	return 0;
      }
      
    } while ((thresh < 0) || (thresh > 255));

    //濃淡画像を二値化する
    cv::threshold(gray_img, binary_img,thresh,255,cv::THRESH_BINARY);
    
    //濃淡画像と二値画像をウインドウに表示する。
    //実際の表示はcvWaitKey()関数を実行したときに行われる
    cv::imshow("input image", gray_img);
    cv::imshow("binary image",binary_img);
    cv::imwrite("binary_img.png", binary_img);
    cvWaitKey(500);//cvWaitKey()の引数が小さいと、表示されない場合がある。

    //面積を計算する。1画素が0.25mm四方、入力画像の画素数が600×600画素。
    double area;
    area = 0.25*0.25* (600*600 - cv::countNonZero(binary_img));
    printf("面積: %g mm2\n", area);
  }
  
  //終了時の処理
  cvDestroyWindow("input image");
  cvDestroyWindow("binary image");
  
  return 0;
}
