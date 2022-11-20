#include <Windows.h>
#include <dwmapi.h>
#include <vector>
#pragma comment(lib, "Dwmapi.lib")
const COLORREF MY_COLOR_KEY = RGB(255, 128, 0);
HWND cmdHanlde = NULL;
constexpr unsigned int timerIdWindowUpdate = 1;
constexpr unsigned int timerIdFrameColor = 2;
bool tick = false;
bool minimized = false;

#define KOMOREBIC_PATH "./komorebic state"
#define KEMOREBI(cmd) 

std::vector<int> workspace_layer; //incoude 
std::vector<HWND> g_wrapped_window_groups;
HWND kenobi_handle = NULL;

bool init();
LRESULT _loop_function(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);



INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
{
    

    init();
    cmdHanlde = FindWindow(L"ConsoleWindowClass", L"C:\\WINDOWS\\system32\\cmd.exe");

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

void window_group_info(HWND windows) {

}
bool init() {
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Kenobi";
    wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;

    wc.lpfnWndProc = _loop_function;

    RegisterClassEx(&wc);

    kenobi_handle = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_LAYERED | WS_EX_TRANSPARENT, wc.lpszClassName, L"", WS_POPUP | WS_VISIBLE | WS_DISABLED,
        0, 0, 0, 0, nullptr, nullptr, nullptr, nullptr);
    ::SetTimer(kenobi_handle, timerIdWindowUpdate, 50, NULL);
    ::SetTimer(kenobi_handle, timerIdFrameColor, 500, NULL);
    SetLayeredWindowAttributes(kenobi_handle, MY_COLOR_KEY, 255, LWA_COLORKEY);
    ShowWindow(kenobi_handle, SW_SHOW);

    return true;
}


LRESULT _loop_function(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps{};
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT rc{}; GetClientRect(hwnd, &rc);
        HPEN hPen = CreatePen(PS_SOLID, 5, tick ? RGB(255, 128, 1) : RGB(255, 201, 14));
        HBRUSH hBrush = CreateSolidBrush(MY_COLOR_KEY);
        HGDIOBJ hOldPen = SelectObject(hdc, hPen);
        HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);

        Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

        if (hOldPen)
            SelectObject(hdc, hOldPen);
        if (hOldBrush)
            SelectObject(hdc, hOldBrush);
        if (hPen)
            DeleteObject(hPen);
        if (hBrush)
            DeleteObject(hBrush);

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_TIMER:
    {
        if (wp == timerIdWindowUpdate)
        {
            WINDOWPLACEMENT windowPlacement = { sizeof(WINDOWPLACEMENT), };
            if (::GetWindowPlacement(cmdHanlde, &windowPlacement))
            {
                if (windowPlacement.showCmd == SW_SHOWMINIMIZED
                    || !IsWindowVisible(cmdHanlde))
                {
                    ShowWindow(hwnd, SW_HIDE);
                    minimized = true;
                }
                else
                {
                    RECT rect = {};
                    DwmGetWindowAttribute(cmdHanlde, DWMWA_EXTENDED_FRAME_BOUNDS, &rect, sizeof(rect));
                    MONITORINFO monInfo;
                    monInfo.cbSize = sizeof(MONITORINFO);
                    GetMonitorInfoW(MonitorFromWindow(cmdHanlde, MONITOR_DEFAULTTONEAREST), &monInfo);
                    if (cmdHanlde != NULL && ::IsZoomed(cmdHanlde))
                    {
                        rect.left = monInfo.rcWork.left;
                        rect.top = monInfo.rcWork.top;
                        rect.bottom = monInfo.rcWork.bottom > rect.bottom ? rect.bottom : monInfo.rcWork.bottom;
                        rect.right = monInfo.rcWork.right > rect.right ? rect.right : monInfo.rcWork.right;
                    }
                    if (minimized)
                    {
                        ::SetWindowPos(hwnd, cmdHanlde, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                        minimized = false;
                    }
                    else
                    {
                        ::SetWindowPos(cmdHanlde, hwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
                        ::SetWindowPos(hwnd, 0, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
                            SWP_SHOWWINDOW);
                    }
                }
            }
        }
        else if (wp == timerIdFrameColor)
        {
            tick = !tick;
            ::RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hwnd, msg, wp, lp);
    }

    return 0;
}
