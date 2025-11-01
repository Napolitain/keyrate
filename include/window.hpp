//
// Created by Maxime Boucher on 14/06/2025.
//
#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <Windows.h>

// Global window handle
extern HWND g_hWnd;

// Global instance handle
extern HINSTANCE g_hInst;

// Window procedure for the main window
LRESULT CALLBACK WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam);

#endif //WINDOW_HPP
