#include<iostream>
#include<vector>
using namespace std;


class Algor{


private:
	vector<vector<char>> data;
	vector<vector<unsigned int>>highlight;
	int vertcount;
	int diagcount1;
	int diagcount2;
	int horcount;
	int vertempcount;
	int diagempcount1;
	int diagempcount2;
	int horempcount;
	int row;
	int col;


public:
	Algor();
	Algor(char **inputarray, int inputrow, int inputcol,bool player);
	
	~Algor();
	void search(int a , int b);
	int getnumarray();
	void highlighting(int x , int y,int sizeCol,int sizeRow,bool key);
    unsigned int GetHighlight(int x, int y);
	void ClrHighlight();
	vector<vector<unsigned char>> getHB();
	

};