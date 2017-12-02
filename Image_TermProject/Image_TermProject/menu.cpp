#include"menu.h"



menu::menu() {
	firstX = 0;
	firstY = 0;
	lastX = 0, lastY = 0;
	w = 0;
	h = 0;
	system("mode con cols=80 lines=100");

	cout << "welcome to omok insight" << endl;

	cout << "1.start omok assistant program" << endl;



	cout << "2.exit" << endl;

	int key = 0;


	cin >> key;
	if (key == 1) {
		cout << "Choose your stone color(White:0,Black:1)" << endl;
		int p;
		cin >> p;
		while (!(p == 0 || p == 1)){
			cout << "invalid input please retype the stone color" << endl;
			cout << "Choose your stone color(White:0,Black:1)" << endl; 
			cin.ignore();
			cin >> p;
		}
		player = (p == 0) ? false : true;
		cout << "capture start" << endl;

		setcapture();
	}
	else if (key == 2) {
		exit(0);
	}
	else {
		cout << "invalid input please retype the key"<<endl;
	}




}
menu::~menu() {
	cout << "menu destructor" << endl;

}

void menu::capture() {




	HDC hScreen = GetDC(NULL);
	HDC hDC = CreateCompatibleDC(hScreen);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
	HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
	BOOL bRet = BitBlt(hDC, 0, 0, w, h, hScreen, firstX, firstY, SRCCOPY); //"board.bpm"이라는 이름으로 저장됨
	SaveBitmap("board.bmp", hBitmap);

}
void menu::setcapture() {
	POINT mouse;
	
	int clicked = 0;
	while (TRUE) {
		GetCursorPos(&mouse);
		if (clicked == 0 && (GetAsyncKeyState(VK_RBUTTON) & 0x8000))
		{
			firstX = mouse.x;
			firstY = mouse.y;
			clicked = 1;
		}
		else if (clicked == 1 && (GetAsyncKeyState(VK_RBUTTON) & 0x8000) == 0) {
			lastX = mouse.x;
			lastY = mouse.y;
			break;
		}
	}

	w = lastX - firstX;
	h = lastY - firstY;
}

void menu::SaveBitmap(char *szFilename, HBITMAP hBitmap)
{
	// get the DC 
	HDC hdc = GetDC(NULL);

	// get bitmap info
	BITMAPINFO bmpInfo;
	ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	GetDIBits(hdc, hBitmap, 0, 0, NULL, &bmpInfo, DIB_RGB_COLORS);
	if (bmpInfo.bmiHeader.biSizeImage <= 0)
		bmpInfo.bmiHeader.biSizeImage = bmpInfo.bmiHeader.biWidth*abs(bmpInfo.bmiHeader.biHeight)*(bmpInfo.bmiHeader.biBitCount + 7) / 8;

	// get real image
	LPVOID pBuf = NULL;
	if ((pBuf = malloc(bmpInfo.bmiHeader.biSizeImage)) == NULL)
	{
		MessageBox(NULL, L"Unable to Allocate Bitmap Memory", L"Error", MB_OK | MB_ICONERROR);
	}
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	GetDIBits(hdc, hBitmap, 0, bmpInfo.bmiHeader.biHeight, pBuf, &bmpInfo, DIB_RGB_COLORS);

	// bitmap file header
	BITMAPFILEHEADER bmpFileHeader;
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;
	bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmpInfo.bmiHeader.biSizeImage;
	bmpFileHeader.bfType = 'MB';
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// file IO
	FILE* fp = fopen(szFilename, "wb");
	if (fp == NULL)
	{
		MessageBox(NULL, L"Unable to Create Bitmap File", L"Error", MB_OK | MB_ICONERROR);
	}
	fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&bmpInfo.bmiHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(pBuf, bmpInfo.bmiHeader.biSizeImage, 1, fp);

	if (hdc) ReleaseDC(NULL, hdc);
	if (pBuf) free(pBuf);
	if (fp) fclose(fp);
}

bool menu::getplayer() {
	return player;
}