#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <gdiplus.h>
#include "board.h"

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


HDC hdc; // Handle to Device Context
PAINTSTRUCT ps; // Paint Data
LPRECT prect;
POINT mypt;
bool is_vert,rect_is_modified;
int cell_size=10;
int taille[2]= {10,10};
//RECT my_array_of_rect[taille[0]][taille[1]];
static RECT my_array_of_rect[10][10];

//typedef int myint;
//array<myint> array_rect;
//struct mytypestruct{
//    double name;
//    int mabite;
//};
//struct mytypestruct mystruct[5];

//RECT myinitrect;
//RECT ** board_cells_rect;
//board_cells_rect = init_board<RECT>(myinitrect,10,5);

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HBRUSH my_red_brush, my_green_brush;
    my_red_brush = CreateSolidBrush(RGB(255,0,0));
    my_green_brush = CreateSolidBrush(RGB(0,255,0));
    int m,n;

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

//        std::cout << "mypt.x=" << mypt.x << std::endl;
//        std::cout << "mypt.y=" << mypt.y << std::endl;

        rect_is_modified = false;

        for (int i=0; i<taille[0]; i++)
            for (int j=0; j<taille[1]; j++)
            {

                if (!rect_is_modified && PtInRect(&my_array_of_rect[i][j],mypt))
                {
//                    std::cout << "left" << my_array_of_rect[i][j].left << std::endl;
//                    std::cout << "top" << my_array_of_rect[i][j].top << std::endl;
//                    std::cout << "right" << my_array_of_rect[i][j].right << std::endl;
//                    std::cout << "bottom" << my_array_of_rect[i][j].bottom << std::endl;
//
                    std::cout << "found" << std::endl;
//                    std::cout << "i=" << i << std::endl;
//                    std::cout << "j=" << j << std::endl;


                    hdc = GetDC(hwnd);
                    if (is_vert)
                    {
                        FillRect(hdc,&my_array_of_rect[i][j],my_red_brush);
                    }
                    else
                    {
                        FillRect(hdc,&my_array_of_rect[i][j],my_green_brush);
                    }
                    is_vert = !is_vert;
                    ReleaseDC(hwnd,hdc);
                    rect_is_modified = true;

                }
            }


        return 0;

    case WM_PAINT:

    case WM_CREATE:

        HDC hdc;
        hdc = BeginPaint(hwnd,&ps);
        SelectObject(hdc,my_green_brush);
        m=0;
        for (int i=0; i<taille[0]; i++)
        {
            n=0;
            for (int j=0; j<taille[1]; j++)
            {
                SetRect(&my_array_of_rect[i][j],n,m,n+cell_size,m+cell_size);
                n=n+cell_size+1;
                FillRect(hdc,&my_array_of_rect[i][j],my_green_brush);
            }
            m=m+cell_size+1;

        }

        EndPaint(hwnd,&ps);
        is_vert = true;
        return 0;

    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}


// Function Definition
t_user_input input()
{
    t_user_input new_input;

    std::cout << "Duration of Life ? (in number of cycles)" << std::endl;
    std::cin >> new_input.cycle_number;

    std::cout << "Initial cell(s) number ?" << std::endl;
    std::cin >> new_input.init_cell_number;



    new_input.init_cells_positions = new int* [2]; // Rows

    new_input.init_cells_positions[0] = new int [new_input.init_cell_number]; // 1st line : X
    new_input.init_cells_positions[1] = new int [new_input.init_cell_number]; // 2nd line : Y

    for (int i=0; i<new_input.init_cell_number; i++)
    {
        std::cout << "Cell " << i << " x position : " << std::endl;
        std::cin >> new_input.init_cells_positions[0][i];

        std::cout << "Cell " << i << " y position : " << std::endl;
        std::cin >> new_input.init_cells_positions[1][i];

    }

    return new_input;
}

// Main
int main_copy()
{
    Board the_board;
    // Declarations
    t_user_input user_struct;

    user_struct = input();

    the_board.create();
    the_board.initialize(user_struct);

    for(int i=0; i<user_struct.cycle_number; i++)
    {
        the_board.display();
        Sleep(500);
        the_board.update(i);

    }



    return 0;
}
