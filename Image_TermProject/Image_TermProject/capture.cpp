#include<Windows.h>
#include<iostream>

using namespace std;


void SaveBitmap(char *szFilename, HBITMAP hBitmap);

int main(){
	POINT mouse;
	cout << "capture start" << endl;
	//HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE);
	Sleep(1000);  //클릭 할 준비를 위해 준 시간 (프로그램 실행 후 1초 뒤에 드래그 해야함)

	int count = 0;
	int firstX = 0, firstY = 0;
	int lastX = 0, lastY = 0;

	int clicked = 0;

	while (TRUE){
		GetCursorPos(&mouse);
		if (clicked == 0 && (GetKeyState(VK_LBUTTON) & 0x80))
		{
			firstX = mouse.x;
			firstY = mouse.y;
			clicked = 1;
		}
		else if (clicked == 1 && (GetKeyState(VK_LBUTTON) & 0x80) == 0){
			lastX = mouse.x;
			lastY = mouse.y;
			break;
		}
	}


	int w = lastX - firstX;
	int h = lastY - firstY;

	HDC hScreen = GetDC(NULL);
	HDC hDC = CreateCompatibleDC(hScreen);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
	HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
	BOOL bRet = BitBlt(hDC, 0, 0, w, h, hScreen, firstX, firstY, SRCCOPY); //"board.bpm"이라는 이름으로 저장됨
	SaveBitmap("board.bmp", hBitmap);


	return 0;
}


void  SaveBitmap(char *szFilename, HBITMAP hBitmap)
{
	// DC를 얻어옴
	HDC hdc = GetDC(NULL);

	// bitmap info 를 얻어옴
	BITMAPINFO bmpInfo;
	ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	GetDIBits(hdc, hBitmap, 0, 0, NULL, &bmpInfo, DIB_RGB_COLORS);
	if (bmpInfo.bmiHeader.biSizeImage <= 0)
		bmpInfo.bmiHeader.biSizeImage = bmpInfo.bmiHeader.biWidth*abs(bmpInfo.bmiHeader.biHeight)*(bmpInfo.bmiHeader.biBitCount + 7) / 8;

	// 실제 image 내용을 얻어오기
	LPVOID pBuf = NULL;
	if ((pBuf = malloc(bmpInfo.bmiHeader.biSizeImage)) == NULL)
	{
		MessageBox(NULL, L"Unable to Allocate Bitmap Memory", L"Error", MB_OK | MB_ICONERROR);
	}
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	GetDIBits(hdc, hBitmap, 0, bmpInfo.bmiHeader.biHeight, pBuf, &bmpInfo, DIB_RGB_COLORS);

	// bitmap file header 만들기
	BITMAPFILEHEADER bmpFileHeader;
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;
	bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmpInfo.bmiHeader.biSizeImage;
	bmpFileHeader.bfType = 'MB';
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// 파일을 열고 쓰기
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