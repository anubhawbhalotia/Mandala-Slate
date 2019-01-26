using namespace cv;
using namespace std;
#define ROW 720
#define COLUMN 1280
#define BOARD_ROW 9
#define BOARD_COLUMN 289
#define BOARD_HEIGHT 701
#define BOARD_WIDTH 701
#define PI 3.14159
Vec3b COLOR_BACKGROUND={255, 255, 255};
Vec3b COLOR_BOARD = {160, 160, 160};
Vec3b COLOR_BLACK = {0, 0, 0};
Vec3b COLOR_RED = {255, 0, 0};
typedef struct lineEquation
{
	int a,b,c;
	lineEquation(int a,int b,int c):
	a(a), b(b), c(c) {}
	void displayVal()
	{
		cout<<a<<" "<<b<<" "<<c<<endl;
	}
}lineEquation;
pair <int, int> translate(pair <int, int> p)
{
	/*
		convert a coordinate from mandala coordinate syatem to opencv 
		coordinate system
		param1: .first = row, .seoond = column
	*/
	return make_pair(BOARD_ROW + (p.first -BOARD_HEIGHT/2)*-1,
		p.second + BOARD_COLUMN + BOARD_WIDTH/2);
}
double degreeToRadian(double degree)
{
	return (degree/180)*PI;
}

