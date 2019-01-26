using namespace cv;
using namespace std;
#define ROW 720
#define COLUMN 1280
int initializeMatObject(int r1, int r2, int c1, int c2, Mat &obj, 
	Vec3b color)
{
	/*
		"Initializes part of mat object with some color value"
	*/
	for(int i=r1;i<r2;i++)	
	{
		for(int j=c1;j<c2;j++)
		{
			obj.at<Vec3b>(i,j)=color;
		}
	}
	return 1;
}
void invertImage(Mat obj)
{
	int i,j,temp;
	for(i=0;i<obj.rows;i++)
	{
		unsigned char *p=obj.ptr(i);
		for(j=0;j<obj.cols/2;j++)
		{
			temp=*(p+(3*j));
			*(p+(3*j))=*(p+(3*(obj.cols-j-1)));
			*(p+(3*(obj.cols-j-1)))=temp;
			temp=*(p+(3*j)+1);
			*(p+(3*j)+1)=*(p+(3*(obj.cols-j-1))+1);
			*(p+(3*(obj.cols-j-1))+1)=temp;
			temp=*(p+(3*j)+2);
			*(p+(3*j)+2)=*(p+(3*(obj.cols-j-1))+2);
			*(p+(3*(obj.cols-j-1))+2)=temp;
		}
	}
}
vector < pair <int,int> > getLine(pair <int,int> a,pair <int,int> b)
{
	/*
	Takes two points and returns set of points that lie on the line between them"
	*/
	vector < pair <int,int> > points;
	int dx=abs(b.first-a.first);
	int dy=abs(b.second-a.second);
	//direction :-  1 for increment, 0 for decrement
	int dirx=(b.first-a.first>=0)?1:-1;
	int diry=(b.second-a.second>=0)?1:-1;
	if(dx>=dy)
	{
		float slope=(float)(dx)/(float)(dy);
		int x=0,y;
		while(x!=dx)
		{
			x+=1;
			y=floor((float)x/slope);
			points.push_back(make_pair(a.first+(dirx*x),a.second+(diry*y)));
		}
	}
	else
	{
		float slope=(float)(dy)/(float)(dx);
		int y=0,x;
		while(y!=dy)
		{
			y+=1;
			x=floor((float)y/slope);
			points.push_back(make_pair(a.first+(dirx*x),a.second+(diry*y)));
		}
	}
	return points;
}
void drawPoints(vector < pair < int,int>> points, Mat obj, Vec3b color)
{
	/*
		Takes points as input and colours those points.
	*/
	for(vector <pair <int,int> > :: iterator it=points.begin();it!=points.end();it++)
	{
		obj.at<Vec3b>((*it).first,(*it).second)=color;
		//*(obj.ptr((*it).first)+((*it).second))=250;
	}
}