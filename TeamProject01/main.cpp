#include <iostream>
#include <string>
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\core\core.hpp"
#include <bitset>
//
//#pragma comment(lib,"opencv_highgui310d.lib")
//#pragma comment(lib,"opencv_core310d.lib")

using namespace std;
using namespace cv;



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
		Mat image = imread(filename[0], IMREAD_GRAYSCALE);
		for (int y = 0; y < image.rows; y++) {
			for (int x = 0; x < image.cols; x++) {
				uchar val = image.at<uchar>(y, x);
				cout <<(val)<<hex;
			}
			cout << endl;
		}
		

		



	}


	









	////////////processing///////////////





	cout << endl;

	return 0;
}