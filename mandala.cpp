#include <opencv2/highgui.hpp>
#include <bits/stdc++.h>
#include <opencv2/imgproc.hpp>
#include <fstream>
#define ROW 720
#define COLUMN 1280
#define BOARD_ROW 280
#define COLUMN_ROW 0
#define BOARD_HEIGHT 720
#define BOARD_WIDTH 720
using namespace cv;
using namespace std;
Mat original(ROW, COLUMN, CV_8UC3);
VideoCapture cap("v4l2:///dev/video0");
int initializeMatObject(int r1, int c1, int r2, int c2, int rMat obj, Vec3b color)
{
	for(int i=r1;i<r2;i++)	
	{
		for(int j=c1;j<c2;j++)
		{
			obj.at<Vec3b>(i,j)=color;
		}
	}
	return 1;
}
void drawBoard(Mat obj, int depth, Vec3b color)
{

}
int main()
{
	Vec3b COLOR_BACKGROUND={255, 255, 255};
	Vec3b COLOR_BOARD = {160, 160, 160};
	int depth = 4;
	if(cap.isOpened()==false)
	{
		cout<<"Cannot open the video file"<<endl;
		cin.get();
	}
	// initializeMatObject(canavas, COLOR_BACKGROUND);
	initializeMatObject(BOARD_ROW, canavas, COLOR_BACKGROUND)
	while(1)
	{
		bool bSuccess=cap.read(original);
		if(bSuccess==false)
			break;	
		drawBoard(canavas, depth, COLOR_BOARD);


	}
}