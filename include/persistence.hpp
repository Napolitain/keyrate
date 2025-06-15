//
// Created by Maxime Boucher on 14/06/2025.
//
#ifndef PERSISTENCE_HPP
#define PERSISTENCE_HPP
#include <Windows.h>


constexpr LPCWSTR REG_PATH = L"Software\\KeyrateToggler";
constexpr LPCWSTR REG_VALUE_DELAY = L"Delay";
constexpr LPCWSTR REG_VALUE_REPEAT = L"Repeat";
constexpr LPCWSTR REG_VALUE_ENABLE = L"Enable";

bool WriteRegistryDWORD(LPCWSTR name, DWORD value);

bool ReadRegistryDWORD(LPCWSTR name, DWORD &value);

struct KeyrateConfig {
	DWORD delay = 300;
	DWORD repeat = 40;
	bool enable = true;
};

inline KeyrateConfig g_config;

void LoadConfig();

void SaveConfig();

#endif //PERSISTENCE_HPP
