#define UNICODE
#include <windows.h>
#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:{
        PostQuitMessage(0);
        return 0;
    }
    case WM_PAINT:{
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 9));
        EndPaint(hwnd, &ps);
    }
    case WM_SIZE:{
        // Handle window resizing
        RECT rc;
        GetClientRect(hwnd, &rc);
        InvalidateRect(hwnd, &rc, TRUE);
        return 0;
    }
    case WM_CREATE:{
        // Handle window creation
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    }
}
    return DefWindowProc(hwnd, uMsg, wParam, lParam);

}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Learn to Program Windows",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}