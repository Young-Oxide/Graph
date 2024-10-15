#ifndef _pictures_
#define _pictures_

#include <iostream>
#include <graphics.h>
#include <stdio.h>
#include <cmath>
#include <windows.h>
const double XMAX=1200, YMAX=800;

class Pic{
	double XM=XMAX,YM=YMAX,marginX=0.1,marginY=0.1;
	double rangeL, rangeR, rangeT, rangeB, divX=5,divY=5;
	double Ox,Oy;
public:
	Pic(){};
	Pic(double range_L,double range_R, double range_B, double range_T,
		double division_X = 5, double division_Y = 5,
		double Xmax = XMAX, double Ymax = YMAX,
		double MarginX = 0.1 , double MarginY = 0.1){
			Initialize(range_L,range_R,range_B,range_T,division_X,division_Y,XMAX,YMAX,MarginX,MarginY);
		}
	void Initialize(double range_L,double range_R, double range_B, double range_T,
		double division_X = 5, double division_Y = 5,
		double Xmax = XMAX, double Ymax = YMAX,
		double MarginX = 0.1 , double MarginY = 0.1);
	void DrawCord(char* Xtitle="x", char* Ytitle="y");
	void DrawPoint(double X,double Y, color_t color=BLACK, double size=1);
	void DrawEqs(double(*func)(double x,double y,double a), double range_Al,double range_Ar,int divA=20 , 
			color_t color=BLUE , double acc=0.1, double vague=10);
	void DrawFunc(double(*func)(double x),color_t color=BLACK,double size=1);
};

void Pic::Initialize(double range_L,double range_R, double range_B, double range_T,
		double division_X, double division_Y,
		double Xmax, double Ymax,
		double MarginX, double MarginY){
		
		setcolor(BLACK);
		setbkcolor(WHITE);
		
		XM = Xmax, YM = Ymax, marginX = MarginX, marginY = MarginY;
		rangeL = range_L, rangeR = range_R, rangeT = range_T, rangeB = range_B;
		divX = division_X, divY = division_Y;
		
		Ox = XM*(marginX * (1.0-0.5/(2*divX-1)) + (1-marginX) * (0.5/(2*divX-1))) * rangeR /(rangeR-rangeL) -  
			XM*(marginX * (0.5/(2*divX-1)) + (1-marginX) * (1.0-0.5/(2*divX-1))) * rangeL /(rangeR-rangeL);
		Oy = - YM*(marginY * (1.0-0.5/(2*divY-1)) + (1-marginY) * (0.5/(2*divY-1))) * rangeB /(rangeT - rangeB) + 
			YM*(marginY * (0.5/(2*divY-1)) + (1-marginY) * (1.0-0.5/(2*divY-1))) * rangeT /(rangeT - rangeB);
		//the ordinate of the origin
		
//		cout<<Ox<<" "<<Oy;
	
	}
void Pic::DrawCord(char* Xtitle, char* Ytitle){
		
		initgraph(XM,YM,0);
		setbkcolor(WHITE);
		//background      
	
		setcolor(BLACK);
		setlinestyle(SOLID_LINE,0,3);
		rectangle(marginX*XM,marginY*YM,(1.0-marginX)*XM,(1.0-marginY)*YM);	//the rect outside
		circle(Ox,Oy,3); //origin
	
		setcolor(BLACK);
		setfont(16,0,"Times New Roman");
		settextjustify(CENTER_TEXT,CENTER_TEXT);
		outtextxy(XM/2, (1-marginY*0.5)*YM, Xtitle);
    	outtextxy(marginX*0.3*XM, YM/2, Ytitle);
    	//the X-Y title
	
		double ord=0;//temporary variant
	
		setlinestyle(CENTER_LINE);
		
    	settextjustify(CENTER_TEXT,TOP_TEXT);
for(int k=0;k<10;k++)
		ord = rangeR;
		for(int i=0; i<2*divX-1; i++){
			if(abs(ord)<1e-3) ord=0,setlinestyle(SOLID_LINE,0,2);
			else setlinestyle(CENTER_LINE,0,1);
			line ( (marginX * (0.5/(2*divX-1))*(2*i+1) + (1-marginX) * (0.5/(2*divX-1))*(2*(2*divX-1)-2*i-1))*XM, marginY*YM,
				(marginX * (0.5/(2*divX-1))*(2*i+1) + (1-marginX) * (0.5/(2*divX-1))*(2*(2*divX-1)-2*i-1))*XM, (1-marginY)*YM);
			char str[20];
			sprintf(str, "%.2f", ord);
	    	outtextxy( ( marginX*(0.5/(2*divX-1))*(2*i+1)+(1-marginX)*(0.5/(2*divX-1))*(2*(2*divX-1)-2*i-1) )*XM,
					(1-marginY)*YM+3, str);
			ord -= (rangeR - rangeL) /2 /(divX-1);
		}
		
    	settextjustify(RIGHT_TEXT,CENTER_TEXT);
for(int k=0;k<10;k++)
		ord = rangeB;
		for(int i=0; i<2*divY-1; i++){
			if(abs(ord)<1e-3) ord=0,setlinestyle(SOLID_LINE,0,2);
			else setlinestyle(CENTER_LINE,0,1);
			line ( marginX*XM, ( marginY * (0.5/(2*divY-1))*(2*i+1) + (1-marginY) * (0.5/(2*divY-1))*(2*(2*divY-1)-2*i-1) )*YM,
				(1-marginX)*XM, ( marginY * (0.5/(2*divY-1))*(2*i+1) + (1-marginY) * (0.5/(2*divY-1))*(2*(2*divY-1)-2*i-1) )*YM );
			char str[20];
			sprintf(str, "%.2f", ord);
	    	outtextxy(marginX  *XM - 3,
				(marginY * (0.5/(2*divY-1))*(2*i+1) + (1-marginY) * (0.5/(2*divY-1))*(2*(2*divY-1)-2*i-1))*YM, str);
			ord += (rangeT-rangeB) /2 /(divY-1);
		}
	}
