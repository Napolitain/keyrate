//
// Created by Maxime Boucher on 14/06/2025.
//
#ifndef KEYRATE_HPP
#define KEYRATE_HPP
#include <Windows.h>

// Sets the keyboard repeat rate using Windows FilterKeys API
void SetKeyrate(const DWORD delay, const DWORD repeat, const bool enable);

#endif //KEYRATE_HPP
