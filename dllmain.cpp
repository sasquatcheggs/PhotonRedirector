#include "pch.h"
#include "photon_redirect.h"

// Original function pointer type
typedef int (WINAPI* GetAddrInfoW_t)(
    PCWSTR pNodeName,
    PCWSTR pServiceName,
    const ADDRINFOW* pHints,
    PADDRINFOW* ppResult
    );

GetAddrInfoW_t OriginalGetAddrInfoW = nullptr;

// Hooked function
int WINAPI HookedGetAddrInfoW(
    PCWSTR pNodeName,
    PCWSTR pServiceName,
    const ADDRINFOW* pHints,
    PADDRINFOW* ppResult
) {
    if (pNodeName) {
        char domain[256];
        WideCharToMultiByte(CP_ACP, 0, pNodeName, -1, domain, 256, nullptr, nullptr);

        std::string redirect_ip = g_Redirector.Redirect(domain);

        if (!redirect_ip.empty()) {
            wchar_t redirect_ip_w[256];
            MultiByteToWideChar(CP_ACP, 0, redirect_ip.c_str(), -1, redirect_ip_w, 256);

            char msg[512];
            sprintf_s(msg, "Redirecting %s -> %s", domain, redirect_ip.c_str());
            OutputDebugStringA(msg);

            return OriginalGetAddrInfoW(redirect_ip_w, pServiceName, pHints, ppResult);
        }
    }

    return OriginalGetAddrInfoW(pNodeName, pServiceName, pHints, ppResult);
}

void InitializeHooks() {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    HMODULE ws2_32 = GetModuleHandleA("ws2_32.dll");
    OriginalGetAddrInfoW = (GetAddrInfoW_t)GetProcAddress(ws2_32, "GetAddrInfoW");

    if (OriginalGetAddrInfoW) {
        DetourAttach(&(PVOID&)OriginalGetAddrInfoW, HookedGetAddrInfoW);
        DetourTransactionCommit();
        OutputDebugStringA("Hooks initialized successfully");
    }
    else {
        OutputDebugStringA("Failed to get GetAddrInfoW address");
    }
}

void CleanupHooks() {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());

    if (OriginalGetAddrInfoW) {
        DetourDetach(&(PVOID&)OriginalGetAddrInfoW, HookedGetAddrInfoW);
        DetourTransactionCommit();
        OutputDebugStringA("Hooks cleaned up");
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        OutputDebugStringA("PhotonRedirector DLL loaded");
        InitializeHooks();
        break;
    case DLL_PROCESS_DETACH:
        CleanupHooks();
        OutputDebugStringA("PhotonRedirector DLL unloaded");
        break;
    }
    return TRUE;
}