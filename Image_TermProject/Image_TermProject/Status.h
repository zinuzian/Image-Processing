#pragma once

#include "opencv2\core.hpp"

#define EMPTY 0
#define BLACK 1
#define WHITE 2

#define LINE_THICKNESS 10


class Status{
	cv::Mat src;
	uchar* data;
	int width, height;
	int windowSize;

	char** board;
	int row, col;
	int num_w, num_b;


public:
	Status(cv::Mat& src);
	Status();
	~Status();

	bool InitializeBoard();
	bool DifferenceCheck();
	bool UpdateBoard();
	char** getBoard();
	char* getPos(int x, int y);

private:
	int countLines();
	bool setStone(int x, int y, int color);
	cv::Mat binarize(cv::Mat src);

};