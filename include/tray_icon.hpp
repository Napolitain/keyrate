//
// Created by Maxime Boucher on 14/06/2025.
//
#ifndef TRAY_ICON_HPP
#define TRAY_ICON_HPP
#include <Windows.h>
#include <shellapi.h>

constexpr int ID_TRAY_APP_ICON = 1001;
constexpr int ID_TRAY_EXIT = 1002;
constexpr int ID_TRAY_TOGGLE = 1003;
constexpr int WM_TRAYICON = (WM_USER + 1);

// Add the application icon to the system tray
void AddTrayIcon(HWND hWnd);

// Remove the tray icon
void RemoveTrayIcon();

// Show the context menu for the tray icon
void ShowTrayMenu(HWND hWnd);

#endif //TRAY_ICON_HPP
