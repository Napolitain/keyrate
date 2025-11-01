//
// Created by Maxime Boucher on 14/06/2025.
//

#include "dialog.hpp"
#include "config.hpp"
#include "keyrate.hpp"
#include <cwchar>

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
