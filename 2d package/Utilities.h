#include <bits/stdc++.h>
#include <windows.h>
#include <tchar.h>
using namespace std;
int Round(double x)
{
    return (int)(x+0.5);
}
struct point
{
    int x, y;
    point(int xP, int yP)
    {
        x = xP;
        y = yP;
    }
};
//Line Algorithms
void drawlineparametric(HDC hdc, int x1,int y1,int x2,int y2,COLORREF c)
{
    for(double t=0; t<=1; t+=0.001)
    {
        int x=Round(x1+(t*(x2-x1)));
        int y=Round(y1+(t*(y2-y1)));
        SetPixel(hdc,x,y,c);
    }
}
//Mid Point
void integerdda(HDC hdc,int x1,int y1,int x2,int y2,COLORREF c)
{
    int dx = x2 - x1 ;
    int dy = y2 - y1 ;
    int x,y ;
    double m = (double) dy / dx;

    if (abs(dx)>abs(dy))
    {
        if (x1>x2)
        {
            swap(x1,x2);
            swap(y1,y2);
            dx*=-1;
            dy*=-1;
        }
        x=x1;
        y=y1;
        if (m>=0 && m<=1)
        {
            cout<<"first condition"<<endl;
            int d = dx  -2 * dy;
            int d1 = 2 *(dx - dy);
            int d2 = -2 * dy;
            SetPixel(hdc,x,y, c);
            while(x!=x2)
            {
                x++;
                if(d<0)
                {
                    d+=d1;
                    y++;
                }
                else
                    d+=d2;
                SetPixel(hdc,x,y, c);
            }
        }
        else if (-1 <= m&&m<=0  )
        {
            cout<<"Fourth Condition"<<endl;
            int d =-1* dx -2 * dy;;
            int d1 =-2 * dx - 2 * dy;
            int d2 = -2 * dy;
            while(x!=x2)
            {
                x++;
                if (d>0)
                {
                    y--;
                    d+=d1 ;
                }
                else
                    d+=d2;
                SetPixel(hdc,x,y, c);
            }
        }
    }
    else
    {
        if (y1>y2)
        {
            swap(x1,x2);
            swap(y1,y2);
            dx*=-1;
            dy*=-1;
        }
        x=x1;
        y=y1;
        if (m>1)
        {
            cout<<"Second Condition"<<endl;
            int d = 2*dx - dy ;
            int d1 = 2*(dx - dy );
            int d2 = 2 * dx;
            while(y!=y2)
            {
                y++;
                if (d>0)
                {
                    d+=d1;
                    x++;
                }
                else
                {
                    d+=d2;
                }
                SetPixel(hdc,x,y, c);
            }
        }
        else if (m<=-1)
        {
            cout<<"Third Condition"<<endl;
            int d = 2*dx + dy;
            int d1 =2 *(dx + dy);
            int d2 = 2 *dx;
            SetPixel(hdc,x,y, c);
            cout<<"X initial is "<<x<<endl;
            while(y!=y2)
            {
                y++;
                if (d<0)
                {
                    d+=d1;
                    x--;
                }
                else
                    d+=d2;
                SetPixel(hdc,x,y, c);
            }
        }
    }

}
//Line DDA
void LineDDA(HDC hdc, int x1, int y1,int x2, int y2, COLORREF C)
{
    int dx=x2-x1;
    int dy=y2-y1;
    if(abs(dx)>abs(dy))
    {
        if(x1>x2)
        {
            swap(x1,x2);
            swap(y1,y2);
        }
        double m=(double)dy/dx;
        int x=x1;
        double y=y1;
        SetPixel(hdc,x,y,C);
        while(x<x2)
        {
            x++;
            y+=m;
            SetPixel(hdc,x,round(y),C);
        }
    }
    else
    {
        if(y1>y2)
        {
            swap(x1,x2);
            swap(y1,y2);
        }
        double m=(double)dy/dx;
        double x=x1;
        int y=y1;
        SetPixel(hdc,x,y,C);
        while(y<y2)
        {
            y++;
            x+=(1.0/m);
            SetPixel(hdc,Round(x),y,C);
        }
    }
}

// Ellipse Algorithms
void drawellipseparametric(HDC hdc,int xc,int yc, int a,int b,COLORREF C)
{
    for (double theta=0; theta<6.28; theta+=0.001)
    {
        int x=Round(xc+a*cos(theta));
        int y=Round(yc+b*sin(theta));
        SetPixel(hdc,x,y,C);
    }
}
void draw4points(HDC hdc,int xc,int yc,int x,int y,COLORREF c)
{
    SetPixel(hdc, xc + x, yc + y, c);
    SetPixel(hdc, xc - x, yc + y, c);
    SetPixel(hdc, xc + x, yc - y, c);
    SetPixel(hdc, xc - x, yc - y, c);
}
//Polar
void drawellipsepolar(HDC hdc,int xc,int yc, int a,int b,COLORREF C)
{
    int x=a,y=0;
    double theta=0,dtheta1=1.0/(a);
    draw4points(hdc,xc,yc,x,y,C);
    while(theta<=45)
    {
        x=Round(a*cos(theta));
        y=Round(b*sin(theta));
        draw4points(hdc,xc,yc,x,y,C);
        theta+=dtheta1;
    }
}
//Mid Point

