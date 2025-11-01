//
// Created by Maxime Boucher on 14/06/2025.
//

#include "window.hpp"
#include "tray_icon.hpp"
#include "dialog.hpp"

HWND g_hWnd;
HINSTANCE g_hInst;

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
                    RemoveTrayIcon();
                    PostQuitMessage(0);
                    break;
            }
            break;

        case WM_DESTROY:
            RemoveTrayIcon();
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}