void Pic::DrawPoint(double X,double Y, color_t color, double size){
//		std::cout<<"("<<X<<","<<Y<<")\n";
		if( X < (1.0+0.25/(divX-1))*rangeL - rangeR*0.25/(divX-1) ||
			X > (1+0.25/(divX-1))*rangeR-rangeL*0.25/(divX-1) ||
			Y < (1.0+0.25/(divY-1))*rangeB - rangeT*0.25/(divY-1) ||
			Y > (1+0.25/(divY-1))*rangeT-rangeB*0.25/(divY-1)
		) return;
		if(size == 1)
			putpixel(Ox + 2 * (1.0 - 1.0/(2*divX-1)) * X/(rangeR-rangeL) * XM * (0.5-marginX) ,
				Oy - 2 * (1.0 - 1.0/(2*divY-1)) * Y/(rangeT-rangeB) * YM * (0.5-marginY), color);
		else{
			setcolor(color);
			setfillcolor(color);
			fillcircle(Ox + 2 * (1.0 - 1.0/(2*divX-1)) * X/(rangeR-rangeL) * XM * (0.5-marginX) ,
				Oy - 2 * (1.0 - 1.0/(2*divY-1)) * Y/(rangeT-rangeB) * YM * (0.5-marginY), size);
			setcolor(BLACK);
			setfillcolor(WHITE);
		} 
	}
void Pic::DrawEqs(double(*func)(double x,double y,double a), double range_Al,double range_Ar,int divA, 
	color_t color, double acc, double vague){
		const double alph=2;//used to control the func of div, alph larger sum more useless
		const int step = 800;//relative to the efficiency of func
		std::cout<<"Draw a set of curls( f(x,y)=a ):\n";
		double div;
		for(double a=range_Al;
				(divA != -1) && a<=range_Ar;
				(divA == 0 || range_Al == range_Ar )?(divA=-1):(a+=(range_Ar-range_Al)/divA)){
			int cnt;
			for(double x = (1.0+0.25/(divX-1))*rangeL - rangeR*0.25/(divX-1); x<(1+0.25/(divX-1))*rangeR-rangeL*0.25/(divX-1);x+=(rangeR-rangeL)/step){
				double sum=0;
				for(double y = (1.0+0.25/(divY-1))*rangeB - rangeT*0.25/(divY-1);y<(1+0.25/(divY-1))*rangeT-rangeB*0.25/(divY-1);y+=(rangeT-rangeB)/step){
					if(abs(func(x,y,a))< acc){
						sum++;
					}
				}
				cnt+=sum;
				div = 1*sum / (sum + alph*vague) - 1.0/vague * pow(2.718,-1.0*sum/alph) * sin(1.0*sum/alph);//vague larger obscure point larger
				for(double y = (1.0+0.25/(divY-1))*rangeB - rangeT*0.25/(divY-1);y<(1+0.25/(divY-1))*rangeT-rangeB*0.25/(divY-1);y+=(rangeT-rangeB)/2000){
					if(abs(func(x,y,a))< (1.0-div)*acc){
						this->DrawPoint(x,y,color);
					}
				}
//				cout<<"a="<<a<<",x="<<x<<",sum="<<sum<<",div="<<div<<"\n";
				if(sum==0) x+=2*(rangeT-rangeB)/2000;
			}
			if(cnt==0) a+=(range_Ar-range_Al)/divA;
			std::cout<<"Curl of a="<<a<<" finished.\n";
		}
		std::cout<<"Draw Fin!\n";	
	};
void Pic::DrawFunc(double(*func)(double x),color_t color,double size){
		std::cout<<"Draw single function y=f(x):\n";
		for(double x = (1.0+0.25/(divX-1))*rangeL - rangeR*0.25/(divX-1); x<(1+0.25/(divX-1))*rangeR-rangeL*0.25/(divX-1);x+=(rangeR-rangeL)/2000){
			this->DrawPoint(x,func(x),color,size);
		}
		std::cout<<"Draw fin!\n";
	}


#endif