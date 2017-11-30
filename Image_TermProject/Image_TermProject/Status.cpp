#include "Status.h"


Status::Status(cv::Mat& img, int colNum) {
	this->img = img;
	//imshow("original image", img);
	cvtColor(img, gray, CV_RGB2GRAY);
	//imshow("grayscaled image", gray);
	size = cvGetSize(new IplImage(gray));
	//src = smoothing(src);
	contrastStretch(gray,160);

	src = binarize(gray);
	isrc = inverse_binarize(gray);
	cvSaveImage("gray.bmp", new IplImage(gray));
	cvSaveImage("binary.bmp", new IplImage(src));

	windowSize = 0;
	col = row = colNum;
	colPxs = nullptr;
	rowPxs = nullptr;
	board = nullptr;
	//highlight = nullptr;
	num_w = num_b = 0;
}
Status::Status() {
	this->src = 0;
	this->isrc = 0;
	size = cvSize(0, 0);
	row = col = 0;
	colPxs = nullptr;
	rowPxs = nullptr;
	board = nullptr;
	//highlight = nullptr;
	num_w = num_b = 0;
}
Status::~Status() {
	for (int i = 0; i < row; i++) {
		delete[] board[i];
	}
	delete[] board;
	delete[] colPxs;
	delete[] rowPxs;
	std::cout << "Destruct status" << std::endl;
}

bool Status::setStone(int xid, int yid, int color) {
	if (board == nullptr) {
		board = new char*[col];
		for (int i = 0; i < col; i++) {
			board[i] = new char[row];
		}
	}
	if (xid >= col || yid >= row) return false;
	if (board[yid][xid] != EMPTY) return false;

	board[yid][xid] = color;
	return true;
}


Mat Status::binarize(cv::Mat img) {
	Mat tmp = Mat::zeros(size,CV_8U);
	for (int y = 0; y < img.rows; y++) {
		for (int x = 0; x < img.cols; x++) {
			if (img.at<uchar>(y, x) < WB_THRESHOLD)
				tmp.at<uchar>(y, x) = 0;
			else
				tmp.at<uchar>(y, x) = 255;
		}
	}
	return tmp;
}
Mat Status::inverse_binarize(cv::Mat img) {
	Mat tmp = Mat::zeros(size, CV_8U);
	for (int y = 0; y < img.rows; y++) {
		for (int x = 0; x < img.cols; x++) {
			if (img.at<uchar>(y, x) >  UCHAR_MAX - WB_THRESHOLD)
				tmp.at<uchar>(y, x) = 0;
			else
				tmp.at<uchar>(y, x) = 255;
		}
	}
	return tmp;
}
Mat Status::smoothing(Mat& origin) {
	Mat rst = Mat::zeros(size, CV_8U);
	uchar mask[3][3] = { 1,2,1,2,4,2,1,2,1 }; int sum = 500;

	for (int y = 0; y < size.height; y++) {
		for (int x = 0; x < size.width; x++) {
			if (y == 0 || x == 0 || y == size.height - 1 || x == size.width - 1) {
				rst.at<uchar>(y, x) = origin.at<uchar>(y,x);
				continue;
			}
			//if (origin.at<uchar>(y, x) < WB_THRESHOLD) continue;
			int temp = 0;
			for (int j = 0; j < 3; j++) {
				for (int i = 0; i < 3; i++) {
					temp += origin.at<uchar>(y + j - 1, x + i - 1) * mask[i][j];
				}
			}
			temp /= sum;
			rst.at<uchar>(y, x) = temp;
		}
	}
	return rst;
}


void Status::contrastStretch(Mat& org, uchar dst) {
	int histo[256] = { 0 };
	for (int y = 0; y < size.height; y++) {
		for (int x = 0; x < size.width; x++) {
			histo[org.at<uchar>(y, x)]++;
		}
	}
	int max = 0;
	for (int i = 0; i < 255; i++) {
		if (histo[max] < histo[i])
			max = i;
	}

	uchar now = max;
	float param = (float)dst / now;
	if (param > 1)	param = (1 / param);
	org *= param;
}

