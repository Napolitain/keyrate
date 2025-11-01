#define UNICODE
#define _UNICODE

#include <windows.h>
#include <commctrl.h>

#include "config.hpp"
#include "window.hpp"
#include "tray_icon.hpp"
#include "dialog.hpp"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "shell32.lib")

int WINAPI wWinMain(const HINSTANCE hInstance, HINSTANCE, PWSTR, int) {
    g_hInst = hInstance;

    LoadConfig();

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"KeyrateTrayClass";
    RegisterClassW(&wc);

    g_hWnd = CreateWindowW(wc.lpszClassName, L"Keyrate", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, 300, 200, nullptr, nullptr, hInstance, nullptr);

    AddTrayIcon(g_hWnd);

    constexpr INITCOMMONCONTROLSEX icex = {sizeof(INITCOMMONCONTROLSEX), ICC_WIN95_CLASSES};
    InitCommonControlsEx(&icex);

    // Dialog template memory allocation
    constexpr SIZE_T DIALOG_TEMPLATE_SIZE = 1024;
    constexpr WORD DIALOG_CONTROL_COUNT = 4;
    constexpr short DIALOG_X = 10;
    constexpr short DIALOG_Y = 10;
    constexpr short DIALOG_WIDTH = 200;
    constexpr short DIALOG_HEIGHT = 80;

    auto *pDlg = static_cast<DLGTEMPLATE *>(GlobalAlloc(GPTR, DIALOG_TEMPLATE_SIZE));
    ZeroMemory(pDlg, DIALOG_TEMPLATE_SIZE);
    pDlg->style = WS_POPUP | WS_SYSMENU | WS_CAPTION;
    pDlg->dwExtendedStyle = 0;
    pDlg->cdit = DIALOG_CONTROL_COUNT;
    pDlg->x = DIALOG_X;
    pDlg->y = DIALOG_Y;
    pDlg->cx = DIALOG_WIDTH;
    pDlg->cy = DIALOG_HEIGHT;

    CreateDialogIndirectParamW(hInstance, pDlg, g_hWnd, DialogProc, 0);
    GlobalFree(pDlg);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}
