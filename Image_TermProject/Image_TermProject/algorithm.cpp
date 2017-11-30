#include<iostream>
#include"algorithm.h"

#define TWO 10
#define THREE 100
#define FOUR 200

Algor::Algor(){
	int vertcount = 0;
	int diagcount1 = 0;
	int diagcount2 = 0;
	int horcount = 0;
	int vertempcount = 0;
	int diagempcount1 = 0;
	int diagempcount2 = 0;
	int horempcount = 0;

}
Algor::Algor(char **inputarray, int inputrow, int inputcol, bool player){
	int vertcount = 0;
	int diagcount1 = 0;
	int diagcount2 = 0;
	int horcount = 0;
	int vertempcount = 0;
	int diagempcount1 = 0;
	int diagempcount2 = 0;
	int horempcount = 0;
	for (int i = 0; i < inputrow; i++){
		vector<char> myRow(inputcol, 0);
		data.push_back(myRow);
	}
	for (int i = 0; i < inputrow; i++){
		vector<unsigned int> Row2(inputcol, 0);
		highlight.push_back(Row2);
	}
	if (player == 1){
		for (int i = 0; i < inputrow; i++){
			for (int j = 0; j < inputcol; j++){
				data[i][j] = inputarray[i][j];
			}
		}
	}
	else{
		for (int i = 0; i < inputrow; i++){
			for (int j = 0; j < inputcol; j++){
				data[i][j] = -1 * inputarray[i][j];
			}
		}
	}

}

Algor::~Algor(){
	cout << "destructor call";
}

void Algor::search(int a, int b){
	int x = a;
	int y = b;
	int sizeRow = data.size();
	int sizeCol = data[1].size();

	if (data[x][y] == 1){
		vertcount = -3;
		diagcount1 = -3;
		diagcount2 = -3;
		horcount = -3;
	}
	else{
		vertcount = 1;
		diagcount1 = 1;
		diagcount2 = 1;
		horcount = 1;
	}
	for (int i = 1; i <= 4; i++){

		if ((x + i) < sizeCol){
			if (data[x + i][y] == 1){
				horcount -= 3;
			}
			else if (data[x + i][y] == 0){
				if ((x + i) != ((sizeCol - 1)) && (x + i) != 0){
					if (data[x + i + 1][y] == -1 && data[x + i - 1][y] == -1)
						horempcount += 1;
				}
			}
			else{
				horcount += 1;
			}
		}
		if ((x + i) < sizeCol && (y + i) < sizeRow){
			if (data[x + i][y + i] == 1){
				diagcount1 -= 3;
			}
			else if (data[x + i][y + i] == 0){
				if ((x + i) != (sizeCol - 1) && (x + i) != 0 && (y + i) != 0 && (y + i) != (sizeRow - 1)){
					if (data[x + i + 1][y + i + 1] == -1 && data[x + i - 1][y + i - 1] == -1)
						diagempcount1 += 1;
				}
			}
			else{
				diagcount1 += 1;
			}
		}
		if ((y + i) < sizeRow){
			if (data[x][y + i] == 1){
				vertcount -= 3;
			}
			else if (data[x][y + i] == 0){
				if ((y + i) != (sizeRow - 1) && (y + i) != 0){
					if (data[x][y + i + 1] == -1 && data[x][y + i - 1] == -1)
						vertempcount += 1;
				}
			}
			else{
				vertcount += 1;
			}
		}
		if ((x + i) < sizeCol && (y - i) >= 0){
			if (data[x + i][y - i] == 1){
				diagcount2 -= 3;
			}
			else if (data[x + i][y - i] == 0){
				if ((x + i) != (sizeRow - 1) && (x + i) != 0 && (y - i) != 0 && (y - i) != (sizeCol - 1)){
					if (data[x + i + 1][y - i - 1] == -1 && data[x + i - 1][y - i + 1] == -1)
						diagempcount2 += 1;
				}
			}
			else{
				diagcount2 += 1;
			}

		}
	}
	highlighting(x, y, sizeCol,sizeRow, 1);
	if (data[x][y] == 1){
		vertcount = -3;
		diagcount1 = -3;
		diagcount2 = -3;
		horcount = -3;
	}
	else{
		vertcount = 1;
		diagcount1 = 1;
		diagcount2 = 1;
		horcount = 1;
	}
	for (int i = 1; i <= 4; i++){

		if ((x - i) >= 0){
			if (data[x - i][y] == 1){
				horcount -= 3;
			}
			else if (data[x - i][y] == 0){
				if ((x - i) != (sizeCol - 1) && (x - i) != 0){
					if (data[x - i + 1][y] == -1 && data[x - i - 1][y] == -1)
						horempcount += 1;
				}
			}
			else{
				horcount += 1;
			}
		}
		if ((x - i) >= 0 && (y - i) >= 0){
			if (data[x - i][y - i] == 1){
				diagcount1 -= 3;
			}
			else if (data[x - i][y - i] == 0){
				if ((x - i) != (sizeCol - 1) && (x - i) != 0 && (y - i) != 0 && (y - i) != (sizeRow - 1)){
					if (data[x - i + 1][y - i + 1] == -1 && data[x - i - 1][y - i - 1] == -1)
						diagempcount1 += 1;
				}
			}
			else{
				diagcount1 += 1;
			}
		}
		if ((y - i) >= 0){
			if (data[x][y - i] == 1){
				vertcount -= 3;
			}
			else if (data[x][y - i] == 0){
				if ((y - i) != (sizeRow - 1) && (y - i) != 0){
					if (data[x][y - i + 1] == -1 && data[x][y - i - 1] == -1)
						vertempcount += 1;
				}
			}
			else{
				vertcount += 1;
			}
		}
		if ((x - i) >= 0 && (y + i) < sizeRow){
			if (data[x - i][y + i] == 1){
				diagcount2 -= 3;
			}
			else if (data[x - i][y + i] == 0){
				if ((x - i) != (sizeCol - 1) && (x - i) != 0 && (y + i) != 0 && (y + i) != (sizeRow - 1)){
					if (data[x - i + 1][y + i - 1] == -1 && data[x - i - 1][y + i + 1] == -1)
						diagempcount2 += 1;
				}
			}
			else{
				diagcount2 += 1;
			}

		}
	}
	highlighting(x, y, sizeCol, sizeRow, 0);




}

