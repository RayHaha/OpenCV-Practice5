// Opencvtest.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include<fstream>
#include<string.h>
#include <time.h>

using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Mat image = imread("lena.bmp");
	Mat grayimage;
	Mat dimage;
	Mat eimage;
	Mat oimage;
	Mat cimage;
	cvtColor(image,grayimage, CV_BGR2GRAY);
	cvtColor(image,dimage, CV_BGR2GRAY);
	cvtColor(image,eimage, CV_BGR2GRAY);
	cvtColor(image,oimage, CV_BGR2GRAY);
	cvtColor(image,cimage, CV_BGR2GRAY);

	int pixel = 0;
	imshow("origin",grayimage);

	//dilation
	for(int i=2; i<grayimage.rows-2; i++){
		for(int j=2; j<grayimage.cols-2; j++){
			int largest = 0;
			//find largest
			for(int k=0; k<5; k++){
				for(int l=0; l<5; l++){
					if((k==0&&l==0)||(k==0&&l==4)||(k==4&&l==0)||(k==4&&l==4)){

					}else{
						pixel = grayimage.at<uchar>(i-2+k,j-2+l);
						if(pixel>largest){
							largest = pixel;
						}
					}
				}
			}
			dimage.at<uchar>(i,j) = largest;
		}
	}
	imshow("dilation",dimage);
	imwrite("dilation.bmp",dimage);
	//erosion
	for(int i=2; i<grayimage.rows-2; i++){
		for(int j=2; j<grayimage.cols-2; j++){
			int smallest = 255;
			//find largest
			for(int k=0; k<5; k++){
				for(int l=0; l<5; l++){
					if((k==0&&l==0)||(k==0&&l==4)||(k==4&&l==0)||(k==4&&l==4)){

					}else{
						pixel = grayimage.at<uchar>(i-2+k,j-2+l);
						if(pixel<smallest){
							smallest = pixel;
						}
					}
				}
			}
			eimage.at<uchar>(i,j) = smallest;
		}
	}
	imshow("erosion",eimage);
	imwrite("erosion.bmp",eimage);

	//opening
	for(int i=0; i<eimage.rows; i++){
		for(int j=0; j<eimage.cols; j++){
			pixel = eimage.at<uchar>(i,j);
			oimage.at<uchar>(i,j) = pixel;
		}
	}
	//already erosion, start dilation
	for(int i=2; i<eimage.rows-2; i++){
		for(int j=2; j<eimage.cols-2; j++){
			int largest = 0;
			//find largest
			for(int k=0; k<5; k++){
				for(int l=0; l<5; l++){
					if((k==0&&l==0)||(k==0&&l==4)||(k==4&&l==0)||(k==4&&l==4)){

					}else{
						pixel = eimage.at<uchar>(i-2+k,j-2+l);
						if(pixel>largest){
							largest = pixel;
						}
					}
				}
			}
			oimage.at<uchar>(i,j) = largest;
		}
	}
	imshow("opening",oimage);
	imwrite("opening.bmp",oimage);

	//closing
	for(int i=0; i<dimage.rows; i++){
		for(int j=0; j<dimage.cols; j++){
			pixel = dimage.at<uchar>(i,j);
			cimage.at<uchar>(i,j) = pixel;
		}
	}
	//already dilation, start erosion
	for(int i=2; i<dimage.rows-2; i++){
		for(int j=2; j<dimage.cols-2; j++){
			int smallest = 255;
			//find largest
			for(int k=0; k<5; k++){
				for(int l=0; l<5; l++){
					if((k==0&&l==0)||(k==0&&l==4)||(k==4&&l==0)||(k==4&&l==4)){

					}else{
						pixel = dimage.at<uchar>(i-2+k,j-2+l);
						if(pixel<smallest){
							smallest = pixel;
						}
					}
				}
			}
			cimage.at<uchar>(i,j) = smallest;
		}
	}
	imshow("closing",cimage);
	imwrite("closing.bmp",cimage);

	waitKey(0);
	return 0;
}