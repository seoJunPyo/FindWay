// FindWay.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

/*
스타트, 엔드 포인트 저장 -> 더블 클릭.

길찾기 시작 플래그
-> 스타트 포인트를 자료구조 단 한번 넣어야됨.
-> 더블 클릭으로 스타트 포인트 재설정시, 기존 자료구조 내용을 비우고 플래그를 false로 설정한다.
-> 시작 플래그가 설정되어 있으면, 마우스 업, 도착지 변경등이 발생하면 길을 다시 찾는다.
-> 이를 위해서는 자료구조를 리셋하고, 맵 정보에 visited와 parant의 초기화가 필요함. 장애물 정보는 건드리지 않는다.

엔터 입력 시, 길찾기 루프를 한번 씩 진행.
-> 길을 찾은 경우 더 이상 길찾기를 진행하지 않는다.
-> 진행 후 화면을 다시 그린다.

스페이스바 입력 시, 타이머를 설정해 주기마다 엔터키 이벤트가 발생하도록 함.
-> 자동 길찾기 -> 길을 찾은 경우 타이머 종료.

*/

#include "framework.h"
#include "FindWay.h"
#include "Handler.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MSG msg;
    HWND hWnd;

    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FINDWAY));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FINDWAY);
    wcex.lpszClassName = L"My Process";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&wcex);

    hWnd = CreateWindowW(L"My Process", L"Window", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, nullptr, 0, 0))
    {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        WCreate(hWnd, wParam, lParam);
        break;

    case WM_PAINT:
        WPaint(hWnd, wParam, lParam);
        break;

    case WM_DESTROY:
        WDestroy(hWnd, wParam, lParam);
        break;

    case WM_LBUTTONDOWN :
        Mouse_L_Down(hWnd, wParam, lParam);
        break;

    case WM_LBUTTONUP :
        Mouse_L_Up(hWnd, wParam, lParam);
        break;
        
    case WM_LBUTTONDBLCLK :
        Mouse_L_DC(hWnd, wParam, lParam);
        break;

    case WM_RBUTTONDBLCLK :
        Mouse_R_DC(hWnd, wParam, lParam);
        break;

    case WM_MOUSEMOVE:
        Mouse_Move(hWnd, wParam, lParam);
        break;

    case WM_MOUSEWHEEL:
        Mouse_Wheel(hWnd, wParam, lParam);
        break;

    case WM_KEYDOWN :
        switch (wParam)
        {
        case VK_SPACE :
            Key_Space(hWnd, wParam, lParam);
            break;
        default:
            break;
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}