void midptellipse(HDC hdc,int a, int b,int xc, int yc,COLORREF c)
{
    double y = b, x = 0,a2 = a*a,b2 = b*b ;
    int d = b2 - a2 * b + 0.25 * a2;
    draw4points(hdc,xc,yc,Round(x),Round(y),c);
    while(b2*x<=a2*y)
    {
        x++;
        if (d>0)
        {
            y--;
            d+= b2* (2*x+3) + a2* (-2* y + 2 );
        }
        else
        {
            d+= b2* (2*x+3);
        }
        draw4points(hdc,xc,yc,Round(x),Round(y),c);
    }
    d = (x+0.5) * (x+0.5) * b2 + a2 * (y - 1)*(y-1) - a2 * b2;
    draw4points(hdc,xc,yc,Round(x),Round(y),c);
    while(y!=0)
    {
        y--;
        if (d>0)
        {
            d+=a2 * (-2*y+3);
        }
        else
        {
            x++;
            d += b2 *(2*x+2) + a2 * (-2*y+3);
        }
        draw4points(hdc,xc,yc,Round(x),Round(y),c);
    }
}
//Curves Algorithms
void multiplyMatrixVector(int mat[],int vec[],int res[],int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        res[i] = 0;
        for (int j = 0 ; j < n ; j++)
        {
            res[i]+= mat[i*n+j]*vec[j];
        }
    }
}

//void drawQuadraticCurve(HDC hdc,int x0,int y0,int x05,int y05,int x1,int y1,COLORREF rgb)
//{
//    int xArr[] = {x0,x05,x1}, yArr[] = {y0,y05,y1};
//    int mat[ ] = {1,0,0,   -3,4,-1,    2,-4,2};
//    int coArrX[3],coArrY[3];
//    multiplyMatrixVector(mat,xArr,coArrX,3);;
//    multiplyMatrixVector(mat,yArr,coArrY,3);;
//
//    int x, y;
//    for(double  t = 0 ; t <=1 ; t+=0.0001)
//    {
//        x = coArrX[0] + coArrX[1]*t + coArrX[2]*t*t;
//        y = coArrY[0] + coArrY[1]*t + coArrY[2]*t*t;
//
//        SetPixel(hdc,x,y,rgb);
//    }
//}
//void drawBezierQuadraticCurve(HDC hdc,int x0,int y0,int x05,int y05,int x1,int y1,COLORREF rgb)
//{
//    int xArr[] = {x0,x05,x1}, yArr[] = {y0,y05,y1};
//    int mat[ ] = {1,0,0,-2,2,0,1,-2,1};
//    int coArrX[3],coArrY[3];
//    multiplyMatrixVector(mat,xArr,coArrX,3);;
//    multiplyMatrixVector(mat,yArr,coArrY,3);;
//
//    int x, y;
//    for(double  t = 0 ; t <=1 ; t+=0.0001)
//    {
//        x = coArrX[0] + coArrX[1]*t + coArrX[2]*t*t;
//        y = coArrY[0] + coArrY[1]*t + coArrY[2]*t*t;
//
//        SetPixel(hdc,x,y,rgb);
//    }
//}
void drawCubicHermite(HDC hdc,int x0,int y0,int sx0,int sy0,int x1,int y1,int sx1,int sy1,COLORREF rgb)
{
    int n = 4;
    int xArr[] = {x0,sx0,x1,sx1}, yArr[] = {y0,sy0,y1,sy1};
    int mat[] = {2,1,-2,1, -3,-2,3,-1, 0,1,0,0,   1,0,0,0   };
    int coArrX[n],coArrY[n];
    multiplyMatrixVector(mat,xArr,coArrX,n);;
    multiplyMatrixVector(mat,yArr,coArrY,n);
    double x, y;
    for(double  t = 0 ; t <=1 ; t+=0.0001)
    {
        x = coArrX[3] + coArrX[2]*t + coArrX[1]*t*t+coArrX[0]*t*t*t;
        y = coArrY[3] + coArrY[2]*t + coArrY[1]*t*t+coArrY[0]*t*t*t;

        SetPixel(hdc,round(x),round(y),rgb);
    }
}

