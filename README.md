# Graph
A simple drawing header file for cpp

## includes the follwing headers
cmath
graphics.h ##需另行安装
windows.h

## contains constants:
const double XMAX=1200, YMAX=800;

## class Pic have functions:

Pic(){}; as well as a function, having same inputs as Initialize()

void Initialize(double range_L,double range_R, double range_B, double range_T,
	double division_X = 5, double division_Y = 5,
	double Xmax = XMAX, double Ymax = YMAX,
	double MarginX = 0.1 , double MarginY = 0.1);
 **"division_X" means having 2*divX vertical lines(including frame)**

void DrawCord(char* Xtitle="x", char* Ytitle="y");
**Draw the coordiante system with titles**

void DrawPoint(double X,double Y, color_t color=BLACK, double size=1);
**Point at (x,y) with size**

void DrawEqs(double(*func)(double x,double y,double a), double range_Al,double range_Ar,int divA=20 , 
			color_t color=BLUE , double acc=0.1, double vague=10);
**Draw set of Equations, containing points fit func(x,y,a) < acc
if only few parts are kind of 'vague'
use vague(usually 2 to 20) to control local accuracy**

void DrawFunc(double(*func)(double x),color_t color=BLACK,double size=1);
**Draw function y = func(x), with color and dot size**

## color_t has color: https://xege.org/manual/api/col/intro.htm
