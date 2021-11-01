/*
* @author 刘笑 21S053284
* @date 2021.11.1
* @brief Homework? for Computer Vision 
*/

#include <iostream>
#include <opencv2/opencv.hpp>
#define window_name "dst"

using namespace std;

int Cr_upper_limit = 255;
int Cr_lower_limit = 0;
int Cb_upper_limit = 255;
int Cb_lower_limit = 0;
cv::Mat dst;
cv::Mat Y,Cr,Cb;

void on_trackbar(int, void *){
    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            int index = i * dst.cols + j;
            //像素值
            int Cr_data = (int)Cr.data[index];
            int Cb_data = (int)Cb.data[index];
            if((Cr_data>Cr_lower_limit)&&(Cr_data<Cr_upper_limit)&&(Cb_data>Cb_lower_limit)&&(Cb_data<Cb_upper_limit)){
                dst.data[index] = 255;
            }else{
                dst.data[index] = 0;
            }
        }
    }
    cv::imshow(window_name,dst);
}

int main(){
    cv::Mat src = cv::imread("../data/skin/picture3.png");
    cv::Mat YCrCb;

    vector<cv::Mat> channels;
    if (src.empty()){
        std::cout << "empty input" << std::endl;
        return 0;
    }
    cv::cvtColor(src, YCrCb, CV_BGR2YCrCb);
    cv::split(YCrCb,channels);
    Y = channels.at(0); 
    Cr = channels.at(1);
    Cb = channels.at(2);
    dst= cv::Mat::zeros(cv::Size(Y.cols,Y.rows),CV_8UC1);
    cv::namedWindow(window_name);
    cv::imshow(window_name,dst);

    string trackbar_name1 = "Cr_upper_limit";
    string trackbar_name2 = "Cr_lower_limit";
    string trackbar_name3 = "Cb_upper_limit";
    string trackbar_name4 = "Cb_lower_limit";

    cv::createTrackbar(trackbar_name1,window_name,&Cr_upper_limit,255,on_trackbar);
    cv::createTrackbar(trackbar_name2,window_name,&Cr_lower_limit,255,on_trackbar);
    cv::createTrackbar(trackbar_name3,window_name,&Cb_upper_limit,255,on_trackbar);
    cv::createTrackbar(trackbar_name4,window_name,&Cb_lower_limit,255,on_trackbar);

    cv::waitKey();
    return 0;
}