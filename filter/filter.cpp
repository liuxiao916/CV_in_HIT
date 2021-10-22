/*
* @author 刘笑 21S053284
* @date 2021.10.21
* @brief Homework? for Computer Vision 
*/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <vector>
#include <numeric>

/*
* @function MeanFilter
* @Input 
*  src : Input image
*  dst : output image
*  nTempH : height of kernel
*  nTempW : weight of kernel
*  nTempMY : coordinate of kernel center
*  nTempMY : coordinate of kernel center
*/
void MeanFilter(const cv::Mat src, cv::Mat& dst, int nTempH, int nTempW, int nTempMY, int nTempMX)
{
	if (src.empty())
	{
		return ;
	}
	src.copyTo(dst);
	int i, j;
	for (i = nTempMY; i < dst.rows - (nTempH - nTempMY) + 1; i++)
	{
		for (j = nTempMX; j <dst.cols - (nTempW - nTempMX) + 1; j++)
		{
            std::vector<int> kernel;
			for (int k = 0; k < nTempH; k++)
			{
				for (int l = 0; l < nTempW; l++)
				{   
                    int pix = src.at<uchar>(i + k - nTempMY, j + l - nTempMX);   
                    kernel.push_back(pix);              
				}
			}
            int sum = std::accumulate(kernel.begin(),kernel.end(),0.0);
            int fResult = sum / (nTempH*nTempW);
			dst.at<uchar>(i, j) = (int)fResult;
		}
	}
}


/*
* @function MedianFilter
* @Input 
*  src : Input image
*  dst : output image
*  nTempH : height of kernel
*  nTempW : weight of kernel
*  nTempMY : coordinate of kernel center
*  nTempMY : coordinate of kernel center
*/
void MedianFilter(const cv::Mat src, cv::Mat& dst, int nTempH, int nTempW, int nTempMY, int nTempMX)
{
	if (src.empty())
	{
		return ;
	}
	src.copyTo(dst);
	int i, j;
	for (i = nTempMY; i < dst.rows - (nTempH - nTempMY) + 1; i++)
	{
		for (j = nTempMX; j <dst.cols - (nTempW - nTempMX) + 1; j++)
		{
			int fResult = 0;
            std::vector<int> kernel;
			for (int k = 0; k < nTempH; k++)
			{
				for (int l = 0; l < nTempW; l++)
				{   
                    int pix = src.at<uchar>(i + k - nTempMY, j + l - nTempMX);
                    kernel.push_back(pix);                
				}
			}
            std::sort(kernel.begin(), kernel.end());
			dst.at<uchar>(i, j) = kernel[kernel.size()/2];
		}
	}
}

/*
* @function get1DGaussianArray
* @Input 
*  arr_size : kernel size
*  sigma : sigma parameter of Gaussian function
*/
void get1DGaussianArray(int arr_size, double sigma, double *array){
    int i;
    int center_i = arr_size / 2;
    double pi = 3.141592653589793;
    double sum = 0.0f;
    for (i = 0; i < arr_size; i++ ) {
        array[i]=  sqrt(0.5f *pi*(sigma*sigma)) *exp( -(1.0f)* ( ((i-center_i)*(i-center_i)) / (2.0f*sigma*sigma) ));
        sum += array[i];
    }
    for (i = 0; i < arr_size; i++) {      
        array[i] /= sum;
    }
}

/*
* @function GaussianFilter
* @Input 
*  src : Input image
*  dst : output image
*  nTempH : height of kernel
*  nTempW : weight of kernel
*  nTempMY : coordinate of kernel center
*  nTempMY : coordinate of kernel center
*  kernel: 1D Gaaussian kernel
*/
void GaussianFilter(const cv::Mat src, cv::Mat& dst, int nTempH, int nTempW, int nTempMY, int nTempMX, double *kernel)
{
	if (src.empty())
	{
		return ;
	}
	src.copyTo(dst);
	int i, j;
    double fResult;
	for (i = nTempMY; i < dst.rows - (nTempH - nTempMY) + 1; i++)
	{
		for (j = nTempMX; j <dst.cols - (nTempW - nTempMX) + 1; j++)
		{
            fResult = 0;
			for (int k = 0; k < nTempH; k++)
			{
				for (int l = 0; l < nTempW; l++)
				{   
                    int pix = src.at<uchar>(i + k - nTempMY, j + l - nTempMX);   
                    fResult = fResult + pix*kernel[k*nTempW + l];
				}
			}
			dst.at<uchar>(i, j) = (int)fResult;
		}
	}
}

int main(){
    cv::Mat src = cv::imread("../data/filter/noiseimg.bmp");
    cv::Mat dst;
    if (src.empty()){
        std::cout << "empty input" << std::endl;
        return 0;
    }
    cv::cvtColor(src, src, CV_BGR2GRAY);
    
    //MeanFilter                  
    MeanFilter(src,dst,3,3,1,1);
    cv::imwrite("../data/filter/dst/Mean33_mine.jpg",dst);
    cv::blur(src,dst,cv::Size(3,3));
    cv::imwrite("../data/filter/dst/Mean33_opencv.jpg",dst);
    MeanFilter(src,dst,5,5,3,3);
    cv::imwrite("../data/filter/dst/Mean55_mine.jpg",dst);
    cv::blur(src,dst,cv::Size(5,5));
    cv::imwrite("../data/filter/dst/Mean55_opencv.jpg",dst);
    //MedianFilter
    MedianFilter(src,dst,3,3,1,1);
    cv::imwrite("../data/filter/dst/Median33_mine.jpg",dst);
    cv::medianBlur(src,dst,3);
    cv::imwrite("../data/filter/dst/Median33_opencv.jpg",dst);
    MedianFilter(src,dst,5,5,3,3);
    cv::imwrite("../data/filter/dst/Median55_mine.jpg",dst);
    cv::medianBlur(src,dst,5);
    cv::imwrite("../data/filter/dst/Median55_opencv.jpg",dst);
    //GaussianFilter
    double Gau_1D_Kernel3[3]; 
    get1DGaussianArray(3,3,Gau_1D_Kernel3);
    GaussianFilter(src,dst,3,1,1,0,Gau_1D_Kernel3);
    GaussianFilter(dst,dst,1,3,0,1,Gau_1D_Kernel3);   //Separable Gaussian filter
    cv::imwrite("../data/filter/dst/Separable_Gausian33_mine.jpg",dst);
    double Gau_1D_Kernel5[5]; 
    get1DGaussianArray(5,3,Gau_1D_Kernel5);
    GaussianFilter(src,dst,5,1,3,0,Gau_1D_Kernel5);
    GaussianFilter(dst,dst,1,5,0,3,Gau_1D_Kernel5);   //Separable Gaussian filter
    cv::imwrite("../data/filter/dst/Separable_Gausian55_mine.jpg",dst);
    cv::GaussianBlur(src,dst,cv::Size(3,3),3,3);
    cv::imwrite("../data/filter/dst/Gausian33_opencv.jpg",dst);
    cv::GaussianBlur(src,dst,cv::Size(5,5),3,3);
    cv::imwrite("../data/filter/dst/Gausian55_opencv.jpg",dst);
    //Test the result of GaussianBlur
    cv::Mat edge = dst -src;
    cv::imwrite("../data/filter/dst/test.jpg",edge);
}