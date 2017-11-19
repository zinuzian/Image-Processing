#pragma once

#include "opencv2\opencv.hpp"
using namespace cv;

#define EMPTY 0
#define BLACK 1
#define WHITE 2

#define LINE_THICKNESS 10
#define WB_THRESHOLD 120

class Status{
	cv::Mat img;		//original image
	cv::Mat gray;		//grayscaled image
	cv::Mat src;		//grayscaled image
	CvSize size;
	CvPoint *colPxs,*rowPxs;
	int windowSize;

	char** board;
	int row, col;
	int num_w, num_b;


public:
	Status(Mat& img, int colNum);
	Status();
	~Status();

	bool InitializeBoard();
	bool DifferenceCheck();
	bool Update();
	char** getBoard();
	CvPoint getPos(int xid, int yid);

private:
	bool setStone(int xid, int yid, int color);
	void contrastStretch(Mat& org, uchar dst);
	Mat smoothing(Mat& origin);
	Mat binarize(Mat img);
	Mat inverse_binarize(cv::Mat img);
};