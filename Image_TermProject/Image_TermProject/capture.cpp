#include<Windows.h>
#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include<opencv\highgui.h>
#include<opencv\cv.h>


using namespace std;
using namespace cv;

void SaveBitmap(char *szFilename, HBITMAP hBitmap);
int main(){
   cout << "capture start" << endl;
   //HWND hWnd = GetConsoleWindow();
   //ShowWindow(hWnd, SW_HIDE);
   Sleep(1000);

   int x1, x2, y1, y2, w, h;
   int boardWidth, boardHeight;

   x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
   y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
   x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
   y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);

   w = x2 - x1;
   h = y2 - y1;

   cout << x1 << endl;
   cout << y1 << endl;
   cout << w << endl;
   cout << h << endl;

   HDC hScreen = GetDC(NULL);
   HDC hDC = CreateCompatibleDC(hScreen);
   HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
   HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
   BOOL bRet = BitBlt(hDC, 0, 0, w, h, hScreen, x1, y1, SRCCOPY); //get a full screen image
   SaveBitmap("fullScreen.bmp", hBitmap);

   Mat image;
   image = imread("fullScreen.bmp");


   int screenWidth = image.cols;
   int screenHeight = image.rows;

   cout << screenWidth << endl;
   cout << screenHeight << endl;

   for (int y = 0; y < screenHeight; y++){
      for (int x = 0; x < screenWidth; x++){
         image.at<uchar>(y, x) = 255;
         cout << y << x;

         /*
         for (int c = 0; c < 3; c++){
         cout << image.at<Vec3b>(y, x)[c];
         }
         */
		 cout << endl;
      }
      cout << endl;
   }
   
                     




   /*hScreen = GetDC(NULL);
   hDC = CreateCompatibleDC(hScreen);
   hBitmap = CreateCompatibleBitmap(hScreen, w, h);
   old_obj = SelectObject(hDC, hBitmap);
   bRet = BitBlt(hDC, 0, 0, 100, 100, hScreen, x1, y1, SRCCOPY);
   SaveBitmap("board.bmp", hBitmap);      //board.bmp���Ϸ� ����
   */

   

   


   imshow("board", image);

   waitKey(0);
   


   //system("pause");

   return 0;
}


void  SaveBitmap(char *szFilename, HBITMAP hBitmap)
{
   // DC�� ����
   HDC hdc = GetDC(NULL);

   // bitmap info �� ����
   BITMAPINFO bmpInfo;
   ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
   bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   GetDIBits(hdc, hBitmap, 0, 0, NULL, &bmpInfo, DIB_RGB_COLORS);
   if (bmpInfo.bmiHeader.biSizeImage <= 0)
      bmpInfo.bmiHeader.biSizeImage = bmpInfo.bmiHeader.biWidth*abs(bmpInfo.bmiHeader.biHeight)*(bmpInfo.bmiHeader.biBitCount + 7) / 8;

   // ���� image ������ ������
   LPVOID pBuf = NULL;
   if ((pBuf = malloc(bmpInfo.bmiHeader.biSizeImage)) == NULL)
   {
      MessageBox(NULL, L"Unable to Allocate Bitmap Memory", L"Error", MB_OK | MB_ICONERROR);
   }
   bmpInfo.bmiHeader.biCompression = BI_RGB;
   GetDIBits(hdc, hBitmap, 0, bmpInfo.bmiHeader.biHeight, pBuf, &bmpInfo, DIB_RGB_COLORS);

   // bitmap file header �����
   BITMAPFILEHEADER bmpFileHeader;
   bmpFileHeader.bfReserved1 = 0;
   bmpFileHeader.bfReserved2 = 0;
   bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmpInfo.bmiHeader.biSizeImage;
   bmpFileHeader.bfType = 'MB';
   bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

   // ������ ���� ����
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