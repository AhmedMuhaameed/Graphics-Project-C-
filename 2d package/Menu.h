#include <iostream>
#include <windows.h>
#include <tchar.h>
#include "Headers.h"
using namespace std;

HMENU hMenu;
static void AddMenus(HWND hwnd)
{
    hMenu = CreatePopupMenu();
    HMENU hMenubar = CreateMenu();
    HMENU hSubMenu = CreatePopupMenu();

    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&File");
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_LOAD, L"&Load");
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_SAVE, L"&Save");
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_CLEAR, L"&Clear");
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_EXIT, L"&Exit");
    hMenu = CreatePopupMenu();
    hSubMenu = CreatePopupMenu();

    /*------. Draw -----*/
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&Draw");
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR) hSubMenu, L"&Ellipse");
    AppendMenuW(hSubMenu, MF_STRING, Ellpise_MIDPOINT, L"MidPoint");
    AppendMenuW(hSubMenu, MF_STRING, Ellpise_Cartesian, L"Cartesian");
    AppendMenuW(hSubMenu, MF_STRING, Ellpise_POLAR, L"Polar");
    hSubMenu = CreatePopupMenu();
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR) hSubMenu, L"&Line");
    AppendMenuW(hSubMenu, MF_STRING, LINE_DDA, L"DDA");
    AppendMenuW(hSubMenu, MF_STRING, LINE_MIDPOINT, L"MidPoint");
    AppendMenuW(hSubMenu, MF_STRING, LINE_PARAMETRIC, L"Parametric");
    hSubMenu = CreatePopupMenu();
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR) hSubMenu, L"&Curve");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CURVE_HERMITE, L"Hermite");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CURVE_BEZIER, L"Bezier");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CURVE_SPLINES, L"Splines");
    hSubMenu = CreatePopupMenu();

    hSubMenu = CreatePopupMenu();
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR) hSubMenu, L"&Clipping");
    AppendMenuW(hSubMenu, MF_STRING, POLYGON_CLIPPING, L"Polygon Clipping");
    hSubMenu = CreatePopupMenu();
    SetMenu(hwnd, hMenubar);
}
COLORREF static defaultColor = RGB(255, 255, 255) ;
COLORREF static background = RGB(255, 255, 255) ;
bool HDCToFile(const char* FilePath, HDC Context, RECT Area, uint16_t BitsPerPixel = 24)
{
    uint32_t Width = Area.right - Area.left;
    uint32_t Height = Area.bottom - Area.top;
    BITMAPINFO Info;
    BITMAPFILEHEADER Header;
    memset(&Info, 0, sizeof(Info));
    memset(&Header, 0, sizeof(Header));
    Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    Info.bmiHeader.biWidth = Width;
    Info.bmiHeader.biHeight = Height;
    Info.bmiHeader.biPlanes = 1;
    Info.bmiHeader.biBitCount = BitsPerPixel;
    Info.bmiHeader.biCompression = BI_RGB;
    Info.bmiHeader.biSizeImage = Width * Height * (BitsPerPixel > 24 ? 4 : 3);
    Header.bfType = 0x4D42;
    Header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    char* Pixels = NULL;
    HDC MemDC = CreateCompatibleDC(Context);
    HBITMAP Section = CreateDIBSection(Context, &Info, DIB_RGB_COLORS, (void**)&Pixels, 0, 0);
    DeleteObject(SelectObject(MemDC, Section));
    BitBlt(MemDC, 0, 0, Width, Height, Context, Area.left, Area.top, SRCCOPY);
    DeleteDC(MemDC);
    std::fstream hFile(FilePath, std::ios::out | std::ios::binary);
    if (hFile.is_open())
    {
        hFile.write((char*)&Header, sizeof(Header));
        hFile.write((char*)&Info.bmiHeader, sizeof(Info.bmiHeader));
        hFile.write(Pixels, (((BitsPerPixel * Width + 31) & ~31) / 8) * Height);
        hFile.close();
        DeleteObject(Section);
        return true;
    }
    DeleteObject(Section);
    return false;
}
void ChangeBackground(HDC hdc,COLORREF backgroundColor,HWND hwnd )
{
    int windowWidth ;
    int windowHeight;
    RECT rect;
    if(GetWindowRect(hwnd, &rect))
    {
        windowWidth  = rect.right - rect.left;
        windowHeight = rect.bottom - rect.top;
    }
    RECT rect1 = {0, 0, windowWidth, windowHeight};
    HBRUSH brush = CreateSolidBrush(backgroundColor);
    FillRect(hdc, &rect1, brush);
    defaultColor = backgroundColor;
}
void load(HWND hWnd, HDC &hdc)
{
    string fileName = "picture.bmp";
    if (fileName == "")
        return ;
    HBITMAP hBitmap;
    hBitmap = (HBITMAP)::LoadImage(NULL, fileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HDC hLocalDC;
    hLocalDC = CreateCompatibleDC(hdc);
    BITMAP qBitmap;
    int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(hBitmap), sizeof(BITMAP),reinterpret_cast<LPVOID>(&qBitmap));
    HBITMAP hOldBmp = (HBITMAP)SelectObject(hLocalDC, hBitmap);
    BOOL qRetBlit = BitBlt(hdc, 0, 0, qBitmap.bmWidth, qBitmap.bmHeight,hLocalDC, 0, 0, SRCCOPY);
    SelectObject (hLocalDC, hOldBmp);
    DeleteDC(hLocalDC);
    DeleteObject(hBitmap);
}
void save(HWND &hWnd)
{
    HDC hdc = GetDC(hWnd);
    string fileName = "picture.bmp";
    if (fileName == "")
        return ;
    int windowWidth ;
    int windowHeight;
    RECT rect;
    if(GetWindowRect(hWnd, &rect))
    {
        windowWidth = rect.right - rect.left;
        windowHeight = rect.bottom - rect.top;
    }
    RECT rect1 = {0, 0, windowWidth, windowHeight};
    HDCToFile(fileName.c_str(),hdc,rect1);
}

