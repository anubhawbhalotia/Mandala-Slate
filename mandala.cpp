#include <opencv2/highgui.hpp>
#include <bits/stdc++.h>
#include <opencv2/imgproc.hpp>
#include <fstream>
#include "slatelib.h"
#include "mandalalib.h"
using namespace cv;
using namespace std;
Mat original(ROW, COLUMN, CV_8UC3);
Mat livePoint(ROW, COLUMN, CV_8UC3);
Mat canavas(ROW, COLUMN, CV_8UC3);
VideoCapture cap("v4l2:///dev/video0");
int main()
{
	namedWindow("canavas", WINDOW_NORMAL);
	namedWindow("original", WINDOW_NORMAL);
	vector <lineEquation> le;
	le.push_back(lineEquation(1, -1, 0));
	le.push_back(lineEquation(0, 1, 0));
	le.push_back(lineEquation(1, 0, 0));
	int depth = 2;
	depth-=2;
	if(cap.isOpened()==false)
	{
		cout<<"Cannot open the video file"<<endl;
		cin.get();
	}
	// initializeMatObject(canavas, COLOR_BACKGROUND);
	initializeMatObject(0, ROW, 0, COLUMN, canavas, COLOR_BLACK);
	initializeMatObject(BOARD_ROW, 
		BOARD_ROW + BOARD_HEIGHT,
		BOARD_COLUMN,
		BOARD_COLUMN + BOARD_WIDTH, 
		canavas, 
		COLOR_BACKGROUND);
	imshow("canavas", canavas);
	vector <lineEquation> all_le = drawBoard(canavas, 
			depth, COLOR_BOARD);
	for(int i=0; i!=all_le.size(); i++)
	{
		all_le[i].displayVal();
	}
	while(1)
	{
		vector < pair < int, int > > drawnPoints, allDrawnPoints;
		bool bSuccess=cap.read(original);
		if(bSuccess==false)
			break;	
		invertImage(original);
		initializeMatObject(0, ROW, 0, COLUMN, livePoint, COLOR_BLACK);
		binarise(original, livePoint, 2, 1, 0, COLOR_CENTRE);
		imshow("original", original);
		imshow("livePoint", livePoint);
		pair <int,int> centre=getCentre(livePoint, 100, COLOR_CENTRE);
		cout<<"centre="<<centre.first<<endl;
		drawnPoints.push_back(centre);
		if(centre.second >= BOARD_COLUMN && centre.second<BOARD_COLUMN+BOARD_WIDTH)
		{
			canavas.at<Vec3b>(centre.first, centre.second) = COLOR_DRAW_MANDALA;
			double slope = getSlope(translateOpenCVToMandala(centre));
			if(slope < 1 && slope >0 && centre.first>0 && centre.second>0)
			{
				for(int i=0; i!=all_le.size(); i++)
				{
					drawnPoints = getReflectedLine(drawnPoints, le[i]);
					cout<<"a"<<drawnPoints[0].first<<" "<<drawnPoints[0].second<<endl;
					drawPoints(drawnPoints, canavas, COLOR_DRAW_MANDALA);
					allDrawnPoints.push_back(drawnPoints[0]);
				}
			}

			for(int i=0;i<le.size(); i++)
			{
				vector < pair < int, int> > linePoints = 
					getReflectedLine(allDrawnPoints, le[i]);
				drawPoints(linePoints, canavas, COLOR_DRAW_MANDALA);
				allDrawnPoints.insert(allDrawnPoints.end(),
					linePoints.begin(), linePoints.end());
			}
		}
		int keyPress=waitKey(10);
		imshow("canavas", canavas);
	}
}