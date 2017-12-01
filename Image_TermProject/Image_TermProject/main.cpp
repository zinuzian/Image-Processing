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

bool makeStatusByImage(menu& m, Status*& s){
	m.capture();
	Mat img = imread("board.bmp");
	if (img.empty())
		return -1;

	system("cls");
	s = new Status(img, 20);

	if (s->InitializeBoard() == false) {
		if (s->getBoard() != nullptr)
		{
			delete s; s = nullptr;
		}
		cout << "Board init failed" << endl;
		//menu.setcapture();
		return false;
	}
}






int main() {

	menu menu;
	Status* stat = nullptr;
	bool initsuccess = false;
	bool RCcheck = false;
	Mat skeleton;
	vector<CvPoint> cols, rows;


	if (!makeStatusByImage(menu, stat))
		return -1;
	searchToHighlight(menu,stat);



	long twocircle = 2 * (stat->getWS() / 2 + 1)*(stat->getWS() / 2 + 1)*3.141592;
	while (!(GetAsyncKeyState(53) & 0x8000)) {

		menu.capture();
		Mat img = imread("board.bmp");
		if (img.empty())
			return -1;


		long diff = stat->diffCheck(img);
		if (diff == 0L){
			//waitKey(1);
			Sleep(500);
			continue;
		}
		else if (diff > twocircle){
			if (stat->getBoard() != nullptr) {
				delete stat; stat = nullptr;
			}
			cout << "Retry capture" << endl;
			//Sleep(1000);

			//recapture
			menu.setcapture();


			if (!makeStatusByImage(menu, stat))
				return -1;
			searchToHighlight(menu, stat);
			continue;
		}
		else{
			Status* newStat = nullptr;
			if (!makeStatusByImage(menu, newStat))
				return -1;
			stat->RCvalidation(newStat->getRCImg());
			searchToHighlight(menu, stat);
			waitKey(1);
			Sleep(500);
		}

	}
}


