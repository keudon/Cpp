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

    /* End GDI+ */
    GdiplusShutdown(gdiplustoken);

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    PAINTSTRUCT ps; // Paint Data
    HDC hdc; // Handle to Device Context

    switch (message)                  /* handle the messages */
    {

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;

        case WM_CLOSE:
            if (MessageBox(hwnd,_T("REALLY QUIT?"),_T("DFQ IS THAT"),MB_OKCANCEL) == IDOK)
            {
                DestroyWindow(hwnd);
            } else {
                return 0;
            }

        case WM_LBUTTONDOWN:
            std::cout << "LEFT CLICKED !" << std::endl;

        case WM_PAINT:
            std::cout << "Paint requested" << std::endl;

            hdc = BeginPaint(hwnd,&ps);

//            HPEN hpenOld;
//            hpenOld = static_cast<HPEN>(SelectObject(hdc, GetStockObject(DC_PEN)));
//            HBRUSH hbrushOld;
//            hbrushOld = static_cast<HBRUSH>(SelectObject(hdc, GetStockObject(NULL_BRUSH)));

               // Calculate the dimensions of the 4 equal rectangles.
//            RECT rcWindow;
//            GetClientRect(hwnd, &rcWindow);

//            RECT rc1, rc2, rc3, rc4;
//            rc1 = rc2 = rc3 = rc4 = rcWindow;

//            rc1.right  -= (rcWindow.right - rcWindow.left) / 2;
//            rc1.bottom -= (rcWindow.bottom - rcWindow.top) / 2;

//            rc2.left   = rc1.right;
//            rc2.bottom = rc1.bottom;

//            rc3.top   = rc1.bottom;
//            rc3.right = rc1.right;

//            rc4.top  = rc1.bottom;
//            rc4.left = rc1.right;

            // Optionally, deflate each of the rectangles by an arbitrary amount so that
            // they don't butt up right next to each other and we can distinguish them.
//            InflateRect(&rc1, -5, -5);
//            InflateRect(&rc2, -5, -5);
//            InflateRect(&rc3, -5, -5);
//            InflateRect(&rc4, -5, -5);

            SetDCPenColor(hdc, RGB(255, 0, 0));    // red

            Rectangle(hdc, 0, 0, 100, 100);

//            std::cout << "left = " << rc1.left << std::endl;
//            std::cout << "top = " << rc1.top << std::endl;
//            std::cout << "right = " << rc1.right << std::endl;
//            std::cout << "bottom = " << rc1.bottom << std::endl;

//            FillRect(hdc,&ps.rcPaint,(HBRUSH) (COLOR_WINDOW+2));

//            SolidBrush redBrush(Color::Red);
//            Pen greenPen(Color::Green, 2.0);
//            g.FillRectangle(&redBrush, 20, 20, 100, 100);
//            g.DrawEllipse(&greenPen, 30, 30, 80, 80);
            EndPaint(hwnd, &ps);
            return 0;

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
