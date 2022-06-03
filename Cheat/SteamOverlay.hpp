#pragma once
#include "includes.h"

namespace SteamOverlay {
    uintptr_t FindPattern(uintptr_t pModuleBaseAddress, const char* szSignature, size_t nSelectResultIndex = NULL) {
        auto PatternToBytes = [](const char* szpattern) {
            auto       m_iBytes = std::vector<int>{};
            const auto szStartAddr = const_cast<char*>(szpattern);
            const auto szEndAddr = const_cast<char*>(szpattern) + strlen(szpattern);

            for (auto szCurrentAddr = szStartAddr; szCurrentAddr < szEndAddr; ++szCurrentAddr) {
                if (*szCurrentAddr == '?') {
                    ++szCurrentAddr;
                    if (*szCurrentAddr == '?') ++szCurrentAddr;
                    m_iBytes.push_back(-1);
                }
                else m_iBytes.push_back(strtoul(szCurrentAddr, &szCurrentAddr, 16));
            }
            return m_iBytes;
        };

        const auto pDosHeader = (PIMAGE_DOS_HEADER)pModuleBaseAddress;
        const auto pNTHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)pModuleBaseAddress + pDosHeader->e_lfanew);
        const auto dwSizeOfImage = pNTHeaders->OptionalHeader.SizeOfImage;
        auto       m_iPatternBytes = PatternToBytes(szSignature);
        const auto pScanBytes = reinterpret_cast<std::uint8_t*>(pModuleBaseAddress);
        const auto m_iPatternBytesSize = m_iPatternBytes.size();
        const auto m_iPatternBytesData = m_iPatternBytes.data();
        size_t nFoundResults = 0;

        for (auto i = 0ul; i < dwSizeOfImage - m_iPatternBytesSize; ++i) {
            bool bFound = true;

            for (auto j = 0ul; j < m_iPatternBytesSize; ++j) {
                if (pScanBytes[i + j] != m_iPatternBytesData[j] && m_iPatternBytesData[j] != -1) {
                    bFound = false;
                    break;
                }
            }

            if (bFound) {
                if (nSelectResultIndex != 0) {
                    if (nFoundResults < nSelectResultIndex) {
                        nFoundResults++;
                        bFound = false;
                    }
                    else return reinterpret_cast<uintptr_t>(&pScanBytes[i]);
                }
                else return reinterpret_cast<uintptr_t>(&pScanBytes[i]);
            }
        }
        return NULL;
    }

    uintptr_t GetSteamModule() {
        return (uintptr_t)GetModuleHandleA("GameOverlayRenderer64.dll");
    }
    
    void CreateHook(__int64 iAddr, __int64 iFunction, __int64* iOriginal) {
        static uintptr_t pHookAddr;
        if (!pHookAddr) pHookAddr = FindPattern(GetSteamModule(), ("48 ? ? ? ? 57 48 83 EC 30 33 C0"));
        auto hook = ((__int64(__fastcall*)(__int64 addr, __int64 func, __int64* orig, __int64 smthng))(pHookAddr));
        hook((__int64)iAddr, (__int64)iFunction, iOriginal, (__int64)1);
    }
}