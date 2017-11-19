#include <iostream>
#include "Status.h"



using namespace std;
using namespace cv;

int main(){
	Mat img = imread("sample01.bmp");
	if (img.empty())
		return -1;
	Status stat(img, 20);
	stat.InitializeBoard();
	waitKey();
	//cout << "hi";
}