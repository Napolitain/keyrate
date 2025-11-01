//
// Created by Maxime Boucher on 14/06/2025.
//

#include "tray_icon.hpp"

NOTIFYICONDATAW nid = {};

void AddTrayIcon(const HWND hWnd) {
    nid.cbSize = sizeof(nid);
    nid.hWnd = hWnd;
    nid.uID = ID_TRAY_APP_ICON;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIconW(NULL, MAKEINTRESOURCEW(IDI_INFORMATION));
    wcscpy_s(nid.szTip, L"Keyrate Toggler");
    Shell_NotifyIconW(NIM_ADD, &nid);
}

void RemoveTrayIcon() {
    Shell_NotifyIconW(NIM_DELETE, &nid);
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
