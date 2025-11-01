//
// Created by Maxime Boucher on 14/06/2025.
//
#ifndef DIALOG_HPP
#define DIALOG_HPP
#include <Windows.h>

constexpr int IDD_KEYRATE_DIALOG = 2001;

// Dialog procedure for keyrate configuration dialog
INT_PTR CALLBACK DialogProc(const HWND hDlg, const UINT message, const WPARAM wParam, LPARAM lParam);

#endif //DIALOG_HPP
