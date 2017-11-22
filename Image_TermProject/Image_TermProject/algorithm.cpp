#include<iostream>
#include"algorithm.h"



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
Algor::Algor(char inputarray[][19]){
	int vertcount = 0;
	int diagcount1 = 0;
	int diagcount2 = 0;
	int horcount = 0;
	int vertempcount = 0;
	int diagempcount1 = 0;
	int diagempcount2 = 0;
	int horempcount = 0;
	for (int i = 0; i < 19; i++){
		vector<char> myRow(19, 0);
		data.push_back(myRow);
	}
	for (int i = 0; i < 19; i++){
		vector<unsigned char> Row2(19, 0);
		highlight.push_back(Row2);
	}
	for (int i = 0; i < 19; i++){
		for (int j = 0; j < 19; j++){
			data[i][j] = inputarray[j][i];
		}
	}

}
Algor::Algor(char inputarray[][15]){
	int vertcount = 0;
	int diagcount1 = 0;
	int diagcount2 = 0;
	int horcount = 0;
	int vertempcount = 0;
	int diagempcount1 = 0;
	int diagempcount2 = 0;
	int horempcount = 0;
	for (int i = 0; i < 15; i++){
		vector<char> myRow(15, 0);
		data.push_back(myRow);
	}
	for (int i = 0; i < 15; i++){
		vector<unsigned char> Row2(15, 0);
		highlight.push_back(Row2);
	}
	for (int i = 0; i < 15; i++){
		for (int j = 0; j < 15; j++){
			data[i][j]=inputarray[j][i];
		}
	}


}
Algor::~Algor(){
	cout << "destructor È£Ãâ";
}
void Algor::search(int a, int b){
	int x = a;
	int y = b;
	int size = data.size();

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

		if ((x + i) < data.size()){
			if (data[x + i][y] == 1){
				horcount -= 3;
			}
			else if (data[x + i][y] == 0){
				if ((x + i) != (data.size()-1) && (x + i) != 0){
					if (data[x + i + 1][y] == -1 && data[x + i - 1][y] == -1)
						horempcount += 1;
				}
			}
			else{
				horcount += 1;
			}
		}
		if ((x + i) < size && (y + i) < size){
			if (data[x + i][y + i] == 1){
				diagcount1 -= 3;
			}
			else if (data[x + i][y + i] == 0){
				if ((x + i) != (size - 1) && (x + i) != 0 && (y + i) != 0 && (y + i) != (size - 1)){
					if (data[x + i + 1][y + i + 1] == -1 && data[x + i - 1][y + i - 1] == -1)
						diagempcount1 += 1;
				}
			}
			else{
				diagcount1 += 1;
			}
		}
		if ((y + i) < size){
			if (data[x][y + i] == 1){
				vertcount -= 3;
			}
			else if (data[x][y + i] == 0){
				if ((y + i) != (size - 1) && (y + i) != 0){
					if (data[x][y + i + 1] == -1 && data[x][y + i - 1] == -1)
						vertempcount += 1;
				}
			}
			else{
				vertcount += 1;
			}
		}
		if ((x + i) < size && (y - i) >= 0){
			if (data[x + i][y - i] == 1){
				diagcount2 -= 3;
			}
			else if (data[x + i][y - i] == 0){
				if ((x + i) != (size - 1) && (x + i) != 0 && (y - i) != 0 && (y - i) != (size - 1)){
					if (data[x + i + 1][y - i - 1] == -1 && data[x + i - 1][y - i + 1] == -1)
						diagempcount2 += 1;
				}
			}
			else{
				diagcount2 += 1;
			}

		}
	}
	highlighting(x, y, size, 1);
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
				if ((x - i) != (data.size() - 1) && (x - i) != 0){
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
				if ((x - i) != (size - 1) && (x - i) != 0 && (y - i) != 0 && (y - i) != (size - 1)){
					if (data[x - i + 1][y - i + 1] == -1 && data[x - i - 1][y - i - 1] == -1)
						diagempcount1 += 1;
				}
			}
			else{
				diagcount1 += 1;
			}
		}
		if ((y - i) >= 0){
			if (data[x][y + i] == 1){
				vertcount -= 3;
			}
			else if (data[x][y + i] == 0){
				if ((y + i) != (size - 1) && (y + i) != 0){
					if (data[x][y + i + 1] == -1 && data[x][y + i - 1] == -1)
						vertempcount += 1;
				}
			}
			else{
				vertcount += 1;
			}
		}
		if ((x - i) >= 0 && (y + i) < size){
			if (data[x - i][y + i] == 1){
				diagcount2 -= 3;
			}
			else if (data[x - i][y + i] == 0){
				if ((x - i) != (size - 1) && (x - i) != 0 && (y + i) != 0 && (y + i) != (size - 1)){
					if (data[x - i + 1][y + i - 1] == -1 && data[x - i - 1][y + i + 1] == -1)
						diagempcount2 += 1;
				}
			}
			else{
				diagcount2 += 1;
			}

		}
	}
	highlighting(x, y, size, 0);




}

