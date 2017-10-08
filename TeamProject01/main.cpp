#include <iostream>
#include <string>
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\core\core.hpp"

using namespace std;
using namespace cv;


#define BACKGROUND 255 //background color
#define THRESHOLD 10 //line color

vector<pair<int, int>> getTBLR(Mat im) {

	vector<pair<int, int>> vertex_TBLR;
	
	bool found = false;
	//Top
	for (int y = 0; !found && y < im.rows; y++) {
		for (int x = 0; !found && x < im.cols; x++) {
			uchar pixel = im.at<uchar>(y, x);
			if (pixel != BACKGROUND && pixel < THRESHOLD) {
				vertex_TBLR.push_back(pair<int,int>(y,x)); found = true;
			}
		}
	}
	found = false;
	
	//Bottom
	for (int y = im.rows - 1; !found && y >= 0; y--) {
		for (int x = im.cols - 1; !found && x >= 0; x--) {
			uchar pixel = im.at<uchar>(y, x);
			if (pixel != BACKGROUND && pixel < THRESHOLD) {
				vertex_TBLR.push_back(pair<int, int>(y, x)); found = true;
			}
		}
	}
	found = false;

	//Left
	for (int x = 0; !found && x < im.cols; x++) {
		for (int y = im.rows - 1; !found && y >= 0; y--) {
			uchar pixel = im.at<uchar>(y, x);
			if (pixel != BACKGROUND && pixel < THRESHOLD) {
				vertex_TBLR.push_back(pair<int, int>(y, x)); found = true;
			}
		}
	}
	found = false;

	//Right
	for (int x = im.cols - 1; !found && x >= 0; x--) {
		for (int y = 0; !found && y < im.rows; y++) {
			uchar pixel = im.at<uchar>(y, x);
			if (pixel != BACKGROUND && pixel < THRESHOLD) {
				vertex_TBLR.push_back(pair<int, int>(y, x)); found = true;
			}
		}
	}
	return vertex_TBLR;
}
bool isLine(Mat im, vector<pair<int, int>> tblr) {

	int mid_x = (tblr.at(0).second + tblr.at(2).second) / 2;
	int mid_y = (tblr.at(0).first + tblr.at(2).first) / 2;
	
	uchar pixel = im.at<uchar>(mid_y, mid_x);
	
	if (pixel != BACKGROUND && pixel < THRESHOLD)
		return true;
	else
		return false;
}
bool isOval(vector<pair<int, int>> tblr) {
	
	int TB = tblr.at(1).first - tblr.at(0).first;
	int LR = tblr.at(3).second - tblr.at(2).second;
	
	if (TB == LR)
		return false;
	else
		return true;
}

int main() {

	string filename[10];
	int NOF = 0;

	cout << "Enter Image : " << endl;
	for (int i = 0; i < 10; i++) {
		getline(cin, filename[i], '\n');
		if (!filename[i].compare(""))
			break;
		NOF++;
	}
	cout << "Result : " << endl;



	////////////processing///////////////

	

	for (int i = 0; i < NOF; i++) {

		// 이미지 불러오기
		Mat image = imread(filename[i], IMREAD_GRAYSCALE);

		vector<pair<int, int>> TBLR = getTBLR(image);

		assert(TBLR.size() == 4);

		//check coordinates
		/*
		for (int i = 0; i < 4; i++) {
			cout << TBLR.at(i).second << ", " << TBLR.at(i).first << endl;
		}
		*/

		//line or curve?
		if (isLine(image, TBLR)) {
			cout << "Square!" << endl;
		}
		else {
			if(isOval(TBLR))
				cout << "Oval!" << endl;
			else
				cout << "Circle!" << endl;
		}

	}



	////////////processing///////////////

	cout << endl;

	return 0;
}