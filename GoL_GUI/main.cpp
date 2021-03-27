#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#define WM_START_BOARD (WM_USER + 0x0001)
#define WM_CONTINUE_BOARD (WM_USER + 0x0002)
#define WM_STOP_BOARD (WM_USER + 0x0003)

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

int cell_size=10;
//struct thread_struct {
//    MSG msg;
//    Board * p_to_board;
//};

//DWORD WINAPI ThreadFun1(HWND,LPVOID);

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


    Board *p_board = new Board;
    p_board->p_cell = new Cell;
    HBRUSH my_red_brush, my_green_brush;
    HDC hdc; // Handle to Device Context
    int cell_alive , total_neighboors_alive , cell_alive_next_round;


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
               p_board            /* Application Data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0) > 0)
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);

        /* Send message to WindowProcedure */
        DispatchMessage(&messages);

        if (messages.message == WM_KEYDOWN && messages.wParam == VK_SPACE)
        {
            p_board->game_on = !p_board->game_on;

            std::cout << "GAME ON !!" << std::endl;

        }

        if (p_board->game_on)
        {

            hdc = GetDC(hwnd);
            my_red_brush = CreateSolidBrush(RGB(255,0,0));
            my_green_brush = CreateSolidBrush(RGB(0,255,0));

        }

        while (p_board->game_on)
        {

            // Compute State next round
            for (int x=1; x<p_board->size_x-1; x++)
            {
                for (int y=1; y<p_board->size_y-1; y++)
                {
                    // If the cell is on the border

                    // If the cell is on a corner

                    // Else

                    // Analyze cells around
                    cell_alive = p_board->p_cell->alive[x][y];

                    total_neighboors_alive = p_board->p_cell->alive[x-1][y-1] + p_board->p_cell->alive[x-1][y] + p_board->p_cell->alive[x-1][y+1] + p_board->p_cell->alive[x+1][y-1] + p_board->p_cell->alive[x+1][y] + p_board->p_cell->alive[x+1][y+1] + p_board->p_cell->alive[x][y-1] + p_board->p_cell->alive[x][y+1];

                    ((cell_alive==1 && (total_neighboors_alive==3 || total_neighboors_alive==2)) || (cell_alive==0 && total_neighboors_alive==3)) ? cell_alive_next_round=1 : cell_alive_next_round=0;

                    p_board->p_cell->alive_next_round[x][y] = cell_alive_next_round;

                }
            }

            // Make the update

            for (int x=1; x<p_board->size_x-1; x++)
            {
                for (int y=1; y<p_board->size_y-1; y++)
                {
                    if (p_board->p_cell->alive_next_round[x][y] != p_board->p_cell->alive[x][y])
                    {
                        p_board->p_cell->alive[x][y] = p_board->p_cell->alive_next_round[x][y];

                        (p_board->p_cell->alive[x][y]) ? FillRect(hdc,&(p_board->p_cell->geometry)[x][y],my_red_brush) : FillRect(hdc,&(p_board->p_cell->geometry)[x][y],my_green_brush);

                    }
                }
            }



            Sleep(500);

            if (PeekMessage(&messages,hwnd,WM_KEYFIRST,WM_KEYLAST,PM_REMOVE) && messages.wParam == VK_SPACE && messages.message == WM_KEYDOWN)
            {
                std::cout << "Game Stopped" << std::endl;
                p_board->game_on = false;

                DeleteObject(my_red_brush);
                DeleteObject(my_green_brush);

                ReleaseDC(hwnd,hdc);

            }


        }

    }

    /* End GDI+ */
    GdiplusShutdown(gdiplustoken);

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc; // Handle to Device Context
    PAINTSTRUCT ps; // Paint Data
    HBRUSH my_red_brush, my_green_brush;
    int m,n;
    Board *p_board;
    LONG_PTR ptr;
    CREATESTRUCT *pCreate;
    POINT mypt;

    if (message == WM_CREATE)
    {
        pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        p_board = reinterpret_cast<Board*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)p_board);

        std::cout << "Board size x ?" << std::endl;
        std::cin >> p_board->size_x;
        std::cout << "Board size y ?" << std::endl;
        std::cin >> p_board->size_y;

        p_board->game_on = false;

        p_board->p_cell->geometry         = new RECT * [p_board->size_x];
        p_board->p_cell->alive            = new int * [p_board->size_x];
        p_board->p_cell->alive_next_round = new int * [p_board->size_x];

        for (int i=0;i<p_board->size_x;i++)
        {
            p_board->p_cell->geometry[i]         = new RECT [p_board->size_y];
            p_board->p_cell->alive[i]            = new int [p_board->size_y];
            p_board->p_cell->alive_next_round[i] = new int [p_board->size_x];

        }

    }
    else
    {
        ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
        p_board = reinterpret_cast<Board*>(ptr);

    }

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


    case WM_LBUTTONDOWN:

        mypt.x = (LONG) LOWORD(lParam);
        mypt.y = (LONG) HIWORD(lParam);

        for (int i=0; i<p_board->size_x; i++)
            for (int j=0; j<p_board->size_y; j++)
            {

                if (PtInRect(&(p_board->p_cell->geometry)[i][j],mypt))
                {

                    hdc = GetDC(hwnd);
                    my_green_brush = CreateSolidBrush(RGB(0,255,0));
                    my_red_brush = CreateSolidBrush(RGB(255,0,0));
                    if (p_board->p_cell->alive[i][j] == 0)
                    {
                        FillRect(hdc,&(p_board->p_cell->geometry)[i][j],my_red_brush);
                        p_board->p_cell->alive[i][j] = 1;
                    }
                    else
                    {
                        FillRect(hdc,&(p_board->p_cell->geometry)[i][j],my_green_brush);
                        p_board->p_cell->alive[i][j] = 0;
                    }
                    DeleteObject(my_green_brush);
                    DeleteObject(my_red_brush);
                    ReleaseDC(hwnd,hdc);

                }
            }


        return 0;

    case WM_PAINT:

    case WM_CREATE:

        HDC hdc;
        hdc = BeginPaint(hwnd,&ps);
        my_green_brush = CreateSolidBrush(RGB(0,255,0));
        SelectObject(hdc,my_green_brush);
        m=0;

        for (int i=0; i<p_board->size_x; i++)
        {
            n=0;
            for (int j=0; j<p_board->size_y; j++)
            {
                p_board->p_cell->alive[i][j] = 0;
                p_board->p_cell->alive_next_round[i][j] = 0;
                SetRect(&(p_board->p_cell->geometry[i][j]),n,m,n+cell_size,m+cell_size);
                n=n+cell_size+1;
                FillRect(hdc,&(p_board->p_cell->geometry[i][j]),my_green_brush);

            }
            m=m+cell_size+1;

        }
        DeleteObject(my_green_brush);
        EndPaint(hwnd,&ps);

        return 0;

    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;

}


