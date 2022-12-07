#include "..\imports.h"

std::uint8_t* PatternScan(void* module, const char* signature)
{
    static auto pattern_to_byte = [](const char* pattern) {
        std::vector<int> bytes = std::vector<int>{};
        char* start = const_cast<char*>(pattern);
        char* end = const_cast<char*>(pattern) + strlen(pattern);

        for (char* current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;
                if (*current == '?') {
                    ++current;
                }
                bytes.push_back(-1);
            } 
            else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER) module;
    PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS) ((std::uint8_t*) module + dosHeader->e_lfanew);

    DWORD sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
    std::vector<int> patternBytes = pattern_to_byte(signature);
    std::uint8_t* scanBytes = reinterpret_cast<std::uint8_t*>(module);

    auto s = patternBytes.size();
    auto d = patternBytes.data();

    for (auto i = 0ul; i < sizeOfImage - s; ++i) {
        bool found = true;
        for (auto j = 0ul; j < s; ++j) {
            if (scanBytes[i + j] != d[j] && d[j] != -1) {
                found = false;
                break;
            }
        }
        if (found) {
            return &scanBytes[i];
        }
    }
    return nullptr;
}