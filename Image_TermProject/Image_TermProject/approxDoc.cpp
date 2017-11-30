#include "Status.h"




bool Status::InitializeBoard() {
	try{
		if (src.empty()) return false;
		Mat test = Mat::zeros(size, CV_8U);
		std::vector<CvPoint> list;
		bool done = false;
		for (int y = 0; y < size.height - 6; y++) {
			int colCnt = 0;
			int prev = 0, now = 0;
			for (int x = 0; x < size.width - 6; x++) {
				int tx = x + 3, ty = y + 3;
				CvPoint tmp(tx, ty);
				int p = 0;
				if (test.at<uchar>(ty, tx - 1) == 255) continue;
				if (test.at<uchar>(ty, tx - 2) == 255) continue;
				if (test.at<uchar>(ty, tx - 3) == 255) continue;
				/*if (test.at<uchar>(ty - 1, tx) == 255) continue;
				if (test.at<uchar>(ty - 2, tx) == 255) continue;
				if (test.at<uchar>(ty - 3, tx) == 255) continue;*/

				if (src.at<uchar>(ty, tx) == 0) {
					for (int i = 1; i < 4; i++) {
						if (src.at<uchar>(ty + i, tx) == 0) p++;
						if (src.at<uchar>(ty - i, tx) == 255) p++;
						if (src.at<uchar>(ty, tx + i) == 0) p++;
						if (src.at<uchar>(ty, tx - i) == 0) p++;
					}
				}
				if (p >= 11) {
					test.at<uchar>(ty, tx) = 255; colCnt++;
					prev = now; now = tx;
					list.push_back(tmp);
				}
			}
			if (colCnt < 5 || colCnt > 20) {
				for (int i = 0; i < list.size(); i++) {
					test.at<uchar>(list.at(i)) = 0;
				}
				list.clear();
				continue;
			}
			else {
				col = colCnt + 2;
				windowSize = now - prev;
				colPxs = new CvPoint[col];
				rowPxs = new CvPoint[row];
				CvPoint start = CvPoint(list.at(0)); start.x -= windowSize;
				CvPoint end = CvPoint(list.back()); end.x += windowSize;
				test.at<uchar>(start) = 255; test.at<uchar>(end) = 255;
				colPxs[0] = start;
				for (int i = 0; i < colCnt; i++) {
					colPxs[i + 1] = list.at(i);
				}
				colPxs[col - 1] = end;

				std::cout << col << " columns found." << std::endl;
				/*for (int i = 0; i < col; i++) {
					std::cout << i+1 <<". "<< colPxs[i].x<< " " << colPxs[i].y<<std::endl;
					}*/
				list.clear();
				done = true;
				break;
			}
			if (done) {
				done = false;
				break;
			}
		}
		for (int x = 0; x < size.width - 6; x++) {
			int rowCnt = 0;
			int prev = 0, now = 0;
			for (int y = 0; y < size.height - 6; y++) {
				int tx = x + 3, ty = y + 3;
				CvPoint tmp(tx, ty);
				int p = 0;
				/*if (test.at<uchar>(ty, tx - 1) == 255) continue;
				if (test.at<uchar>(ty, tx - 2) == 255) continue;
				if (test.at<uchar>(ty, tx - 3) == 255) continue;*/
				if (test.at<uchar>(ty - 1, tx) == 255) continue;
				if (test.at<uchar>(ty - 2, tx) == 255) continue;
				if (test.at<uchar>(ty - 3, tx) == 255) continue;

				if (src.at<uchar>(ty, tx) == 0) {
					for (int i = 1; i < 4; i++) {
						if (src.at<uchar>(ty + i, tx) == 0) p++;
						if (src.at<uchar>(ty - i, tx) == 0) p++;
						if (src.at<uchar>(ty, tx + i) == 0) p++;
						if (src.at<uchar>(ty, tx - i) == 255) p++;
					}
				}
				if (p >= 11) {
					test.at<uchar>(ty, tx) = 255; rowCnt++;
					prev = now; now = ty;
					list.push_back(tmp);
				}
			}
			if (list.empty())
				continue;
			if (list.at(0).x != colPxs[0].x) {
				for (int i = 0; i < list.size(); i++) {
					test.at<uchar>(list.at(i)) = 0;
				}
				list.clear();
				continue;
			}
			else {
				row = rowCnt + 2;
				CvPoint start = colPxs[0];
				CvPoint end = CvPoint(list.back()); end.y += windowSize;
				test.at<uchar>(end) = 255;
				rowPxs[0] = start;
				for (int i = 0; i < rowCnt; i++) {
					rowPxs[i + 1] = list.at(i);
				}
				rowPxs[row - 1] = end;
				std::cout << row << " rows found." << std::endl;
				/*for (int i = 0; i < row; i++) {
					std::cout << i + 1 << ". " << rowPxs[i].x << " " << rowPxs[i].y << std::endl;
					}*/

				board = new char*[row];
				//highlight = new unsigned char*[row];
				for (int i = 0; i < row; i++) {
					board[i] = new char[col];
					//highlight[i] = new unsigned char[col];
					for (int j = 0; j < col; j++) {
						board[i][j] = EMPTY;
					}
				}
				cvSaveImage("RowColPxs.bmp", new IplImage(test));
				return true;
			}
		}

		/*Mat smoothed = smoothing(gray);*/

		//imshow("d", isrc);
		//imshow("", src);
	}
	catch (Exception e){
		return false;
	}
	return false;
}

void Status::printBoard() {
	for (int j = 0; j < row; j++) {
		for (int i = 0; i < col; i++) {
			if (board[j][i] == EMPTY) std::cout << "¦«";
			else if(board[j][i] == WHITE) std::cout << "¡Ü";
			else if (board[j][i] == BLACK) std::cout << "¡Û";
		}
		std::cout << std::endl;
	}
}
bool Status::BoardCheck() {
	try{
		int checkWindow = windowSize / 2;

		for (int j = 0; j < row; j++) {
			for (int i = 0; i < col; i++) {
				CvPoint testPoint = getPos(i, j);
				int cnt_b = 0, cnt_w = 0;
				for (int wx = testPoint.x; wx < testPoint.x + checkWindow && wx < size.width; wx++) {
					for (int wy = testPoint.y; wy < testPoint.y + checkWindow && wy<size.height; wy++) {
						if (src.at<uchar>(wy, wx) == 0) cnt_b++;
					}
				}
				if (isrc.at<uchar>(testPoint) == 0) {
					setStone(i, j, WHITE);
				}
				else if (cnt_b>checkWindow* checkWindow*3.141592 / 4) {
					setStone(i, j, BLACK);
				}
				else {
					setStone(i, j, EMPTY);
				}
			}
		}
		printBoard();
	}
	catch (Exception e){
		return false;
	}
	return true;
}