//// Function Definition
//t_user_input input()
//{
//    t_user_input new_input;
//
//    std::cout << "Duration of Life ? (in number of cycles)" << std::endl;
//    std::cin >> new_input.cycle_number;
//
//    std::cout << "Initial cell(s) number ?" << std::endl;
//    std::cin >> new_input.init_cell_number;
//
//
//
//    new_input.init_cells_positions = new int* [2]; // Rows
//
//    new_input.init_cells_positions[0] = new int [new_input.init_cell_number]; // 1st line : X
//    new_input.init_cells_positions[1] = new int [new_input.init_cell_number]; // 2nd line : Y
//
//    for (int i=0; i<new_input.init_cell_number; i++)
//    {
//        std::cout << "Cell " << i << " x position : " << std::endl;
//        std::cin >> new_input.init_cells_positions[0][i];
//
//        std::cout << "Cell " << i << " y position : " << std::endl;
//        std::cin >> new_input.init_cells_positions[1][i];
//
//    }
//
//    return new_input;
//}
//
//// Main
//int main_copy()
//{
//    Board the_board;
//    // Declarations
//    t_user_input user_struct;
//
//    user_struct = input();
//
//    the_board.create();
//    the_board.initialize(user_struct);
//
//    for(int i=0; i<user_struct.cycle_number; i++)
//    {
//        the_board.display();
//        Sleep(500);
//        the_board.update(i);
//
//    }
//
//
//
//    return 0;
//}


//DWORD WINAPI ThreadFun1(HWND hwnd,LPVOID lpParam)
//{
//    thread_struct *p_thread_struct;
//    PeekMessage(&(p_thread_struct->msg), NULL, WM_USER, WM_USER, PM_NOREMOVE);
//    std::cout << "Entering thread" << std::endl;
//    p_thread_struct = (thread_struct*)lpParam;
//
//    while (1){
//
//        std::cout << "Ca tourne" << std::endl;
//        Sleep(1000);
//        p_thread_struct->p_to_board->p_cell->alive[1][1] = !p_thread_struct->p_to_board->p_cell->alive[1][1];
//
//    }

//        if (PeekMessage (&(p_thread_struct->msg), NULL, 0, 0, PM_REMOVE) != 0)
//        {
//
//            TranslateMessage(&(p_thread_struct->msg));
//            std::cout << "p_thread_struct->msg : " << p_thread_struct->msg.message << std::endl;
//
//        }





//    p_my_board=(p_my_board)lpParam;

//    while (p_thread_struct->p_to_board->game_on == true)
//    {
//        std::cout << "Thread Running" << std::endl;
//        Sleep(1000);
//        if (PeekMessage (&(p_thread_struct->msg), NULL, 0, 0, PM_NOREMOVE) != 0)
//        {
//            std::cout << "Thread Message Recieved !!!!!!!!!!" << std::endl;
//        } else
//        {
//            std::cout << "Nothing" << std::endl;
//        }
//
//    }

//    while (GetMessage (&(p_thread_struct->msg), NULL, 0, 0) != 0)
//    {
//        std::cout << "Thread Message Recieved" << std::endl;
//    }
//    else
//    {
//        std::cout << "Nothing" << std::endl;
//    }

//    while (p_thread_struct->p_to_board->game_on== true)
//    {
//        std::cout << "game_on " << std::endl;
//    }


//    PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE)

//}
