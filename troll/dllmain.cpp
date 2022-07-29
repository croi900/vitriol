// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>


#include "interface.h"
#include "init_stop.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    core::h_mod = hModule;
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH: {
            CreateThread(0,0,(LPTHREAD_START_ROUTINE)core::khak_init,0,0,0);
            
            return true;
        }
        case DLL_PROCESS_DETACH: {
            FreeLibrary(hModule);
            return true;
        }
    }
        
    return false;
}

