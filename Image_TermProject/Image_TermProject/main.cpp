#include <iostream>
#include<Windows.h>
#include"menu.h"
#include "Status.h"
#include "algorithm.h"

using namespace std;
using namespace cv;

int main() {

	menu menu;
	Status* stat=nullptr;
	int prev_row=0, prev_col=0;
	bool initsuccess = false;
	while (1) {
		
		menu.capture();
		Mat img = imread("board.bmp");
		if (img.empty())
			return -1;
		if (stat != nullptr){
			long twocircle = 2 * (stat->getWS() / 2+1)*(stat->getWS() / 2+1)*3.141592;
			long diff = stat->diffCheck(img);
			if (diff == 0L){
				waitKey(1);
				Sleep(1000);
				continue;
			}
			else if (diff > twocircle){
				if (stat->getBoard() != nullptr) {
					delete stat; stat = nullptr;
				}
				cout << "wrong capture" << endl;
				//Sleep(1000);
				menu.setcapture();
				continue;
			}
			delete stat;
		}
		system("cls");
		stat = new Status(img, 20);
		initsuccess = stat->InitializeBoard();
	
		
		if (initsuccess == false) {
			if (stat->getBoard() != nullptr)
			{
				delete stat; stat = nullptr;
			}
			cout << "wrong capture" << endl;
			//menu.setcapture();
			continue;
		}
		
		if (prev_row == 0 && prev_col == 0){
			prev_row = stat->getRow();
			prev_col = stat->getCol();
		}
		
		
		stat->BoardCheck();
		char** tmp = stat->getBoard();

		Algor algorithm(tmp, stat->getRow(), stat->getCol(), menu.getplayer());
		for (int y = 0; y < stat->getRow(); y++) {
			for (int x = 0; x < stat->getCol(); x++) {
				if (tmp[x][y] != EMPTY) {
					algorithm.search(x, y);
				}
			}
		}

		stat->highlight = algorithm.getHB();

		for (int y = 0; y < stat->getRow(); y++) {
			for (int x = 0; x < stat->getCol(); x++) {
				std::cout << (int)algorithm.GetHighlight(y, x) << " ";
			}
			std::cout << std::endl;
		}
		stat->Update();
		waitKey(1);
		Sleep(1000);
		continue;
		
	}
}