#pragma once
#include "sdk/client/CClientEntityList.h"
#include "sdk/engine/CIVDebugOverlay.h"
#include "sdk/client/CInputSystem.h"
#include "sdk/vgui/VPanelWrapper.h"
#include "sdk/engine/CEngineClient.h"
#include <string>
namespace core {
	namespace iface {
        CClientEntityList* cl_entity_list = 0;
        CIVDebugOverlay* debug_overlay = nullptr;
        typedef void* (__cdecl* tCreateInterface)(const char* name, int* returnCode);
        CInputSystem* input_sys = nullptr;
        VPanelWrapper* panel_wrapper = nullptr;
        CEngineClient* engine_client = nullptr;
        void* get_interface(const char* dllname, const char* interfacename)
        {
            tCreateInterface CreateInterface = (tCreateInterface)GetProcAddress(GetModuleHandleA(dllname), "CreateInterface");

            int ret = 0;
            void* ptr_interface = CreateInterface(interfacename, &ret);
            if (ret == 1) {
                MessageBoxA(GetActiveWindow(), std::string("error creating interface ").append(interfacename).c_str(), "FUCK", MB_OK);
            }
            return ptr_interface;
        }

        void init_ent_list() {
            cl_entity_list = (CClientEntityList*)get_interface("client.dll", "VClientEntityList003");
           // cl_debug_overlay = (CIVDebugOverlay*)get_interface("engine.dll", "CIVDebugOverlay015");
            
        }

        void init_debug_overlay() {
            debug_overlay = (CIVDebugOverlay*)get_interface("engine.dll", "VDebugOverlay003");
        }

        void init_input_sys() {
            input_sys = (CInputSystem*)get_interface("inputsystem.dll", "InputSystemVersion001");
        }

        void init_panel_wrapper() {
            panel_wrapper = (VPanelWrapper*)get_interface("vgui2.dll", "VGUI_Panel009");
        }

        void init_engine_client() {
            engine_client = (CEngineClient*)get_interface("engine.dll", "VEngineClient015");
        }
        
	}
}