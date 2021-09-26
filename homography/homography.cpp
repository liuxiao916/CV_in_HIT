/*
*  @ author 刘笑 21S053284
* @date 2021.9.26
* @brief Homework1 for Computer Vision 
*/

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class ChessBoard
{
    public:
        ChessBoard(cv::Mat img, int width = 9, int height = 6, double size = 0.03):img(img), width(width), height(height), size(0.03)
        {}
        ~ChessBoard(){}
        void get_world_coordinations(vector<cv::Point2f>& worlds);
        void get_corners(void);
        cv::Mat get_H(void);

    private:
        int width;
        int height;
        double size;
        cv::Mat img;
        cv::Mat dst;
        std::vector<cv::Point2f> corners;
        std::vector<cv::Point2f> worlds;
    
};

void ChessBoard::get_world_coordinations(vector<cv::Point2f>& worlds){
    for (size_t i = 0; i < width; i++){
        for (size_t j = 0; j < height; j++)
        {
            worlds.push_back(cv::Point2f(i*size,j*size));
        }  
    }
}

void ChessBoard::get_corners(void){
    bool flag = cv::findChessboardCorners(img,cv::Size(width,height),corners);
    dst =img.clone();
    cv::drawChessboardCorners(dst,cv::Size(width,height),corners,flag);
    cv::imwrite("dst.jpg",dst);
}

cv::Mat ChessBoard::get_H(void){
    
}

int main(){
    cv::Mat img = cv::imread("data/left7.jpg");
    if (img.empty()){
        cout << "Empty input!";
        return 0;
    }
    ChessBoard chessboard(img);
    chessboard.get_corners();
    return 0;
}