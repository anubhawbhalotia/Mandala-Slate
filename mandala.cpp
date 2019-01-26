#include <opencv2/highgui.hpp>
#include <bits/stdc++.h>
#include <opencv2/imgproc.hpp>
#include <fstream>
#include "slatelib.h"
#include "mandalalib.h"
using namespace cv;
using namespace std;
Mat original(ROW, COLUMN, CV_8UC3);
VideoCapture cap("v4l2:///dev/video0");

int main()
{
	namedWindow("canavas", WINDOW_NORMAL);
	namedWindow("original", WINDOW_NORMAL);
	Mat canavas(ROW, COLUMN, CV_8UC3);
	int depth = 5;
	depth-=2;
	if(cap.isOpened()==false)
	{
		cout<<"Cannot open the video file"<<endl;
		cin.get();
	}
	// initializeMatObject(canavas, COLOR_BACKGROUND);
	initializeMatObject(0, 
		ROW,
		0,
		COLUMN, 
		canavas, 
		COLOR_BLACK);
	initializeMatObject(BOARD_ROW, 
		BOARD_ROW + BOARD_HEIGHT,
		BOARD_COLUMN,
		BOARD_COLUMN + BOARD_WIDTH, 
		canavas, 
		COLOR_BACKGROUND);
	imshow("canavas", canavas);
	drawBoard(canavas, 
			depth, 
			COLOR_BOARD);
	while(1)
	{
		bool bSuccess=cap.read(original);
		imshow("original", original);
		if(bSuccess==false)
			break;	
		int keyPress=waitKey(10);
		imshow("canavas", canavas);
	}
}