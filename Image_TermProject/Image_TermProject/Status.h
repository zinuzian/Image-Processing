#pragma once

#include "opencv2\opencv.hpp"
using namespace cv;
using namespace std;

#define EMPTY 0
#define BLACK 1
#define WHITE -1

#define LINE_THICKNESS 10
#define WB_THRESHOLD 140

class Status{
	cv::Mat img;		//original image
	cv::Mat gray;		//grayscaled image
	cv::Mat src;		//binarized image
	cv::Mat isrc;		//inverse binarized image
	cv::Mat rowcol;
	CvSize size;
	vector<CvPoint> colPxs,rowPxs;
	int windowSize;

	char** board;
	
	int row, col;
	int num_w, num_b;


public:
	Status(Mat& img, int colNum);
	Status();
	~Status();
	std::vector<std::vector<unsigned char>> highlight;
	bool InitializeBoard();
	bool BoardCheck();
	bool Update();
	char** getBoard();
	CvPoint getPos(int xid, int yid);
	void printBoard();
	int getRow();
	int getCol();
	int getWS();
	long diffCheck(Mat newImg);
	bool RCvalidation(Mat newRC);
	Mat getRCImg();
	void setRCImg(Mat RCImg);

private:
	bool setStone(int xid, int yid, int color);
	bool grayscale(Mat origin, Mat& dst);
	void contrastStretch(Mat& org, uchar dst);
	Mat smoothing(Mat& origin);
	Mat binarize(Mat img);
	Mat inverse_binarize(cv::Mat img);
};