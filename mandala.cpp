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
// void drawReflection(vector < pair < int, int > > points, lineEquation le,
// 	Mat obj, Vec3b color)
// {
	
// }
void drawBoard(Mat obj, int depth, Vec3b color)
{
	double stepSize = 45.0/pow(2,depth);
	double mDeg =0.0;
	vector <lineEquation> le;
	le.push_back(lineEquation(1, 1, 0));
	le.push_back(lineEquation(0, 1, 0));
	le.push_back(lineEquation(1, 0, 0));
	for(int i =0; i!=le.size(); i++)
	{
		le[i].displayVal();
	}
	while(mDeg <= 45)
	{
		cout<<mDeg<<" ";
		double mRad = degreeToRadian(mDeg);
		cout<<mRad<<" "<<tan(mRad)<<endl;
		int inp;
		pair <int, int> a = translate(make_pair(
			double(tan(mRad) * int(BOARD_WIDTH/2)), BOARD_WIDTH/2));
		pair <int, int> b = translate(make_pair(0,0));
		vector <pair <int, int>> linePoints = getLine(a,b);	
		// for(int i=0; i<line.size(); i++)
		// {
		// 	cout<<line[i].first<<" "<<line[i].second<<endl;
		// }
		drawPoints(linePoints, obj, COLOR_BOARD);
		drawReflection(linePoints, le, obj, COLOR_BOARD);
		mDeg+=stepSize;
		// 	cin>>inp;
	}
	for(int i=11; i<40; i++)
	{
		obj.at<Vec3b>(i, i+5)=COLOR_BACKGROUND;
	}

}
int main()
{
	namedWindow("canavas", WINDOW_NORMAL);
	namedWindow("original", WINDOW_NORMAL);
	Mat canavas(ROW, COLUMN, CV_8UC3);
	int depth = 2;
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
		COLOR_BACKGROUND);
	// initializeMatObject(BOARD_ROW, 
	// 	BOARD_ROW + BOARD_HEIGHT,
	// 	BOARD_COLUMN,
	// 	BOARD_COLUMN + BOARD_WIDTH, 
	// 	canavas, 
	// 	COLOR_BACKGROUND);
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