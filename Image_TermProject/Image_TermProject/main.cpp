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
	while (1) {
			
		menu.capture();
		Mat img = imread("board.bmp");
		if (img.empty())
			return -1;
		stat = new Status(img, 20);
		if ((stat->InitializeBoard()) == false) {
			if(stat->getBoard() != nullptr) delete stat;
			cout << "wrong capture" << endl;
			menu.setcapture();
			continue;
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

		/*for (int y = 0; y < stat.getRow(); y++) {
			for (int x = 0; x < stat.getCol(); x++) {
				stat.highlight[x][y] = tHB[x][y];
			}
		}*/

		stat->highlight = algorithm.getHB();

		for (int y = 0; y < stat->getRow(); y++) {
			for (int x = 0; x < stat->getCol(); x++) {
				std::cout << (int)algorithm.GetHighlight(y, x) << " ";
			}
			std::cout << std::endl;
		}
		stat->Update();





		waitKey(1);
		Sleep(2000);
		delete stat;
	}
}

/*mat img = imread("board.bmp");
if (img.empty())
	return -1;
status stat(img, 20);
stat.initializeboard();

char** tmp = stat.getboard();

algor algorithm(tmp, stat.getrow(), stat.getcol(),1);
for (int y = 0; y < stat.getrow(); y++){
	for (int x = 0; x < stat.getcol(); x++){
		if (tmp[x][y] != empty){
			algorithm.search(x, y);
		}
	}
}

vector<vector<unsigned char>> thb = algorithm.gethb();

for (int y = 0; y < stat.getrow(); y++){
	for (int x = 0; x < stat.getcol(); x++){
		stat.highlight[x][y] = thb[x][y];
	}
}
for (int y = 0; y < stat.getrow(); y++){
	for (int x = 0; x < stat.getcol(); x++){
		std::cout <<(int) algorithm.gethighlight(y, x) << " ";
	}
	std::cout << std::endl;
}
stat.update();





waitkey();*/
//cout << "hi";