void Algor::highlighting(int x, int y, int size, bool key){
	if (key == 1){
		for (int i = 1; i <= 4; i++){

			if ((x + i) < size){
				if (data[x + i][y] == 0){
					switch (horcount){
					case 0:
						if (horempcount == 0){
							highlight[x + i][y] = (unsigned char)(highlight[x + i][y] + 5);

						}
						else if (horempcount == 1){
							highlight[x + i][y] = (unsigned char)(highlight[x + i][y] + 5);
						}
						break;



					case 3:
						highlight[x + i][y] = (unsigned char)(highlight[x + i][y] + 10);
						break;

					case 4:
						highlight[x + i][y] = (unsigned char)(highlight[x + i][y] + 255);
						break;
					case -1:
						if (horempcount == 1){
							highlight[x + i][y] = (unsigned char)(highlight[x + i][y] + 5);
						}
						break;
					}
				}

			}
			if ((x + i) < size && (y + i) < size){
				if (data[x + i][y + i] == 0){
					switch (diagcount1){
					case 0:
						if (diagempcount1 == 0){
							highlight[x + i][y + i] = (unsigned char)(highlight[x + i][y + i] + 5);

						}
						else if (diagempcount1 == 1){
							highlight[x + i][y + i] = (unsigned char)(highlight[x + i][y + i] + 5);
						}
						break;



					case 3:
						highlight[x + i][y + i] = (unsigned char)(highlight[x + i][y + i] + 10);
						break;

					case 4:
						highlight[x + i][y + i] = (unsigned char)(highlight[x + i][y + i] + 255);
						break;
					case -1:
						if (diagempcount1 == 1){
							highlight[x + i][y + i] = (unsigned char)(highlight[x + i][y + i] + 5);
						}
						break;

					}
				}

			}
			if ((y + i) < size){
				if (data[x][y + i] == 0){
					switch (vertcount){
					case 0:
						if (vertempcount == 0){
							highlight[x][y + i] = (unsigned char)(highlight[x][y + i] + 5);

						}
						else if (vertempcount == 1){
							highlight[x][y + i] = (unsigned char)(highlight[x][y + i] + 5);
						}
						break;



					case 3:
						highlight[x][y + i] = (unsigned char)(highlight[x][y + i] + 10);
						break;

					case 4:
						highlight[x][y + i] = (unsigned char)(highlight[x][y + i] + 255);
						break;
					case -1:
						if (vertempcount == 1){
							highlight[x][y + i] = (unsigned char)(highlight[x][y + i] + 5);
						}
						break;

					}
				}

			}
			if ((x + i) < size && (y - i) >= 0){
				if (data[x + i][y - i] == 0){
					switch (diagcount2){
					case 0:
						if (diagempcount2 == 0){
							highlight[x + i][y - i] = (unsigned char)(highlight[x + i][y - i] + 5);

						}
						else if (diagempcount2 == 1){
							highlight[x + i][y - i] = (unsigned char)(highlight[x + i][y - i] + 5);
						}
						break;



					case 3:
						highlight[x + i][y - i] = (unsigned char)(highlight[x + i][y - i] + 10);
						break;

					case 4:
						highlight[x + i][y - i] = (unsigned char)(highlight[x + i][y - i] + 255);
						break;
					case -1:
						if (diagempcount2 == 1){
							highlight[x + i][y - i] = (unsigned char)(highlight[x + i][y - i] + 5);
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
							highlight[x + i][y] = (unsigned char)(highlight[x + i][y] + 5);

						}
						else if (horempcount == 1){
							highlight[x + i][y] = (unsigned char)(highlight[x + i][y] + 5);
						}
						break;



					case 3:
						highlight[x + i][y] = (unsigned char)(highlight[x + i][y] + 10);
						break;

					case 4:
						highlight[x + i][y] = (unsigned char)(highlight[x + i][y] + 255);
						break;
					case -1:
						if (horempcount == 1){
							highlight[x + i][y] = (unsigned char)(highlight[x + i][y] + 5);
						}
						break;

					}
				}

			}
			if ((x + i) >= 0 && (y + i) >=0){
				if (data[x + i][y + i] == 0){
					switch (diagcount1){
					case 0:
						if (diagempcount1 == 0){
							highlight[x + i][y + i] = (unsigned char)(highlight[x + i][y + i] + 5);

						}
						else if (diagempcount1 == 1){
							highlight[x + i][y + i] = (unsigned char)(highlight[x + i][y + i] + 5);
						}
						break;



					case 3:
						highlight[x + i][y + i] = (unsigned char)(highlight[x + i][y + i] + 10);
						break;

					case 4:
						highlight[x + i][y + i] = (unsigned char)(highlight[x + i][y + i] + 255);
						break;
					case -1:
						if (diagempcount1 == 1){
							highlight[x + i][y + i] = (unsigned char)(highlight[x + i][y + i] + 5);
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
							highlight[x][y + i] = (unsigned char)(highlight[x][y + i] + 5);

						}
						else if (vertempcount == 1){
							highlight[x][y + i] = (unsigned char)(highlight[x][y + i] + 5);
						}
						break;



					case 3:
						highlight[x][y + i] = (unsigned char)(highlight[x][y + i] + 10);
						break;

					case 4:
						highlight[x][y + i] = (unsigned char)(highlight[x][y + i] + 255);
						break;
					case -1:
						if (vertempcount == 1){
							highlight[x][y + i] = (unsigned char)(highlight[x][y + i] + 5);
						}
						break;

					}
				}

			}
			if ((x + i) >= 0 && (y - i) <size){
				if (data[x + i][y - i] == 0){
					switch (diagcount2){
					case 0:
						if (diagempcount2 == 0){
							highlight[x + i][y - i] = (unsigned char)(highlight[x + i][y - i] + 5);

						}
						else if (diagempcount2 == 1){
							highlight[x + i][y - i] = (unsigned char)(highlight[x + i][y - i] + 5);
						}
						break;



					case 3:
						highlight[x + i][y - i] = (unsigned char)(highlight[x + i][y - i] + 10);
						break;

					case 4:
						highlight[x + i][y - i] = (unsigned char)(highlight[x + i][y - i] + 255);
						break;
					case -1:
						if (diagempcount2 == 1){
							highlight[x + i][y - i] = (unsigned char)(highlight[x + i][y - i] + 5);
						}
						break;

					}
				}


			}
		}



	}

}

unsigned char Algor::GetHighlight(int x, int y){


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
	return highlight;
}