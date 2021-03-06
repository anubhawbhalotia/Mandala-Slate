using namespace cv;
using namespace std;
#define ROW 720
#define COLUMN 1280
#define BOARD_ROW 9
#define BOARD_COLUMN 289
#define BOARD_HEIGHT 701
#define BOARD_WIDTH 701
#define PI 3.14159
Vec3b COLOR_BLACK = {0, 0, 0};
Vec3b COLOR_RED = {0, 0, 255};
Vec3b COLOR_WHITE={255, 255, 255};

Vec3b COLOR_CENTRE = COLOR_WHITE;
Vec3b COLOR_BACKGROUND= COLOR_WHITE;
Vec3b COLOR_BOARD = {160, 160, 160};
Vec3b COLOR_DRAW_MANDALA = COLOR_BLACK;

typedef struct lineEquation
{
	double a,b,c;
	lineEquation(double a,double b,double c):
	a(a), b(b), c(c) {}
	void displayVal()
	{
		cout<<a<<" "<<b<<" "<<c<<endl;
	}
}lineEquation;
pair <int, int> translateMandalaToOpenCV(pair <int, int> p)
{
	/*
		convert a coordinate from mandala coordinate syatem to opencv 
		coordinate system
		param1: .first = row, .seoond = column
	*/
	return make_pair(BOARD_ROW + (p.first -BOARD_HEIGHT/2)*-1,
		p.second + BOARD_COLUMN + BOARD_WIDTH/2);
}
pair <int, int> translateOpenCVToMandala(pair <int, int> p)
{
	/*
		convert a coordinate from opencv to mandala coordinate syatem
		coordinate system
		param1: .first = row, .seoond = column
	*/
	return make_pair((p.first - BOARD_ROW - BOARD_HEIGHT/2)*-1,
		p.second - BOARD_COLUMN - BOARD_WIDTH/2);
}
double degreeToRadian(double degree)
{
	return (degree/180)*PI;
}
vector < pair <int,int> > getReflectedLine(vector < pair< int, int> > points, 
	lineEquation le)
{
	vector < pair <int,int> > reflectedPoints;
	double a = le.a, b=le.b, c=le.c;
	for(int i=0; i!=points.size(); i++)
	{
		pair < int, int> mandalaPoint = translateOpenCVToMandala(points[i]);
		int q=mandalaPoint.first;
		int p=mandalaPoint.second;
		int x=(((p * ((a*a) - (b*b))) - (2*b *((a*q) + c)))) / ((a*a) + (b*b));
		int y=(((q * ((b*b) - (a*a))) - (2*a *((b*p) + c)))) / ((a*a) + (b*b));
		cout<<y<<" "<<x<<endl;
		reflectedPoints.push_back(translateMandalaToOpenCV(make_pair(y, x)));
	}
	return reflectedPoints;
}
vector <lineEquation> drawBoard(Mat obj, int depth, Vec3b color)
{
	vector <pair <int, int>> allBoardPoints;
	vector <lineEquation> all_le;
	double stepSize = 45.0/pow(2,depth);
	double mDeg =0.0;
	vector <lineEquation> le;
	le.push_back(lineEquation(1, -1, 0));
	le.push_back(lineEquation(0, 1, 0));
	le.push_back(lineEquation(1, 0, 0));
	for(int i =0; i!=le.size(); i++)
	{
		le[i].displayVal();
	}
	while(mDeg <= 45)
	{
		double mRad = degreeToRadian(mDeg);
		int inp;
		double tan_mRad = tan(mRad);
		cout<<"tan="<<tan_mRad;
		all_le.push_back(lineEquation(1,-1.0*tan_mRad,0));
		pair <int, int> a = translateMandalaToOpenCV(make_pair(
			double(tan_mRad * int(BOARD_WIDTH/2)), BOARD_WIDTH/2));
		pair <int, int> b = translateMandalaToOpenCV(make_pair(0,0));
		vector <pair <int, int>> linePoints = getLine(a,b);	
		// for(int i=0; i<line.size(); i++)
		// {
		// 	cout<<line[i].first<<" "<<line[i].second<<endl;
		// }
		drawPoints(linePoints, obj, COLOR_BOARD);
		allBoardPoints.insert(allBoardPoints.end(),
			linePoints.begin(), linePoints.end());
		cout<<allBoardPoints.size()<<endl;
		mDeg+=stepSize;
	}
	for(int i=0; i!=le.size();i++)
	{
		vector < pair < int, int> > linePoints = 
			getReflectedLine(allBoardPoints, le[i]);
		// for(int i=0; i<linePoints.size(); i++)
		// {
		// 	cout<<linePoints[i].first<<" "<<linePoints[i].second<<endl;
		// }
		drawPoints(linePoints, obj, color);
		allBoardPoints.insert(allBoardPoints.end(),
			linePoints.begin(), linePoints.end());
	}
	return all_le;
}
double getSlope(pair < int, int> point)
{
	return double(point.first)/point.second;
}