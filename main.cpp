#define UNICODE
#define _UNICODE

#include <windows.h>
#include <shellapi.h>
#include <commctrl.h>
#include <string>
#include <sstream>
#include <cwchar>

#include "persistence.hpp"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "shell32.lib")

constexpr int ID_TRAY_APP_ICON = 1001;
constexpr int ID_TRAY_EXIT = 1002;
constexpr int ID_TRAY_TOGGLE = 1003;
constexpr int WM_TRAYICON = (WM_USER + 1);
constexpr int IDD_KEYRATE_DIALOG = 2001;

HINSTANCE g_hInst;
NOTIFYICONDATAW nid = {};
HWND g_hWnd;

void SetKeyrate(const DWORD delay, const DWORD repeat, const bool enable) {
    FILTERKEYS keys = {sizeof(FILTERKEYS)};
    keys.iDelayMSec = delay;
    keys.iRepeatMSec = repeat;
    keys.dwFlags = enable ? (FKF_FILTERKEYSON | FKF_AVAILABLE) : 0;
    SystemParametersInfoW(SPI_SETFILTERKEYS, 0, &keys, SPIF_SENDCHANGE);
}

void ShowTrayMenu(const HWND hWnd) {
    POINT pt;
    GetCursorPos(&pt);

    const HMENU hMenu = CreatePopupMenu();
    InsertMenuW(hMenu, -1, MF_BYPOSITION, ID_TRAY_TOGGLE, L"Configure Keyrate");
    InsertMenuW(hMenu, -1, MF_BYPOSITION, ID_TRAY_EXIT, L"Exit");

    SetForegroundWindow(hWnd);
    TrackPopupMenu(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, nullptr);
    DestroyMenu(hMenu);
}

INT_PTR CALLBACK DialogProc(const HWND hDlg, const UINT message, const WPARAM wParam, LPARAM lParam) {
    static HWND hEditDelay, hEditRepeat, hCheckEnable;

    switch (message) {
        case WM_INITDIALOG:
            hEditDelay = GetDlgItem(hDlg, 101);
            hEditRepeat = GetDlgItem(hDlg, 102);
            hCheckEnable = GetDlgItem(hDlg, 103);

            wchar_t buf[16];
            swprintf(buf, 16, L"%u", g_config.delay);
            SetWindowTextW(hEditDelay, buf);

            swprintf(buf, 16, L"%u", g_config.repeat);
            SetWindowTextW(hEditRepeat, buf);

            SendMessageW(hCheckEnable, BM_SETCHECK, g_config.enable ? BST_CHECKED : BST_UNCHECKED, 0);
            return TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK) {
                wchar_t delayStr[16], repeatStr[16];
                GetWindowTextW(hEditDelay, delayStr, 16);
                GetWindowTextW(hEditRepeat, repeatStr, 16);

                const DWORD delay = _wtoi(delayStr);
                const DWORD repeat = _wtoi(repeatStr);
                const bool enable = (SendMessageW(hCheckEnable, BM_GETCHECK, 0, 0) == BST_CHECKED);

                g_config.delay = delay;
                g_config.repeat = repeat;
                g_config.enable = enable;

                SetKeyrate(delay, repeat, enable);
                SaveConfig();

                EndDialog(hDlg, 0);
                return TRUE;
            } else if (LOWORD(wParam) == IDCANCEL) {
                EndDialog(hDlg, 0);
                return TRUE;
            }
            break;
    }
    return FALSE;
}

LRESULT CALLBACK WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam) {
    switch (message) {
        case WM_TRAYICON:
            if (lParam == WM_RBUTTONUP) {
                ShowTrayMenu(hWnd);
            }
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_TRAY_TOGGLE:
                    DialogBoxW(g_hInst, MAKEINTRESOURCEW(IDD_KEYRATE_DIALOG), hWnd, DialogProc);
                    break;
                case ID_TRAY_EXIT:
                    Shell_NotifyIconW(NIM_DELETE, &nid);
                    PostQuitMessage(0);
                    break;
            }
            break;

        case WM_DESTROY:
            Shell_NotifyIconW(NIM_DELETE, &nid);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}

void AddTrayIcon(const HWND hWnd) {
    nid.cbSize = sizeof(nid);
    nid.hWnd = hWnd;
    nid.uID = ID_TRAY_APP_ICON;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIconW(NULL, IDI_INFORMATION);
    wcscpy_s(nid.szTip, L"Keyrate Toggler");
    Shell_NotifyIconW(NIM_ADD, &nid);
}

int WINAPI wWinMain(const HINSTANCE hInstance, HINSTANCE, PWSTR, int) {
    g_hInst = hInstance;

    // Register class, create window ...

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

    auto *pDlg = static_cast<DLGTEMPLATE *>(GlobalAlloc(GPTR, 1024));
    ZeroMemory(pDlg, 1024);
    pDlg->style = WS_POPUP | WS_SYSMENU | WS_CAPTION;
    pDlg->dwExtendedStyle = 0;
    pDlg->cdit = 4;
    pDlg->x = 10;
    pDlg->y = 10;
    pDlg->cx = 200;
    pDlg->cy = 80;

    CreateDialogIndirectParamW(hInstance, pDlg, g_hWnd, DialogProc, 0);
    GlobalFree(pDlg);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}
