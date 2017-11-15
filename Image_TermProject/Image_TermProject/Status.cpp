#include "Status.h"


Status::Status(cv::Mat& src){
	this->src = src;
	windowSize = 0;
	width = src.cols;
	height = src.rows;

	col = row = countLines();
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

int Status::countLines(){
	int count = 0;
	int val;
	int y = 10;
	for (int x = 0; x < width; x++){
		if ((val = src.at<uchar>(x, y)) < 5){
			for (int i = 0; i < LINE_THICKNESS; i++){
				x++;
				if ((val = src.at<uchar>(x, y)) >= 5){
					i
				}
			}
		}
	}

}
bool Status::setStone(int x, int y,int color){
	if (board == nullptr){
		board = new char*[col];
		for (int i = 0; i < col; i++){
			board[i] = new char[row];
		}
	}
	if (x >= row || y >= col) return false;
	if (board[y][x] != EMPTY) return false;

	board[y][x] = color;
	return true;
}
cv::Mat binarize(cv::Mat src){

}

bool Status::InitializeBoard(){

}
bool Status::DifferenceCheck(){

}
bool Status::UpdateBoard(){

}
char** Status::getBoard(){

}
char* Status::getPos(int x, int y){

}

