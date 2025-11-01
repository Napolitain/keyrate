//
// Created by Maxime Boucher on 14/06/2025.
//

#include "keyrate.hpp"

void SetKeyrate(const DWORD delay, const DWORD repeat, const bool enable) {
    FILTERKEYS keys = {sizeof(FILTERKEYS)};
    keys.iDelayMSec = delay;
    keys.iRepeatMSec = repeat;
    keys.dwFlags = enable ? (FKF_FILTERKEYSON | FKF_AVAILABLE) : 0;
    SystemParametersInfoW(SPI_SETFILTERKEYS, 0, &keys, SPIF_SENDCHANGE);
}
