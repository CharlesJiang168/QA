// SimpleGraphicsClass.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SimpleGraphicsClass.h"

#define MAX_LOADSTRING 100

class CGraphics;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

CGraphics* g = NULL;

class CGraphics
{
protected:
	HDC m_hdc;
	HBITMAP m_hbmp;
	HBITMAP m_holdbmp;
	HPEN m_hpen;
	HPEN m_holdpen;
	HBRUSH m_hbrush;
	HBRUSH m_holdbrush;
public:
	CGraphics(HDC hdc, int width, int height, COLORREF clrClear = RGB(255, 255, 255))
	{
		gpCreateDoubleBuffer(hdc, width, height);

		RECT rcFill = {0, 0, width, height};
		
		DrawFillRectangle(clrClear, rcFill);

		m_hpen = NULL;
		m_holdpen = NULL;
		m_hbrush = NULL;
		m_holdbrush = NULL;
	}
	CGraphics(HWND hWnd, COLORREF clrClear = RGB(255, 255, 255))
	{
		HDC hdc = ::GetDC(hWnd);
		RECT rc;
		::GetClientRect(hWnd, &rc);

		gpCreateDoubleBuffer(hdc, rc.right, rc.bottom);

		DrawFillRectangle(clrClear, rc);

		::ReleaseDC(hWnd, hdc);

		m_hpen = NULL;
		m_holdpen = NULL;
		m_hbrush = NULL;
		m_holdbrush = NULL;
	}
	~CGraphics()
	{
		gpDeleteDoubleBuffer();
	}
protected:
	void gpCreateDoubleBuffer(HDC hdc, int width, int height)
	{
		m_hdc = ::CreateCompatibleDC(hdc);
		m_hbmp = ::CreateCompatibleBitmap(hdc, width, height);
		m_holdbmp = (HBITMAP)::SelectObject(m_hdc, m_hbmp);
	}
	void gpDeleteDoubleBuffer()
	{
		if ( m_hdc )
		{
			::SelectObject(m_hdc, m_holdbmp);
			::DeleteDC(m_hdc);
			m_hdc = NULL;
		}

		if ( m_hbmp )
		{
			::DeleteObject(m_hbmp);
			m_hbmp = NULL;
		}
	}
	void gpBeginPen(COLORREF color, int width)
	{
		m_hpen = ::CreatePen(PS_SOLID, width, color);
		m_holdpen = (HPEN)::SelectObject(m_hdc, m_hpen);
	}
	void gpEndPen()
	{
		::SelectObject(m_hdc, m_holdpen);
		::DeleteObject(m_hpen);
		m_hpen = NULL;
		m_holdpen = NULL;
	}
	void gpBeginBrush(COLORREF color)
	{
		m_hbrush = ::CreateSolidBrush(color);
		m_holdbrush = (HBRUSH)::SelectObject(m_hdc, m_hbrush);
	}
	void gpBeginHollowBrush()
	{
		m_hbrush = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
		m_holdbrush = (HBRUSH)::SelectObject(m_hdc, m_hbrush);
	}
	void gpEndBrush()
	{
		::SelectObject(m_hdc, m_holdbrush);
		::DeleteObject(m_hbrush);
		m_hbrush = NULL;
		m_holdbrush = NULL;
	}
public:
	void Render(HDC hdc, int width, int height)
	{
		::BitBlt(hdc, 0, 0, width, height, m_hdc, 0, 0, SRCCOPY);
	}
	HDC GetHdc()
	{
		return m_hdc;
	}
	HGDIOBJ SelectObject(HGDIOBJ h)
	{
		return ::SelectObject(m_hdc, h);
	}
	BOOL DeleteObject(HGDIOBJ h)
	{
		return ::DeleteObject(h);
	}
	BOOL BitBlt(int x, int y, int width, int height, 
		       HDC srcHdc, int srcX, int srcY, int rop = SRCCOPY)
	{
		return ::BitBlt(m_hdc, x, y, width, height, srcHdc, srcX, srcY, rop);
	}
	BOOL StretchBlt(int xDest, int yDest, int wDest, 
				int hDest, HDC srcHdc, int xSrc, int ySrc, int wSrc, int hSrc, int rop)
	{
		return ::StretchBlt(m_hdc, xDest, yDest, wDest, hDest, srcHdc, xSrc, ySrc, xSrc, ySrc, rop);
	}
	HDC CreateCompatibleDC(HDC hdc)
	{
		return ::CreateCompatibleDC(hdc);
	}
	/* CreateCompatibleDC from this hdc
	 */
	HDC CreateCompatibleDC()
	{
		return ::CreateCompatibleDC(m_hdc);
	}
	HBITMAP CreateCompatibleBitmap(HDC hdc, int width, int height)
	{
		return ::CreateCompatibleBitmap(hdc, width, height);
	}
	/* CreateCompatibleBitmap from this hdc
	 */
	HBITMAP CreateCompatibleBitmap(int width, int height)
	{
		return ::CreateCompatibleBitmap(m_hdc, width, height);
	}
	/* Easy version of Gdi32 CreateFont
	 */
	HFONT CreateFont(char* name, int size, bool bold = false)
	{
		int hight = -MulDiv(size, GetDeviceCaps(GetDC(GetDesktopWindow()), LOGPIXELSY), 72);
		int width = FW_NORMAL;

		if ( bold )
			width = FW_BOLD;

		return ::CreateFont(hight, 0, 0, 0, width, 0, 0, 0, 1, 8, 0, 4, 2, name);
	}
	/* Resize the rendering area.
	 */
	void Resize(HWND hWnd, COLORREF clrClear = RGB(255, 255, 255))
	{
		gpDeleteDoubleBuffer();

		HDC hdc = ::GetDC(hWnd);
		RECT rc;
		::GetClientRect(hWnd, &rc);

		gpCreateDoubleBuffer(hdc, rc.right, rc.bottom);

		DrawFillRectangle(clrClear, rc);

		::ReleaseDC(hWnd, hdc);
	}
	void DrawLine(COLORREF color, int x1, int y1, int x2, int y2, int width = 1)
	{
		gpBeginPen(color, width);

		::MoveToEx(m_hdc, x1, y1, NULL);
		::LineTo(m_hdc, x2, y2);

		gpEndPen();
	}
	void DrawRectangle(COLORREF clrPen, int x1, int y1, int x2, int y2, int borderWidth = 1)
	{
		gpBeginPen(clrPen, borderWidth);
		gpBeginHollowBrush();

		::Rectangle(m_hdc, x1, y1, x2, y2);

		gpEndBrush();
		gpEndPen();
	}
	void DrawFillRectangle(COLORREF color, int x, int y, int width, int height)
	{
		RECT rc = {x, y, width, height};
		::FillRect(m_hdc, &rc, CreateSolidBrush(color));
	}
	void DrawFillRectangle(COLORREF color, RECT rc)
	{
		::FillRect(m_hdc, &rc, CreateSolidBrush(color));
	}
	void DrawEllpise(COLORREF clrPen, int x1, int y1, int x2, int y2, int borderWidth = 1)
	{
		gpBeginPen(clrPen, borderWidth);
		gpBeginHollowBrush();

		::Ellipse(m_hdc, x1, y1, x2, y2);

		gpEndBrush();
		gpEndPen();
	}
	void DrawFillEllpise(COLORREF clrPen, COLORREF clrFill, int x1, int y1, int x2, int y2, int borderWidth = 1)
	{
		gpBeginPen(clrPen, borderWidth);
		gpBeginBrush(clrFill);

		::Ellipse(m_hdc, x1, y1, x2, y2);

		gpEndBrush();
		gpEndPen();
	}
	void DrawText(char* text, COLORREF color, int x, int y, 
		                 int format = DT_SINGLELINE | DT_LEFT, HFONT font = NULL)
	{
		unsigned int len = strlen(text);

		int oldmode = ::SetBkMode(m_hdc, TRANSPARENT);

		COLORREF oldcolor = ::SetTextColor(m_hdc, color);

		HFONT oldfont = NULL;

		if ( font )
		{
			oldfont = (HFONT)::SelectObject(m_hdc, font);
		}

		SIZE size;
        ::GetTextExtentPointA(m_hdc, text, len, &size);

		RECT rect;

        rect.left = x;
        rect.top = y;
        rect.right = rect.left + size.cx;
        rect.bottom = rect.top + size.cy;

		::DrawTextA(m_hdc, text, len, &rect, format);

		if ( font &&  oldfont)
		{
			::SelectObject(m_hdc, oldfont);
		}

		::SetTextColor(m_hdc, oldcolor);

		::SetBkMode(m_hdc, oldmode);
	}
	/* Simple gradient fill drawing function. I know this not the best algorithm but this is what
	 * I every time use.
	 */
	void DrawGradientFill(COLORREF color1, COLORREF color2, int x, int y, int width, int height, bool bVertical)
	{
		int Width = width;
		int Height = height;

		int r1 = GetRValue(color1);
		int g1 = GetGValue(color1);
		int b1 = GetBValue(color1);

		int r2 = GetRValue(color2);
		int g2 = GetGValue(color2);
		int b2 = GetBValue(color2);

		COLORREF OldBkColor = GetBkColor(m_hdc);

		if (bVertical)
		{
			for(int i=0; i < Width; ++i)
			{
				int r = r1 + (i * (r2-r1) / Width);
				int g = g1 + (i * (g2-g1) / Width);
				int b = b1 + (i * (b2-b1) / Width);
				SetBkColor(m_hdc, RGB(r, g, b));
				RECT line = {i + x, y, i + 1 + x, y+Height};
				ExtTextOut(m_hdc, 0, 0, ETO_OPAQUE, &line, NULL, 0, 0);
			}
		}
		else
		{
			for(int i=0; i < Height; ++i)
			{
				int r = r1 + (i * (r2-r1) / Height);
				int g = g1 + (i * (g2-g1) / Height);
				int b = b1 + (i * (b2-b1) / Height);
				SetBkColor(m_hdc, RGB(r, g, b));
				RECT line = {x, i + y, x+Width, i + 1 + y};
				ExtTextOut(m_hdc, 0, 0, ETO_OPAQUE, &line, NULL, 0, 0);
			}
		}

		SetBkColor(m_hdc, OldBkColor);
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SIMPLEGRAPHICSCLASS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPLEGRAPHICSCLASS));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SIMPLEGRAPHICSCLASS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SIMPLEGRAPHICSCLASS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      100, 100, 600, 480, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   g = new CGraphics(hWnd);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...

			RECT rc;
			::GetClientRect(hWnd, &rc);

			g->DrawText("Hello, World!", RGB(255, 0, 0), 200, 20);

			HFONT font = g->CreateFont("Segoe UI", 14);

			g->DrawText("Hello, World!", RGB(200, 100, 0), 200, 40, DT_SINGLELINE | DT_LEFT, font);

			g->DrawText("Simple Graphics Class", RGB(0, 200, 0), 200, 330, DT_SINGLELINE | DT_LEFT, font);

			g->DeleteObject(font);

			g->DrawLine(RGB(255, 0, 0), 10, 10, 100, 100);

			g->DrawLine(RGB(255, 0, 0), 40, 5, 100, 70, 5);

			g->DrawEllpise(RGB(0, 0, 0), 140, 110, 210, 210);

			g->DrawEllpise(RGB(0, 0, 0), 30, 110, 100, 210, 5);

			g->DrawFillEllpise(RGB(0, 0, 0), RGB(0, 200, 0), 30, 230, 100, 330, 5);

			g->DrawGradientFill(RGB(0, 255, 0), RGB(0, 200, 0), 230, 80, 100, 100, false);

			g->DrawGradientFill(RGB(0, 0, 233), RGB(0, 0, 103), 230, 190, 100, 100, true);

			g->DrawFillRectangle(RGB(255, 0, 0), 400, 80, 500, 200);

			g->DrawRectangle(RGB(0, 100, 100), 400, 210, 500, 300);

			// Render what you have done!
			g->Render(hdc, rc.right, rc.bottom);

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_SIZE:
		{
			g->Resize(hWnd);
			InvalidateRect(hWnd, NULL, 1);
		}
		break;
	case WM_ERASEBKGND:
		return TRUE;
	case WM_DESTROY:
		{
			// Free Memory
			delete g;
			g = NULL;
			PostQuitMessage(0);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
