#include <InitTools/InitPlatform/InitPlatform_Windows.h>
#include <InitTools/InitPlatform.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

namespace InitPlatform_Windows {
    std::string getRegistryString(const std::wstring& fullPath, const std::wstring& valueName) {
#if defined(_WIN32) || defined(_WIN64)
        HKEY root = nullptr;
        std::wstring subKey;

        auto upper = [](std::wstring s) {
            std::transform(s.begin(), s.end(), s.begin(), ::towupper);
            return s;
        };

        std::wstring pathUpper = upper(fullPath);

        if(pathUpper.rfind(L"HKEY_LOCAL_MACHINE\\", 0) == 0) {
            root = HKEY_LOCAL_MACHINE;
            subKey = fullPath.substr(19); // длина "HKEY_LOCAL_MACHINE\"
        } 
        else if(pathUpper.rfind(L"HKEY_CURRENT_USER\\", 0) == 0) {
            root = HKEY_CURRENT_USER;
            subKey = fullPath.substr(18);
        }
        else if(pathUpper.rfind(L"HKEY_CLASSES_ROOT\\", 0) == 0) {
            root = HKEY_CLASSES_ROOT;
            subKey = fullPath.substr(18);
        }
        else if(pathUpper.rfind(L"HKEY_USERS\\", 0) == 0) {
            root = HKEY_USERS;
            subKey = fullPath.substr(11);
        }
        else if(pathUpper.rfind(L"HKEY_CURRENT_CONFIG\\", 0) == 0) {
            root = HKEY_CURRENT_CONFIG;
            subKey = fullPath.substr(20);
        } else {
            return "";
        }

        HKEY hKey = nullptr;
        if(RegOpenKeyExW(root, subKey.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS) {
            return "";
        }

        DWORD type = 0;
        DWORD dataSize = 0;
        if(RegQueryValueExW(hKey, valueName.c_str(), nullptr, &type, nullptr, &dataSize) != ERROR_SUCCESS || type != REG_SZ) {
            RegCloseKey(hKey);
            return "";
        }

        std::wstring buffer(dataSize / sizeof(wchar_t), L'\0');
        if(RegQueryValueExW(hKey, valueName.c_str(), nullptr, nullptr, reinterpret_cast<LPBYTE>(&buffer[0]), &dataSize) != ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return "";
        }
        RegCloseKey(hKey);

        if(!buffer.empty() && buffer.back() == L'\0') buffer.pop_back();

        int needed = WideCharToMultiByte(CP_UTF8, 0, buffer.c_str(), -1, nullptr, 0, nullptr, nullptr);
        std::string result(needed, '\0');
        WideCharToMultiByte(CP_UTF8, 0, buffer.c_str(), -1, &result[0], needed, nullptr, nullptr);
        if(!result.empty() && result.back() == '\0') result.pop_back();

        return result;
#else
        return "NON";
#endif
    }

    std::string getArchitecture() {
#if defined(_WIN32)
        return "32";
#elif defined(_WIN64)
        return "64";
#endif
        return "NON";
    }

    std::string getProductName() {
        if(InitPlatform::getOS() == "Windows") {
            return getRegistryString(L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"ProductName");
        } else {
            return "NON";
        }
    }

    std::string getVersionNumber() {
        if(InitPlatform::getOS() == "Windows") {
            std::string productName = getProductName();
            size_t firstSpace = productName.find(' ');
            if(firstSpace == std::string::npos) return "Unknown";
            size_t secondSpace = productName.find(' ', firstSpace + 1);
            if(secondSpace == std::string::npos) return productName.substr(firstSpace + 1);
            return productName.substr(firstSpace + 1, secondSpace - (firstSpace + 1));
        } else {
            return "NON";
        }
    }
};
