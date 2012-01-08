// Lab.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Lab.h"

using namespace std;
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

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
	LoadString(hInstance, IDC_LAB, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LAB);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

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
		
		hdc = BeginPaint(hWnd, &ps);
		int g,h,i,j,o;
		int tab[10][10];
		int xm,ym;
		int nrkratki;
		nrkratki=1;
		int llx,lly;
		for (g=0; g<=9; g++){
		for (h=0; h<=9; h++)
		tab[g][h]=0;
		}
		g=0;
		h=0;
		
		// TODO: 
		//rysowanie kratek
		MoveToEx(hdc, 250, 10, NULL);
		LineTo(hdc, 1050, 10);
		LineTo(hdc, 1050, 810);
		LineTo(hdc, 250, 810);
		LineTo(hdc, 250, 10);
		for(i=1;i<10;i++){
		MoveToEx(hdc, 250+(i*80), 10, NULL);
		LineTo(hdc, 250+(i*80), 810);
		}
		MoveToEx(hdc, 250, 10, NULL);
		for(j=1;j<10;j++){
		MoveToEx(hdc, 250, 10+(j*80), NULL);
		LineTo(hdc, 1050, 10+(j*80));
		}

		//losowa generacja
		int x,y;
		x=250;
		y=10;
		for(int u=0;u<10;u++)
		{
		
		
		for(int l=1;l<=10;l++)
		{
			MoveToEx(hdc, x, -70+(l*80), NULL);
			int z=rand()%3;
			if(z==1){
				if(g==0 && h==0)continue;
						LineTo(hdc, x+80, y+80);
						MoveToEx(hdc, x+80, y, NULL);
						LineTo(hdc, x, y+80);
						MoveToEx(hdc, x, y, NULL);
						tab[g][h]=1;
						
		
					}
			
			h++;
			y=y+80;
		}
		h=0;
		y=10;
		x=x+80;
		g++;

		}
		//ludzik
		llx=280;
		lly=30;
		//glowa

		MoveToEx(hdc, llx, lly, NULL);
		LineTo(hdc, llx+20, lly);
		LineTo(hdc, llx+20, lly+20);
		LineTo(hdc, llx, lly+20);
		LineTo(hdc, llx, lly);
		//rece
		MoveToEx(hdc, llx+10, lly+20, NULL);
		LineTo(hdc, llx+10, lly+40);
		LineTo(hdc, llx+20, lly+55);
		MoveToEx(hdc, llx, lly+30, NULL);
		LineTo(hdc, llx+20,lly+30);
		//nogi
		MoveToEx(hdc, llx+10, lly+40, NULL);
		LineTo(hdc, llx, lly+55);
		//oczy
		MoveToEx(hdc, llx+5, lly+7, NULL);
		LineTo(hdc, llx+7, lly+7);
		MoveToEx(hdc, llx+15, lly+7, NULL);
		LineTo(hdc, llx+17, lly+7);


	
	case WM_LBUTTONDOWN:
	{
	
    xm=LOWORD( lParam );
	ym=HIWORD( lParam );
	if(xm==0)xm=280;
	if(ym==0)ym=30;
	//kratki 1-10
	if(250<=xm<330 && 10<=ym<90)nrkratki=1;
	if(330<=xm<410 && 10<=ym<90)nrkratki=2;
	if(410<=xm<490 && 10<=ym<90)nrkratki=3;
	if(490<=xm<570 && 10<=ym<90)nrkratki=4;
	if(570<=xm<650 && 10<=ym<90)nrkratki=5;
	if(650<=xm<730 && 10<=ym<90)nrkratki=6;
	if(730<=xm<810 && 10<=ym<90)nrkratki=7;
	if(810<=xm<890 && 10<=ym<90)nrkratki=8;
	if(890<=xm<970 && 10<=ym<90)nrkratki=9;
	if(970<=xm<1050 && 10<=ym<90)nrkratki=10;
	//kartki 11-20
	if(250<=xm<330 && 90<=ym<170)nrkratki=11;
	if(330<=xm<410 && 90<=ym<170)nrkratki=12;
	if(410<=xm<490 && 90<=ym<170)nrkratki=13;
	if(490<=xm<570 && 90<=ym<170)nrkratki=14;
	if(570<=xm<650 && 90<=ym<170)nrkratki=15;
	if(650<=xm<730 && 90<=ym<170)nrkratki=16;
	if(730<=xm<810 && 90<=ym<170)nrkratki=17;
	if(810<=xm<890 && 90<=ym<170)nrkratki=18;
	if(890<=xm<970 && 90<=ym<170)nrkratki=19;
	if(970<=xm<1050 && 90<=ym<170)nrkratki=20;
	//kratki 21-30
	if(250<=xm<330 && 170<=ym<250)nrkratki=21;
	if(330<=xm<410 && 170<=ym<250)nrkratki=22;
	if(410<=xm<490 && 170<=ym<250)nrkratki=23;
	if(490<=xm<570 && 170<=ym<250)nrkratki=24;
	if(570<=xm<650 && 170<=ym<250)nrkratki=25;
	if(650<=xm<730 && 170<=ym<250)nrkratki=26;
	if(730<=xm<810 && 170<=ym<250)nrkratki=27;
	if(810<=xm<890 && 170<=ym<250)nrkratki=28;
	if(890<=xm<970 && 170<=ym<250)nrkratki=29;
	if(970<=xm<1050 && 170<=ym<250)nrkratki=30;
	//kratki 31-40
	if(250<=xm<330 && 250<=ym<330)nrkratki=31;
	if(330<=xm<410 && 250<=ym<330)nrkratki=32;
	if(410<=xm<490 && 250<=ym<330)nrkratki=33;
	if(490<=xm<570 && 250<=ym<330)nrkratki=34;
	if(570<=xm<650 && 250<=ym<330)nrkratki=35;
	if(650<=xm<730 && 250<=ym<330)nrkratki=36;
	if(730<=xm<810 && 250<=ym<330)nrkratki=37;
	if(810<=xm<890 && 250<=ym<330)nrkratki=38;
	if(890<=xm<970 && 250<=ym<330)nrkratki=39;
	if(970<=xm<1050 && 250<=ym<330)nrkratki=40;
	//kratki 41-50
	if(250<=xm<330 && 330<=ym<410)nrkratki=41;
	if(330<=xm<410 && 330<=ym<410)nrkratki=42;
	if(410<=xm<490 && 330<=ym<410)nrkratki=43;
	if(490<=xm<570 && 330<=ym<410)nrkratki=44;
	if(570<=xm<650 && 330<=ym<410)nrkratki=45;
	if(650<=xm<730 && 330<=ym<410)nrkratki=46;
	if(730<=xm<810 && 330<=ym<410)nrkratki=47;
	if(810<=xm<890 && 330<=ym<410)nrkratki=48;
	if(890<=xm<970 && 330<=ym<410)nrkratki=49;
	if(970<=xm<1050 && 330<=ym<410)nrkratki=50;
	//kratki 51-60
	if(250<=xm<330 && 410<=ym<490)nrkratki=51;
	if(330<=xm<410 && 410<=ym<490)nrkratki=52;
	if(410<=xm<490 && 410<=ym<490)nrkratki=53;
	if(490<=xm<570 && 410<=ym<490)nrkratki=54;
	if(570<=xm<650 && 410<=ym<490)nrkratki=55;
	if(650<=xm<730 && 410<=ym<490)nrkratki=56;
	if(730<=xm<810 && 410<=ym<490)nrkratki=57;
	if(810<=xm<890 && 410<=ym<490)nrkratki=58;
	if(890<=xm<970 && 410<=ym<490)nrkratki=59;
	if(970<=xm<1050 && 410<=ym<490)nrkratki=60;
	//kratki 61-70
	if(250<=xm<330 && 490<=ym<570)nrkratki=61;
	if(330<=xm<410 && 490<=ym<570)nrkratki=62;
	if(410<=xm<490 && 490<=ym<570)nrkratki=63;
	if(490<=xm<570 && 490<=ym<570)nrkratki=64;
	if(570<=xm<650 && 490<=ym<570)nrkratki=65;
	if(650<=xm<730 && 490<=ym<570)nrkratki=66;
	if(730<=xm<810 && 490<=ym<570)nrkratki=67;
	if(810<=xm<890 && 490<=ym<570)nrkratki=68;
	if(890<=xm<970 && 490<=ym<570)nrkratki=69;
	if(970<=xm<1050 && 490<=ym<570)nrkratki=70;
	//kratki 71-80
	if(250<=xm<330 && 570<=ym<650)nrkratki=71;
	if(330<=xm<410 && 570<=ym<650)nrkratki=72;
	if(410<=xm<490 && 570<=ym<650)nrkratki=73;
	if(490<=xm<570 && 570<=ym<650)nrkratki=74;
	if(570<=xm<650 && 570<=ym<650)nrkratki=75;
	if(650<=xm<730 && 570<=ym<650)nrkratki=76;
	if(730<=xm<810 && 570<=ym<650)nrkratki=77;
	if(810<=xm<890 && 570<=ym<650)nrkratki=78;
	if(890<=xm<970 && 570<=ym<650)nrkratki=79;
	if(970<=xm<1050 && 570<=ym<650)nrkratki=80;
	//kratki 81-90
	if(250<=xm<330 && 650<=ym<730)nrkratki=81;
	if(330<=xm<410 && 650<=ym<730)nrkratki=82;
	if(410<=xm<490 && 650<=ym<730)nrkratki=83;
	if(490<=xm<570 && 650<=ym<730)nrkratki=84;
	if(570<=xm<650 && 650<=ym<730)nrkratki=85;
	if(650<=xm<730 && 650<=ym<730)nrkratki=86;
	if(730<=xm<810 && 650<=ym<730)nrkratki=87;
	if(810<=xm<890 && 650<=ym<730)nrkratki=88;
	if(890<=xm<970 && 650<=ym<730)nrkratki=89;
	if(970<=xm<1050 && 650<=ym<730)nrkratki=90;
	//kratki 91-100
	if(250<=xm<330 && 730<=ym<810)nrkratki=91;
	if(330<=xm<410 && 730<=ym<810)nrkratki=92;
	if(410<=xm<490 && 730<=ym<810)nrkratki=93;
	if(490<=xm<570 && 730<=ym<810)nrkratki=94;
	if(570<=xm<650 && 730<=ym<810)nrkratki=95;
	if(650<=xm<730 && 730<=ym<810)nrkratki=96;
	if(730<=xm<810 && 730<=ym<810)nrkratki=97;
	if(810<=xm<890 && 730<=ym<810)nrkratki=98;
	if(890<=xm<970 && 730<=ym<810)nrkratki=99;
	if(970<=xm<1050 && 730<=ym<810)nrkratki=100;

	HDC hdc = GetDC( hWnd );
	SetPixel( hdc, xm, ym, RGB( 255, 0, 0 ) );
		
		for(o=1;o<=5;o++){
		if(o==1) SetPixel( hdc, xm+5, ym, RGB( 255, 0, 0 ) );
		if(o==2) SetPixel( hdc, xm+10, ym, RGB( 255, 0, 0 ) );
		if(o==3) SetPixel( hdc, xm+15, ym, RGB( 255, 0, 0 ) );
		if(o==4) SetPixel( hdc, xm+20, ym, RGB( 255, 0, 0 ) );
		if(o==5) SetPixel( hdc, xm+25, ym, RGB( 255, 0, 0 ) );
		Sleep( 50 );
		llx=llx+((xm-llx)/5);
		
		//glowa
		MoveToEx(hdc, llx, lly, NULL);
		LineTo(hdc, llx+20, lly);
		LineTo(hdc, llx+20, lly+20);
		LineTo(hdc, llx, lly+20);
		LineTo(hdc, llx, lly);
		//rece
		MoveToEx(hdc, llx+10, lly+20, NULL);
		LineTo(hdc, llx+10, lly+40);
		LineTo(hdc, llx+20, lly+55);
		MoveToEx(hdc, llx, lly+30, NULL);
		LineTo(hdc, llx+20,lly+30);
		//nogi
		MoveToEx(hdc, llx+10, lly+40, NULL);
		LineTo(hdc, llx, lly+55);
		//oczy
		MoveToEx(hdc, llx+5, lly+7, NULL);
		LineTo(hdc, llx+7, lly+7);
		MoveToEx(hdc, llx+15, lly+7, NULL);
		LineTo(hdc, llx+17, lly+7);
	
		}

	
	ReleaseDC( hWnd, hdc );


	}
	
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
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


