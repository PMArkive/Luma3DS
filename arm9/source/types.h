/*
*   This file is part of Luma3DS
*   Copyright (C) 2016-2020 Aurora Wright, TuxSH
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

//Common data types
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

/// Creates a bitmask from a bit number.
#define BIT(n) (1U<<(n))

/// Aligns a struct (and other types?) to m, making sure that the size of the struct is a multiple of m.
#define ALIGN(m)   __attribute__((aligned(m)))

#define NORETURN __attribute__((noreturn))

#include "3dsheaders.h"

#define CFG_BOOTENV         (*(vu32 *)0x10010000)
#define CFG_UNITINFO        (*(vu8  *)0x10010010)
#define CFG_TWLUNITINFO     (*(vu8  *)0x10010014)
#define OTP_DEVCONSOLEID    (*(vu64 *)0x10012000)
#define OTP_TWLCONSOLEID    (*(vu64 *)0x10012100)
#define CFG11_SOCINFO       (*(vu32 *)0x10140FFC)

#define ISN3DS       (CFG11_SOCINFO & 2)
#define ISDEVUNIT    (CFG_UNITINFO != 0)

typedef struct __attribute__((packed, aligned(4)))
{
    char magic[4];
    u16 formatVersionMajor, formatVersionMinor;

    u32 config, multiConfig, bootConfig;
    u64 hbldr3dsxTitleId;
    u32 rosalinaMenuCombo;
} CfgData;

typedef struct
{
    char magic[4];
    u16 formatVersionMajor, formatVersionMinor;

    u8 lengthHash[32];
    u8 hash[32];
} PinData;

typedef struct
{
    u32 magic[2];
    u16 versionMinor, versionMajor;

    u16 processor, core;
    u32 type;

    u32 totalSize;
    u32 registerDumpSize;
    u32 codeDumpSize;
    u32 stackDumpSize;
    u32 additionalDataSize;
} ExceptionDumpHeader;

typedef enum FirmwareSource
{
    FIRMWARE_SYSNAND = 0,
    FIRMWARE_EMUNAND,
    FIRMWARE_EMUNAND2,
    FIRMWARE_EMUNAND3,
    FIRMWARE_EMUNAND4
} FirmwareSource;

typedef enum FirmwareType
{
    NATIVE_FIRM = 0,
    TWL_FIRM,
    AGB_FIRM,
    SAFE_FIRM,
    SYSUPDATER_FIRM,
    NATIVE_FIRM1X2X
} FirmwareType;

typedef enum bootType
{
    B9S = 0,
    B9SNTR,
    FIRM0,
    FIRM1,
    FIRMLAUNCH,
    NTR
} BootType;

extern bool isSdMode;

extern BootType bootType;

extern u16 launchedFirmTidLow[8];
extern u16 launchedPath[80+1];