/*
bool Status::InitializeBoard() {
	if (src.empty()) return false;
	uchar newcolor;
	char pmask[4][3][3] = {
		{ -1, -2, -1, 0, 0, 0, 1, 2, 1 },
		{ -1, 0, 1, -2, 0, 2, -1, 0, 1 },
		{ 0, 1, 2, -1, 0, 1, -2, -1, 0 },
		{ -2, -1, 0, -1, 0, 1, 0, 1, 2 }
	};

	Mat buffer = Mat::zeros(cvSize(width, height), CV_8U);

	for (int y = 0; y < height; y++) {		//real
		for (int x = 0; x < width; x++) {	//real
			if (y == 0 || x == 0 || y == height - 1 || x == width - 1) {
				buffer.at<uchar>(y, x) = 0;
				continue;
			}
			int res1 = 0,res2=0;
			//for (int k = 0; k < 2; k++)
				for (int i = -1; i < 2; i++) {		//mask
					for (int j = -1; j < 2; j++) {	//mask
						int tx = x + j, ty = y + i;	//3x3 mat coordinates
						res1 += abs(src.at<uchar>(ty, tx) * pmask[0][i + 1][j + 1]);
						res2 += abs(src.at<uchar>(ty, tx) * pmask[1][i + 1][j + 1]);
					}
				}
			
			if (res1>500 && res2>500 && res1+res2 < 1260) {

				buffer.at<uchar>(y, x) = (uchar)255;
			}
		}
	}
	
	for (int y = height - 1; y >= 0; y--) {
		for (int x = width - 1; x >= 0; x--) {
			if (buffer.at<uchar>(y, x) == 255) {
				
			}
		}
	}



	
	imshow("", buffer);
	return true;
}

*/

//bool Status::DifferenceCheck(){
//
//}
bool Status::Update(){
	for (int y = 0; y < row; y++){
		for (int x = 0; x < col; x++){
			CvPoint temp = getPos(x, y);
			if (highlight[y][x]>0){
				Vec3b color = img.at<Vec3b>(temp.y - windowSize / 2, temp.x - windowSize / 2);
				int t = highlight[y][x];
				if (color[2] + t > 255)
					color[2] = 255;
				else
					color[2] = t+20;
				if (color[1] - t < 0)
					color[1] = 0;
				else
					color[1] -= t;
				if (color[0] - t < 0)
					color[0] = 0;
				else
					color[0] -= t;
				for (int ty = temp.y - windowSize / 2; ty < temp.y + windowSize / 2; ty++){
					for (int tx = temp.x - windowSize / 2; tx < temp.x + windowSize / 2; tx++){
						img.at<Vec3b>(ty, tx) = color;
					}
				}
			}
				
		}
	}
	imshow("result", img);
	return true;
}
char** Status::getBoard(){
	return board;
}
CvPoint Status::getPos(int xid, int yid){
	assert(xid < col && yid < row);
	return CvPoint(colPxs[xid].x, rowPxs[yid].y);
}

int Status::getRow(){
	return row;
}
int Status::getCol(){
	return col;
}
int Status::getWS(){
	return windowSize;
}

long Status::diffCheck(Mat newImg){
	if (windowSize == 0)
		return false;
	long sum = 0L;
	Mat diff;
	cvtColor(newImg, diff, CV_RGB2GRAY);
	contrastStretch(diff, 160);
	int checkWindow = windowSize / 2;
	for (int y = 0; y < size.height; y++){
		for (int x = 0; x < size.width; x++){
			if (abs(diff.at<uchar>(y, x) - gray.at<uchar>(y, x))>0){
				diff.at<uchar>(y, x) = 255;
				sum++;
			}
			else{
				diff.at<uchar>(y, x) = 0;
			}
		}
	}
	cvSaveImage("diff.bmp", new IplImage(diff));
	return sum;
}