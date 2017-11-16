#include "Status.h"


Status::Status(cv::Mat& img, int colNum){
	this->img = img;
	imshow("original image", img);
	cvtColor(img, src, CV_RGB2GRAY);

	/*imshow("grayscaled image", src);
	Mat tmp = src;
	src = binarize(src);
	imshow("binarized image", src);
	tmp = inverse_binarize(tmp);
	imshow("inverse binarized image", tmp);*/

	windowSize = 0;
	width = src.cols;
	height = src.rows;

	col = row = colNum;
	board = new char*[col];
	for (int i = 0; i < col; i++){
		board[i] = new char[row];
	}
	num_w = num_b = 0;
}
Status::Status(){
	this->src = 0;
	row = col = 0;
	board = nullptr;
	num_w = num_b = 0;
}
Status::~Status(){
	for (int i = 0; i < col; i++){
		delete[] board[i];
	}
	delete[] board;
}

bool Status::setStone(int xid, int yid,int color){
	if (board == nullptr){
		board = new char*[col];
		for (int i = 0; i < col; i++){
			board[i] = new char[row];
		}
	}
	if (xid >= row || yid >= col) return false;
	if (board[yid][xid] != EMPTY) return false;

	board[yid][xid] = color;
	return true;
}


Mat Status::binarize(cv::Mat src){
	Mat tmp(src);
	for (int y = 0; y < src.rows; y++){
		for (int x = 0; x < src.cols; x++){
			if (src.at<uchar>(y, x) < WB_THRESHOLD)
				tmp.at<uchar>(y, x) = 0;
			else
				tmp.at<uchar>(y, x) = 255;
		}
	}
	return tmp;
}
Mat Status::inverse_binarize(cv::Mat src){
	Mat tmp(src);
	for (int y = 0; y < src.rows; y++){
		for (int x = 0; x < src.cols; x++){
			if (src.at<uchar>(y, x) > UCHAR_MAX - WB_THRESHOLD)
				tmp.at<uchar>(y, x) = 0;
			else
				tmp.at<uchar>(y, x) = 255;
		}
	}
	return tmp;
}
bool Status::InitializeBoard(){

}
/*
bool Status::DifferenceCheck(){

}
bool Status::Update(){

}
char** Status::getBoard(){

}
char* Status::getPos(int xid, int yid){

}*/