//void drawCubicBezier1(HDC hdc,int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,COLORREF rgb)
//{
//    int n = 4;
//    int xArr[] = {x0,x1,x2,x3},yArr[] = {y0,y1,y2,y3};
//    int mat[] = { -1,3,-3,1,  3,-6,3,0, -3,3,0,0,  1,0,0,0  };
//    int coArrX[n],coArrY[n];
//    ///Na5od balna w a7na bnrsm in el third point dy msh btkon bltrteb zy ally fato but btkon ta7t w b3dkda fo2
//    multiplyMatrixVector(mat,xArr,coArrX,n);;
//    multiplyMatrixVector(mat,yArr,coArrY,n);
//    double x, y;
//    for(double  t = 0 ; t <=1 ; t+=0.0001)
//    {
//        x = coArrX[3] + coArrX[2]*t + coArrX[1]*t*t+coArrX[0]*t*t*t;
//        y = coArrY[3] + coArrY[2]*t + coArrY[1]*t*t+coArrY[0]*t*t*t;
//
//        SetPixel(hdc,round(x),round(y),rgb);
//    }
//}
void drawCubicBezier2(HDC hdc,int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,COLORREF rgb)
{
    int sx0 = 3 * (x1-x0), sy0 = 3 * (y1 - y0),sx1 = 3 * (x3-x2), sy1 = 3 * (y3-y2) ;
    drawCubicHermite(hdc,x0,y0,sx0,sy0,x3,y3,sx1,sy1,rgb);
}
void drawSplines(HDC hdc ,vector<point> p,int n , double c,COLORREF rgb)
{
    double c1 = 1-c;
    int s0x =c1*(p[2].x - p[0].x) , s0y =  c1*(p[2].y - p[0].y) ,s1x,s1y;
    for (int i = 2 ; i<n-1;i++){
        s1x = c1*(p[i+1].x-p[i-1].x),s1y=c1*(p[i+1].y-p[i-1].y);

        drawCubicHermite(hdc,p[i-1].x,p[i-1].y,s0x,s0y,p[i].x,p[i].y,s1x,s1y,rgb);
        s0x = s1x ; s0y = s1y;
    }
}

// Clipping
union OutCode
{
    unsigned All:4;
    struct
    {
        unsigned left:1,top:1,right:1,bottom:1;
    };
};

OutCode GetOutCode(double x,double y,int xleft,int ytop,int xright,int ybottom)
{
    OutCode out;
    out.All=0;
    if(x<xleft)
        out.left=1;
    else if(x>xright)
        out.right=1;
    if(y>ytop)
        out.top=1;
    else if(y<ybottom)
        out.bottom=1;
    return out;
}
pair<int, int> VIntersect(double xs,double ys,double xe,double ye,int x,double &xi,double &yi)
{
    pair<int,int> p;
    xi=x;
    yi=ys+(x-xs)*(ye-ys)/(xe-xs);
    p.first=xi;
    p.second=yi;
    return p;
}
pair<int, int> HIntersect(double xs,double ys,double xe,double ye,int y,double &xi,double &yi)
{
    pair<int,int> p;
    yi=y;
    xi=xs+(y-ys)*(xe-xs)/(ye-ys);
    p.first=xi;
    p.second=yi;
    return p;
}
void CohenSuth(HDC hdc,int xs,int ys,int xe,int ye,int xleft,int ytop,int xright,int ybottom,COLORREF C)
{
    double x1=xs,y1=ys,x2=xe,y2=ye;

    OutCode out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
    OutCode out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);

    while( (out1.All || out2.All) && !(out1.All & out2.All))
    {
        pair<int, int> point;
        double xi,yi;
        if(out1.All)
        {
            if(out1.left)
                point = VIntersect(x1,y1,x2,y2,xleft, xi, yi);
            else if(out1.top)
                point = HIntersect(x1,y1,x2,y2,ytop, xi, yi);
            else if(out1.right)
                point = VIntersect(x1,y1,x2,y2,xright, xi, yi);
            else
                point = HIntersect(x1,y1,x2,y2,ybottom, xi, yi);
            x1=point.first;
            y1=point.second;
            out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
        }
        else
        {
            if(out2.left)
                point = VIntersect(x1,y1,x2,y2,xleft,xi,yi);
            else if(out2.top)
                point = HIntersect(x1,y1,x2,y2,ytop,xi,yi);
            else if(out2.right)
                point = VIntersect(x1,y1,x2,y2,xright,xi,yi);
            else
                point = HIntersect(x1,y1,x2,y2,ybottom,xi,yi);
            x2=point.first;
            y2=point.second;
            out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
        }
    }
    if(!out1.All && !out2.All)
    {
        drawlineparametric(hdc,x1,y1,x2,y2,C);
    }
}
