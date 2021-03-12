#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <gdiplus.h>
using namespace Gdiplus;

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

    /* Initialize GDI+ */
    GdiplusStartupInput gdiplusstartupinput;
    ULONG_PTR gdiplustoken;
    GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);

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
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+1;

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

    /* End GDI+ */
    GdiplusShutdown(gdiplustoken);

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

void repaint_square(HWND hwnd,LPRECT pmyrect,PAINTSTRUCT ps,HBRUSH the_brush);

/*  This function is called by the Windows function DispatchMessage()  */
HDC hdc; // Handle to Device Context
PAINTSTRUCT ps; // Paint Data
static RECT myrect;
LPRECT prect;
POINT mypt;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)                  /* handle the messages */
    {

    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;

    case WM_CLOSE:
//        if (MessageBox(hwnd,_T("REALLY QUIT?"),_T("DFQ IS THAT"),MB_OKCANCEL) == IDOK)
//        {
        DestroyWindow(hwnd);
//        }
//        else
//        {
        return 0;
//        }

//        case WM_LBUTTONUP:
//            std::cout << "Up clicked !" << std::endl;
//            SetRect(&myrect,0,0,100,100);


    case WM_LBUTTONDOWN:
//        std::cout << "WM_LBUTTONDOWN" << std::endl;

        mypt.x = (LONG) LOWORD(lParam);
        mypt.y = (LONG) HIWORD(lParam);

        if (PtInRect(&myrect,mypt))
        {
            std::cout << "In RECT !" << std::endl;

            hdc = GetDC(hwnd);
            static RECT mynewrect;
            HBRUSH my_red_brush;
            my_red_brush = CreateSolidBrush(RGB(255,0,0));
            SetRect(&mynewrect,150,150,200,200);
            FillRect(hdc,&mynewrect,my_red_brush);
            DeleteObject(my_red_brush);
            ReleaseDC(hwnd,hdc);

        }
        else
        {
            std::cout << "NOT in RECT :( " << std::endl;
        }

        return 0;

    case WM_PAINT:

        HDC hdc;
        HBRUSH my_green_brush;
        my_green_brush = CreateSolidBrush(RGB(0,255,0));
        hdc = BeginPaint(hwnd,&ps);
        SetRect(&myrect,0,0,150,150);
        SelectObject(hdc,my_green_brush);
        FillRect(hdc,&myrect,my_green_brush);
        DeleteObject(my_green_brush);
        EndPaint(hwnd,&ps);
        return 0;

    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

void repaint_square(HWND hwnd,LPRECT pmyrect,PAINTSTRUCT ps,HBRUSH the_brush)
{


//    hdc = GetDC(hwnd);
//    Rectangle(hdc,pmyrect->left,pmyrect->top,pmyrect->right,pmyrect->bottom);

//    Rectangle(hdc,pmyrect->left,pmyrect->top,pmyrect->right,pmyrect->bottom);
//    if(test==0) {

//    } else {
//        SetRect(pmyrect,150,150,150,200);
//    }

//    ReleaseDC(hwnd,hdc);



}
