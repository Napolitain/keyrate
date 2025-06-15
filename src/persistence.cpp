//
// Created by Maxime Boucher on 14/06/2025.
//

#include "persistence.hpp"

bool WriteRegistryDWORD(const LPCWSTR name, const DWORD value) {
	HKEY hKey;
	if (RegCreateKeyExW(HKEY_CURRENT_USER, REG_PATH, 0, nullptr, 0, KEY_WRITE, nullptr, &hKey, nullptr) !=
	    ERROR_SUCCESS)
		return false;

	const LONG ret = RegSetValueExW(hKey, name, 0, REG_DWORD, (const BYTE *) &value, sizeof(value));
	RegCloseKey(hKey);
	return ret == ERROR_SUCCESS;
}

bool ReadRegistryDWORD(const LPCWSTR name, DWORD &value) {
	HKEY hKey;
	DWORD dataSize = sizeof(value);
	DWORD type = 0;
	if (RegOpenKeyExW(HKEY_CURRENT_USER, REG_PATH, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
		return false;

	const LONG ret = RegQueryValueExW(hKey, name, nullptr, &type, reinterpret_cast<LPBYTE>(&value), &dataSize);
	RegCloseKey(hKey);

	return (ret == ERROR_SUCCESS && type == REG_DWORD && dataSize == sizeof(value));
}

void LoadConfig() {
	DWORD val;
	if (ReadRegistryDWORD(REG_VALUE_DELAY, val)) g_config.delay = val;
	if (ReadRegistryDWORD(REG_VALUE_REPEAT, val)) g_config.repeat = val;

	if (ReadRegistryDWORD(REG_VALUE_ENABLE, val))
		g_config.enable = (val != 0);
}

void SaveConfig() {
	WriteRegistryDWORD(REG_VALUE_DELAY, g_config.delay);
	WriteRegistryDWORD(REG_VALUE_REPEAT, g_config.repeat);
	WriteRegistryDWORD(REG_VALUE_ENABLE, g_config.enable ? 1 : 0);
}
