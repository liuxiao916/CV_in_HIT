/*
*  @ author 刘笑 21S053284
* @date 2021.10.11
* @brief Homework2 for Computer Vision 
*/

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;

class ChessBoard
{
    public:
        ChessBoard(std::vector<cv::String> images, int width = 9, int height = 6, double size = 30):images(images), width(width), height(height), size(size)
        {}
        ~ChessBoard(){}
        void get_world_coordinations(void);
        void get_corners(void);
        void calibration(void);

    private:
        int width;
        int height;
        int rows;
        int cols;
        double size;
        cv::Mat img, gray;
        std::vector<cv::String> images;
        std::vector<cv::Point2f> corners;
        std::vector<cv::Point3f> worlds;
        std::vector<std::vector<cv::Point2f> > imgpoints;
        std::vector<std::vector<cv::Point3f> > worldpoints;
        cv::Mat cameraMatrix, distCoeffs, R, T;
};

void ChessBoard::get_world_coordinations(void){
    for (size_t i = 0; i < height; i++){
        for (size_t j = 0; j < width; j++)
        {
            worlds.push_back(cv::Point3f(j*size,i*size,0));
        }  
    }
}

void ChessBoard::get_corners(void){
    cv::TermCriteria criteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.001);
    for (int i=0; i<images.size();i++){
        img = cv::imread(images[i]);
        rows = img.rows;
        cols = img.cols;
        if (img.empty()){
        cout << "Empty input!"<<endl;
        }
        bool success = cv::findChessboardCorners(img,cv::Size(width,height),corners);
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
        if (success){
            cv::cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1), criteria);
            imgpoints.push_back(corners);
            worldpoints.push_back(worlds);
        }

    }
    
    //cv::drawChessboardCorners(dst,cv::Size(width,height),corners,flag);
    //cv::imwrite("dst.jpg",dst);
}

void ChessBoard::calibration(void){
    cv::calibrateCamera(worldpoints, imgpoints, cv::Size(rows, cols), cameraMatrix, distCoeffs, R, T);
    // 内参矩阵
	std::cout << "cameraMatrix : " << cameraMatrix << std::endl;
	// 透镜畸变系数
	std::cout << "distCoeffs : " << distCoeffs << std::endl;
	// rvecs
	std::cout << "Rotation vector : " << R << std::endl;
	// tvecs
	std::cout << "Translation vector : " << T << std::endl;

}


int main(){
    std::vector<cv::String> images;
    std::string path = "../data/calibration/Images/*.jpg";
    cv::glob(path, images);
    ChessBoard chessboard(images);
    chessboard.get_world_coordinations();
    chessboard.get_corners();
    chessboard.calibration();

    //extract result to txt file
    // ofstream outfile("/home/liuxiao/code/CV_in_HIT/homography/result/left13.txt");
    // for (size_t i = 0; i < 3; i++)
    // {
    //     for (size_t j = 0; j < 3; j++)
    //     {  
    //         if (!(i == 2 && j == 2)){
    //             outfile << result.at<double>(3*i+j,0) <<" " ;
    //         }else{
    //             outfile << 1;
    //         }
            
    //     }
    //     outfile <<endl; 
    // }
    // outfile.close();
    
    return 0;
}