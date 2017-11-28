#include<iostream>
#include<vector>
#include<Windows.h>
using namespace std;

class menu{
private :
	 int key;
	 bool player;
	 int firstX;
	 int firstY;
	 int lastX;
	 int lastY;
	 int w;
	 int h;

public:
	menu();
	~menu();
	void capture();
	void recapture();   //리캡쳐 시 출력
	void start();
	void  SaveBitmap(char *szFilename, HBITMAP hBitmap);
	void setcapture();
	bool getplayer();
};