void Algor::highlighting(int x, int y, int sizeCol, int sizeRow, bool key){
	if (key == 1){
		for (int i = 1; i <= 4; i++){

			if ((x + i) < sizeCol){
				if (data[x + i][y] == 0){
					switch (horcount){
					case 0:
						if (horempcount == 0){
							highlight[x + i][y] = (highlight[x + i][y] + 5);

						}
						else if (horempcount == 1){
							highlight[x + i][y] = (highlight[x + i][y] + 5);
						}
						break;

					case 2:
						////////////////////////
						highlight[x + i][y] += TWO;
						break;

					case 3:
						highlight[x + i][y] = (highlight[x + i][y] + THREE);
						break;

					case 4:
						highlight[x + i][y] = (highlight[x + i][y] + FOUR);
						break;
					case 5:
						cout << "game over!";
						break;
					case -1:
						if (horempcount == 1){
							highlight[x + i][y] = (highlight[x + i][y] + 5);
						}
						break;
					}
				}

			}
			if ((x + i) < sizeCol && (y + i) < sizeRow){
				if (data[x + i][y + i] == 0){
					switch (diagcount1){
					case 0:
						if (diagempcount1 == 0){
							highlight[x + i][y + i] = (highlight[x + i][y + i] + 5);

						}
						else if (diagempcount1 == 1){
							highlight[x + i][y + i] = (highlight[x + i][y + i] + 5);
						}
						break;

					case 2:
						////////////////////////
						highlight[x + i][y + i] += TWO;
						break;

					case 3:
						highlight[x + i][y + i] = (highlight[x + i][y + i] + THREE);
						break;

					case 4:
						highlight[x + i][y + i] = (highlight[x + i][y + i] + FOUR);
						break;
					case 5:
						cout << "game over!";
						break;
					case -1:
						if (diagempcount1 == 1){
							highlight[x + i][y + i] = (highlight[x + i][y + i] + 5);
						}
						break;

					}
				}

			}
			if ((y + i) < sizeRow){
				if (data[x][y + i] == 0){
					switch (vertcount){
					case 0:
						if (vertempcount == 0){
							highlight[x][y + i] = (highlight[x][y + i] + 5);

						}
						else if (vertempcount == 1){
							highlight[x][y + i] = (highlight[x][y + i] + 5);
						}
						break;

					case 2:
						////////////////////////
						highlight[x][y + i] += TWO;
						break;

					case 3:
						highlight[x][y + i] = (highlight[x][y + i] + THREE);
						break;

					case 4:
						highlight[x][y + i] = (highlight[x][y + i] + FOUR);
						break;
					case 5:
						cout << "game over!";
						break;
					case -1:
						if (vertempcount == 1){
							highlight[x][y + i] = (highlight[x][y + i] + 5);
						}
						break;

					}
				}

			}
			if ((x + i) < sizeCol && (y - i) >= 0){
				if (data[x + i][y - i] == 0){
					switch (diagcount2){
					case 0:
						if (diagempcount2 == 0){
							highlight[x + i][y - i] = (highlight[x + i][y - i] + 5);

						}
						else if (diagempcount2 == 1){
							highlight[x + i][y - i] = (highlight[x + i][y - i] + 5);
						}
						break;


					case 2:
						////////////////////////
						highlight[x + i][y - i] += TWO;
						break;
					case 3:
						highlight[x + i][y - i] = (highlight[x + i][y - i] + THREE);
						break;

					case 4:
						highlight[x + i][y - i] = (highlight[x + i][y - i] + FOUR);
						break;
					case 5:
						cout << "game over!";
						break;

					case -1:
						if (diagempcount2 == 1){
							highlight[x + i][y - i] = (highlight[x + i][y - i] + 5);
						}
						break;

					}
				}


			}
		}
	}
	else{
		for (int i = -1; i >= -4; i--){

			if ((x + i) >= 0){
				if (data[x + i][y] == 0){
					switch (horcount){
					case 0:
						if (horempcount == 0){
							highlight[x + i][y] = (highlight[x + i][y] + 5);

						}
						else if (horempcount == 1){
							highlight[x + i][y] = (highlight[x + i][y] + 5);
						}
						break;

					case 2:
						////////////////////////
						highlight[x + i][y] += TWO;
						break;

					case 3:
						highlight[x + i][y] = (highlight[x + i][y] + THREE);
						break;

					case 4:
						highlight[x + i][y] = (highlight[x + i][y] + FOUR);
						break;
					case 5:
						cout << "game over!";
						break;
					case -1:
						if (horempcount == 1){
							highlight[x + i][y] = (highlight[x + i][y] + 5);
						}
						break;

					}
				}

			}
			if ((x + i) >= 0 && (y + i) >= 0){
				if (data[x + i][y + i] == 0){
					switch (diagcount1){
					case 0:
						if (diagempcount1 == 0){
							highlight[x + i][y + i] = (highlight[x + i][y + i] + 5);

						}
						else if (diagempcount1 == 1){
							highlight[x + i][y + i] = (highlight[x + i][y + i] + 5);
						}
						break;

					case 2:
						////////////////////////
						highlight[x + i][y + i] += TWO;
						break;

					case 3:
						highlight[x + i][y + i] = (highlight[x + i][y + i] + THREE);
						break;

					case 4:
						highlight[x + i][y + i] = (highlight[x + i][y + i] + FOUR);
						break;
					case 5:
						cout << "game over!";
						break;
					case -1:
						if (diagempcount1 == 1){
							highlight[x + i][y + i] = (highlight[x + i][y + i] + 5);
						}
						break;

					}
				}

			}
			if ((y + i) >= 0){
				if (data[x][y + i] == 0){
					switch (vertcount){
					case 0:
						if (vertempcount == 0){
							highlight[x][y + i] = (highlight[x][y + i] + 5);

						}
						else if (vertempcount == 1){
							highlight[x][y + i] = (highlight[x][y + i] + 5);
						}
						break;

					case 2:
						////////////////////////
						highlight[x][y + i] += TWO;
						break;

					case 3:
						highlight[x][y + i] = (highlight[x][y + i] + THREE);
						break;

					case 4:
						highlight[x][y + i] = (highlight[x][y + i] + FOUR);
						break;
					case 5:
						cout << "game over!";
						break;
					case -1:
						if (vertempcount == 1){
							highlight[x][y + i] = (highlight[x][y + i] + 5);
						}
						break;

					}
				}

			}
			if ((x + i) >= 0 && (y - i) <sizeRow){
				if (data[x + i][y - i] == 0){
					switch (diagcount2){
					case 0:
						if (diagempcount2 == 0){
							highlight[x + i][y - i] = (highlight[x + i][y - i] + 5);

						}
						else if (diagempcount2 == 1){
							highlight[x + i][y - i] = (highlight[x + i][y - i] + 5);
						}
						break;

					case 2:
						////////////////////////
						highlight[x + i][y - i] += TWO;
						break;

					case 3:
						highlight[x + i][y - i] = (highlight[x + i][y - i] + THREE);
						break;

					case 4:
						highlight[x + i][y - i] = (highlight[x + i][y - i] + FOUR);
						break;
					case 5:
						cout << "game over!";
						break;
					case -1:
						if (diagempcount2 == 1){
							highlight[x + i][y - i] = (highlight[x + i][y - i] + 5);
						}
						break;

					}
				}


			}
		}



	}
	/*for (int i = 0; i < sizeRow; i++){
		for (int j = 0; j < sizeCol; j++){
			if (highlight[i][j]>255){
				highlight[i][j] = 255;
			}
		}
	}*/

}

unsigned int Algor::GetHighlight(int x, int y){


	return highlight[x][y];

}

void Algor::ClrHighlight(){
	int size = highlight.size();
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){

			highlight[i][j] = 0;
		}
	}

}

vector<vector<unsigned char>> Algor::getHB(){
	vector<vector<unsigned char>> real;
	for (int i = 0; i < highlight.size(); i++){
		vector<unsigned char> row(highlight[0].size(), 0);
		real.push_back(row);
	}
	for (int i = 0; i < highlight.size(); i++){
		for (int j = 0; j < highlight[0].size(); j++){
			real[i][j] = (unsigned char) ((highlight[i][j]>255) ? 255 : highlight[i][j]);
		}
	}
	return real;
}