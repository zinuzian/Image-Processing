#include <iostream>
#include<Windows.h>
#include"menu.h"
#include "Status.h"
#include "algorithm.h"

using namespace std;
using namespace cv;

void searchToHighlight(menu& m, Status*& s){
	s->BoardCheck();
	char** tmp = s->getBoard();

	Algor algorithm(tmp, s->getRow(), s->getCol(), m.getplayer());
	for (int y = 0; y < s->getRow(); y++) {
		for (int x = 0; x < s->getCol(); x++) {
			if (tmp[x][y] != EMPTY) {
				algorithm.search(x, y);
			}
		}
	}

	s->highlight = algorithm.getHB();

	for (int y = 0; y < s->getRow(); y++) {
		for (int x = 0; x < s->getCol(); x++) {
			std::cout << (int)algorithm.GetHighlight(y, x) << " ";
		}
		std::cout << std::endl;
	}
	s->Update();
}

bool makeStatusByImage(Mat& image, menu& m, Status*& s){
	
	if (image.empty())
		return false;

	system("cls");
	s = new Status(image, 20);

	if (s->InitializeBoard() == false) {
		if (s->getBoard() != nullptr)
		{
			delete s; s = nullptr;
		}
		cout << "Board init failed" << endl;
		return false;
	}
	return true;
}






int main() {

	Mat intro = imread("insight.bmp");
	imshow("Omok Insight #_ #a",intro);
	waitKey(0x1);


	menu menu;
	Status* stat = nullptr;
	bool initsuccess = false;
	bool RCcheck = false;
	Mat img;
	vector<CvPoint> cols, rows;

	menu.capture();
	img = imread("board.bmp");
	if (!makeStatusByImage(img,menu, stat))
		return -1;
	searchToHighlight(menu,stat);
	waitKey(1);
	Sleep(100);


	long twocircle = 2 * (stat->getWS() / 2 + 1)*(stat->getWS() / 2 + 1)*3.141592;
	while (!(GetAsyncKeyState(0x53) & 0x8001)) {	//press S to quit

		menu.capture();
		img = imread("board.bmp");
		if (img.empty())
			return -1;


		long diff = stat->diffCheck(img);
		if (diff == 0L){
			waitKey(1);
			Sleep(10);
		}
		else if (diff > twocircle){
			if (stat->getBoard() != nullptr) {
				delete stat; stat = nullptr;
			}
			cout << "Retry capture" << endl;

			//recapture
			menu.setcapture();

			menu.capture();
			img = imread("board.bmp");
			if (img.empty())
				return -1;
			if (!makeStatusByImage(img,menu, stat))
				return -1;
			searchToHighlight(menu, stat);
			waitKey(1);
			Sleep(10);
		}
		else{
			Status* newStat = nullptr;
			if (!makeStatusByImage(img, menu, newStat))
				return -1;
			newStat->RCvalidation(stat->getRCImg(),stat->getCols(),stat->getRows());
			delete stat;
			stat = newStat;
			searchToHighlight(menu, stat);
			waitKey(1);
			Sleep(10);
		}

	}
}


