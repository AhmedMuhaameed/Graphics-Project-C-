#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#include "Utilities.h"
#include "Menu.h"
using namespace std;


int static pointsArray [500][2];
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}
/*  This function is called by the Windows function DispatchMessage()  */
void DrawShape(HDC hd,int xs,int ys, int xe,int ye)
{
    LineDDA(hd,xs,ys,xs,ye,COLORREF(RGB(255,0,0)));
    LineDDA(hd,xs,ys,xe,ys,COLORREF(RGB(255,0,0)));
    LineDDA(hd,xe,ys,xe,ye,COLORREF(RGB(255,0,0)));
    LineDDA(hd,xs,ye,xe,ye,COLORREF(RGB(255,0,0)));
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    hdc = GetDC(hwnd);
    static int wmID;
    //static int ch =0;
    //static int points = 0;
    int x, y;
    //static vector <point> Points;
    static int ch =0;
    static int points = 0;
    static vector <point> Points;
    /* handle the messages */
    switch (message)
    {
    case WM_LBUTTONDBLCLK:
        x = (LOWORD(lParam));
        y = (HIWORD(lParam));
        SetPixel(hdc, x, y,COLORREF(RGB(255,0,0)));
        Points.push_back(point(x, y));
        pointsArray[points][0] = x ;
        pointsArray[points][1] = y ;
        points++;
        cout<<points<<" th point is " << x<<"  "<<y<<endl;
        cout<<"Array size : " << Points.size()<<endl;
        if (points >= 2 && ch>=1 && ch<=6)
        {
            ///Lines
            if(ch ==1 )
                LineDDA(hdc,Points[0].x,Points[0].y,Points[1].x,Points[1].y,COLORREF(RGB(255,0,0)));
            else if(ch == 2)
                drawlineparametric(hdc,Points[0].x,Points[0].y,Points[1].x,Points[1].y,COLORREF(RGB(255,0,0)));
            else if(ch == 3 )
                integerdda(hdc,Points[0].x,Points[0].y,Points[1].x,Points[1].y,COLORREF(RGB(255,0,0)));
            ///ellipse
            else if(ch == 4 )
            {
                int xc = Points[0].x, yc = Points[0].y, a = Points[1].x, b = Points[1].y;
                int x = xc, y = yc ;
                midptellipse(hdc, a,  b, xc,  yc,COLORREF(RGB(255,0,0)));
            }
            else if(ch == 5 )
            {
                int xc = Points[0].x, yc = Points[0].y, a = Points[1].x, b = Points[1].y;
                int x = a - xc, y = b - yc ;
                drawellipseparametric(hdc, a,  b, xc,  yc,COLORREF(RGB(255,0,0)));
            }
            else if(ch == 6 )
            {
                int xc = Points[0].x, yc = Points[0].y, a = Points[1].x, b = Points[1].y;
                int x = a - xc, y = b - yc ;
                drawellipsepolar(hdc, a,  b, xc,  yc,COLORREF(RGB(255,0,0)));
            }


            points = 0 ;
            Points.clear();

        }
        ///Curves
        else if (points==4 && (ch==7 || ch==8||ch==10))
        {
            if(ch==7)
            {
                for(int i=0; i<points-1; i++ )
                {
                    CohenSuth(hdc, Points[i].x,Points[i].y,Points[i+1].x,Points[i+1].y, 1, 200, 200, 1, RGB(0,0,0));
                }
                CohenSuth(hdc, Points[0].x,Points[0].y,Points[points-1].x,Points[points-1].y, 1, 200, 200, 1, RGB(0,0,0));
            }
            if (ch == 8 )
                drawCubicBezier2(hdc,Points[0].x,Points[0].y,Points[1].x,Points[1].y,Points[2].x,Points[2].y,Points[3].x,Points[3].y,RGB(0,0,0));
            if(ch == 10)
            {
                drawCubicHermite(hdc,Points[0].x,Points[0].y,Points[1].x,Points[1].y,Points[2].x,Points[2].y,Points[3].x,Points[3].y,RGB(0,0,0));

            }
            points = 0 ;
            Points.clear();
        }
        else if(ch == 9 && points==6)
        {
            drawSplines(hdc,Points,6,0.5,RGB(0,0,0));
            points = 0 ;
            Points.clear();
        }
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case LINE_DDA:
            ch = 1 ;
            break;
        case LINE_PARAMETRIC:
            ch =2;
            break;
        case LINE_MIDPOINT:
            ch =3;
            break;
        case Ellpise_MIDPOINT:
            ch= 4;
            break;
        case Ellpise_Cartesian:
            ch= 5;
            break;
        case Ellpise_POLAR:
            ch= 6;
            break;
        case POLYGON_CLIPPING:
            ch=7;
            DrawShape(hdc,1,1,200,200);
            break;
        case IDM_CURVE_BEZIER:
            ch=8;
            break;
        case IDM_CURVE_SPLINES:
            ch=9;
            break;
        case IDM_CURVE_HERMITE:
            ch=10;
            break;
        case IDM_FILE_EXIT:
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            DestroyWindow(hwnd);
            break;
        case IDM_FILE_LOAD:
            load(hwnd,hdc);
            break;
        case IDM_FILE_SAVE:
            save(hwnd);
            break;
        case IDM_FILE_CLEAR:
            background = defaultColor;
            ChangeBackground(hdc,background, hwnd);
            break;

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
        }
        break;
    ///Creating menu bar and Set icons
    case WM_CREATE:
        AddMenus(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
