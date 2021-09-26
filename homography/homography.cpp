/*
*  @ author 刘笑 21S053284
* @date 2021.9.26
* @brief Homework1 for Computer Vision 
*/

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;

class ChessBoard
{
    public:
        ChessBoard(cv::Mat img, int width = 9, int height = 6, double size = 30):img(img), width(width), height(height), size(size)
        {}
        ~ChessBoard(){}
        void get_world_coordinations(void);
        void get_corners(void);
        cv::Mat get_H(void);

    private:
        int width;
        int height;
        double size;
        cv::Mat img;
        cv::Mat dst;
        cv::Mat H;
        std::vector<cv::Point2f> corners;
        std::vector<cv::Point2f> worlds;
    
};

void ChessBoard::get_world_coordinations(void){
    for (size_t i = 0; i < height; i++){
        for (size_t j = 0; j < width; j++)
        {
            worlds.push_back(cv::Point2f(j*size,i*size));
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
    cv::Mat A = cv::Mat::zeros(2*width*height,8,CV_64FC1);
    cv::Mat B = cv::Mat::zeros(2*width*height,1,CV_64FC1);

    for (int i = 0; i < width*height; i++)
    {
        A.at<double>(i,0) = corners[i].x;    //x1
        A.at<double>(i,1) = corners[i].y;    //y1
        A.at<double>(i,2) = 1;    //1
        A.at<double>(i,6) = -corners[i].x*worlds[i].x; //-x1*x2
        A.at<double>(i,7) = -corners[i].y*worlds[i].x; //-y1*x2

        A.at<double>(i+1,3) = corners[i].x;    //x1
        A.at<double>(i+1,4) = corners[i].y;    //y1
        A.at<double>(i+1,5) = 1;    //1
        A.at<double>(i+1,6) = -corners[i].x*worlds[i].y; //-x1*y2
        A.at<double>(i+1,7) = -corners[i].y*worlds[i].y; //-y1*y2

        B.at<double>(i,0) = worlds[i].x;    //x2
        B.at<double>(i+1,0) = worlds[i].y; //y2
    }
    
    H = (A.t() *A).inv()*A.t()*B;
    return H;

}

int main(){
    cv::Mat img = cv::imread("/home/liuxiao/code/CV_in_HIT/data/left13.jpg");
    if (img.empty()){
        cout << "Empty input!"<<endl;
        return 0;
    }
    cv::Mat result;
    ChessBoard chessboard(img);
    chessboard.get_world_coordinations();
    chessboard.get_corners();
    result = chessboard.get_H();

    //extract result to txt file
    ofstream outfile("/home/liuxiao/code/CV_in_HIT/homography/result/left13.txt");
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {  
            if (!(i == 2 && j == 2)){
                outfile << result.at<double>(3*i+j,0) <<" " ;
            }else{
                outfile << 1;
            }
            
        }
        outfile <<endl; 
    }
    outfile.close();
    
    return 0;
}