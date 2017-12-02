#include "Status.h"


Status::Status(cv::Mat& img, int colNum) {
	this->img = img;
	size = cvGetSize(new IplImage(img));
	grayscale(img, gray);
	contrastStretch(gray,160);

	src = binarize(gray);
	isrc = inverse_binarize(gray);
	cvSaveImage("gray.bmp", new IplImage(gray));
	cvSaveImage("binary.bmp", new IplImage(src));

	windowSize = 0;
	col = row = colNum;
	board = nullptr;
}
Status::Status() {
	this->gray = 0;
	this->src = 0;
	this->isrc = 0;
	size = cvSize(0, 0);
	row = col = 0;
	board = nullptr;
}
Status::~Status() {
	for (int i = 0; i < row; i++) {
		delete[] board[i];
	}
	delete[] board;
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

bool Status::grayscale(Mat origin, Mat& dst){
	if (size.width < 30 || size.height < 30){
		return false;
	}
	dst = Mat::zeros(size, CV_8U);
	for (int y = 0; y < size.height; y++){
		for (int x = 0; x < size.width; x++){
			Vec3b color = origin.at<Vec3b>(y, x);
			dst.at<uchar>(y, x) = color[1] * 0.7152 + color[0] * 0.0722 + color[2] * 0.2126;
		}
	}

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
	cvSaveImage("Omok Insight.bmp", new IplImage(img));
	imshow("Omok Insight #_ #a", img);
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
		return -1;
	long sum = 0L;
	Mat diff;
	grayscale(newImg, diff);
	contrastStretch(diff, 160);
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

bool Status::RCvalidation(	Mat oldRC, 
							vector<CvPoint> cols, 
							vector<CvPoint> rows)
{
	
		if (windowSize == 0)
			return false;
		long sum = 0L;
		for (int y = 0; y < size.height; y++){
			for (int x = 0; x < size.width; x++){
				if (abs(oldRC.at<uchar>(y, x) - rowcol.at<uchar>(y, x))>0){
					sum++;
				}
			}
		}
		if (sum != 0L){
			rowcol = oldRC;
			this->colPxs = cols;
			this->rowPxs = rows;
			col = colPxs.size();
			row = rowPxs.size();
			cout << "row and col adjusted" << endl;
			std::cout << col << " columns found." << std::endl;
			std::cout << row << " rows found." << std::endl;
		}
	
	return true;
}

Mat Status::getRCImg(){
	return rowcol;
}
void Status::setRCImg(Mat RCImg){
	this->rowcol = Mat(RCImg);
}

vector<CvPoint> Status::getCols() {
	return this->colPxs;
}
vector<CvPoint> Status::getRows() {
	return this->rowPxs;
}