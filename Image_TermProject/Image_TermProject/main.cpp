#include <iostream>
#include "Status.h"



using namespace std;
using namespace cv;

int main(){
	Mat img = imread("omokSample.bmp");
	if (img.empty())
		return -1;
	Status stat(img, 20);
	waitKey();
	cout << "hi";
}