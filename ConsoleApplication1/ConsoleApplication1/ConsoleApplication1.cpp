#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <core.hpp>
#include <opencv2/imgproc.hpp>
#include <imgcodecs.hpp>
#include <highgui.hpp>
#include "C:\bitmap\bitmap_image.hpp"


using namespace cv;
using namespace std;

int main()
{
	


	/*
	//threshold 함수 이용
	Mat input_img = imread("unnamed.jpg", IMREAD_GRAYSCALE);
	Mat output_img;

	
	//input_img.convertTo(input_img,cv);
	int h, w;
	cout << input_img.at<Vec3b>(0, 0) << endl;
	input_img.at<Vec3b>(0, 0)[0]; //B
	input_img.at<Vec3b>(0, 0)[1]; //G
	input_img.at<Vec3b>(0, 0)[2]; //R
	h = input_img.size().height;
	w = input_img.size().width;

	

	threshold(input_img,output_img,  3, 255, THRESH_OTSU);

	imshow("before", input_img);

	imshow("after", output_img);

	while (waitKey(0) < 0);
	*/
	
	
	
	//구현
	Mat input_img = imread("unnamed.jpg", IMREAD_COLOR);
	int h, w;
	h = input_img.rows;
	w = input_img.cols;

	Mat output_img=Mat::zeros(h,w,CV_8U);

	int hist_value[256];

	output_img.at<uchar>(55, 24) = 255;
	cout << output_img.at<uchar>(55, 24) << endl;
	cout<<input_img.at<Vec3b>(0, 0)<<endl; //B

	cout << h << w;

	for (int i = 0; i < 256; i++) {
		hist_value[i] = 0;
	}

	//histogram 만들기
	int pixel;
	for (int r = 0; r < h; r++) {
		for (int c = 0; c < w; c++) {
			pixel = round((int(input_img.at<Vec3b>(r, c)[0]) + int(input_img.at<Vec3b>(r, c)[1]) + int(input_img.at<Vec3b>(r, c)[2])) / 3);
			hist_value[pixel] += 1;
		}
	}

	//
	int t = 0;
	double min = 100000000000;
	double max = -1000000000000000;
	int th = 0;
	while (t <= 256) {
		double wb = 0, mb = 0, vb = 0, wf = 0, mf = 0, vf = 0, sumb = 0, sumf = 0, bv = 0, hg=0;
		for (int b = 0; b < t; b++) {
			sumb += hist_value[b];
			mb += b * hist_value[b];
		}
		for (int f = t; f < 256; f++) {
			sumf+= hist_value[f];
			mf += f * hist_value[f];
		}
		mb = mb / sumb;
		wb = sumb / (h*w);
		mf = mf / sumf;
		wf = sumf / (h*w);

		for (int v = 0; v < 256; v++) {
			vb=hist_value[v] * (v - mb) *(v-mb);
		}
		for (int v = 0; v < 256; v++) {
			vb = hist_value[v] * (v - mb) *(v - mb);
		}
		vb = vb / sumb;
		vf = vf / sumf;

		//OTSU method
		bv= (wb*mb*mb + wf * mf*mf);
		// Valley Emphasis Method임
	/*	hg = hist_value[t] / (sumb + sumf);
		wv = (1-hg)*(wb*mb*mb + wf * mf*mf);*/

		if (max <= bv) {
			max = bv;
			th = t;
		}
	t++;
	}

	for (int c = 0; c < w; c++) {
	for (int r = 0; r < h;r++) {
		pixel = round((int(input_img.at<Vec3b>(r, c)[0]) + int(input_img.at<Vec3b>(r, c)[1]) + int(input_img.at<Vec3b>(r, c)[2])) / 3);
		if (th > pixel) {
			output_img.at<uchar>(r,c)=0;

		}
		else {
			output_img.at<uchar>(r, c) = 255;
				55;

		}
		
	}
}


	imshow("before", input_img);
	imshow("after", output_img);

	while (waitKey(0) < 0);
	
	return 0;
}
