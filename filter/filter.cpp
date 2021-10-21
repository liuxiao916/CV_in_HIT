/*
*  @ author 刘笑 21S053284
* @date 2021.10.21
* @brief Homework? for Computer Vision 
*/

#include <iostream>
#include <opencv2/opencv.hpp>

int main(){
    cv::Mat src = cv::imread("../data/filter/lena.png");
    if (src.empty()){
        std::cout << "empty input" << std::endl;
        return 0;
    }else{
        std::cout << "OK" << std::endl;
        return 0;
    }
}