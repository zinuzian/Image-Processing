#pragma once

#include "opencv2\opencv.hpp"
using namespace cv;

#define EMPTY 0
#define BLACK 1
#define WHITE 2

#define LINE_THICKNESS 10
#define WB_THRESHOLD 30

class Status{
	cv::Mat img;		//original picture
	cv::Mat src;
	int width, height;
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
	char* getPos(int xid, int yid);

private:
	bool setStone(int xid, int yid, int color);
	Mat binarize(Mat img);
	Mat inverse_binarize(cv::Mat src);
};