#include <iostream>
#include "Status.h"
#include "algorithm.h"


using namespace std;
using namespace cv;

int main(){
	Mat img = imread("sample02.bmp");
	if (img.empty())
		return -1;
	Status stat(img, 20);
	stat.InitializeBoard();
	

	char **tmp = stat.getBoard();
	char b[15][15];
	for (int i = 0; i < 15; i++){
		for (int j = 0; j < 15; j++){
			b[i][j] = tmp[i][j];
		}
	}
	

	Algor algorithm(b);
	for (int y = 0; y < stat.getRow(); y++){
		for (int x = 0; x < stat.getCol(); x++){
			if (b[x][y] != EMPTY){
				algorithm.search(x, y);
			}
		}
	}
	
	vector<vector<unsigned char>> tHB = algorithm.getHB();

	for (int y = 0; y < stat.getRow(); y++){
		for (int x = 0; x < stat.getCol(); x++){
			stat.highlight[y][x] = tHB[x][y];
		}
	}
	for (int y = 0; y < stat.getRow(); y++){
		for (int x = 0; x < stat.getCol(); x++){
			std::cout <<(int) algorithm.GetHighlight(x, y) << " ";
		}
		std::cout << std::endl;
	}
	stat.Update();
	

	waitKey();
	//cout << "hi";
}