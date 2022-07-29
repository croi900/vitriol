#pragma once

#include <Windows.h>
#include <string_view>
#include <psapi.h>
#include <signal.h>
#include <limits>
#include <array>
#include <string>

#include <d3d9.h>
#include <d3dx9.h>

#include "menu.h"
#include "interface.h"
#include "esp.h"
#include "aimbot.h"

#include "sdk/vgui/VPanelWrapper.h"

#ifndef GWL_WNDPROC
#define GWL_WNDPROC GWLP_WNDPROC
#endif
IMGUI_IMPL_API LRESULT  ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WNDPROC oWndProc;
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (menu::open) {
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
        return true;
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

namespace core {
    namespace hook {
        template<typename T>
        inline T vmt_hook(PVOID** src, PVOID dst, int index)
        {
            PVOID* VMT = *src;
            PVOID ret = (VMT[index]);
            DWORD originalProtection;
            VirtualProtect(&VMT[index], sizeof(PVOID), PAGE_EXECUTE_READWRITE, &originalProtection);
            VMT[index] = dst;
            VirtualProtect(&VMT[index], sizeof(PVOID), originalProtection, &originalProtection);
            return (T)ret;
        };

        inline auto bad_char_table(std::string_view pattern) noexcept {
            std::array<std::size_t, 256> table;

            auto lastWildcard = pattern.rfind('?');
            if (lastWildcard == std::string_view::npos)
                lastWildcard = 0;

            const auto defaultShift = (std::max)(std::size_t(1), pattern.length() - 1 - lastWildcard);
            table.fill(defaultShift);

            for (auto i = lastWildcard; i < pattern.length() - 1; ++i)
                table[static_cast<std::uint8_t>(pattern[i])] = pattern.length() - 1 - i;

            return table;
        }

        inline const char* find_pattern(const char* moduleName, std::string_view pattern, std::string patternName) noexcept
        {
            PVOID moduleBase = 0;
            std::size_t moduleSize = 0;
            if (HMODULE handle = GetModuleHandleA(moduleName))
                if (MODULEINFO moduleInfo; GetModuleInformation(GetCurrentProcess(), handle, &moduleInfo, sizeof(moduleInfo)))
                {
                    moduleBase = moduleInfo.lpBaseOfDll;
                    moduleSize = moduleInfo.SizeOfImage;
                }


            if (moduleBase && moduleSize) {
                int lastIdx = pattern.length() - 1;
                const auto badCharTable = bad_char_table(pattern);

                auto start = static_cast<const char*>(moduleBase);
                const auto end = start + moduleSize - pattern.length();

                while (start <= end) {
                    int i = lastIdx;
                    while (i >= 0 && (pattern[i] == '?' || start[i] == pattern[i]))
                        --i;

                    if (i < 0)
                    {
                        return start;
                    }

                    start += badCharTable[static_cast<std::uint8_t>(start[lastIdx])];
                }
            }
            std::string toPrint = "Failed to find pattern\"" + patternName + "\", let the dev know ASAP!";
            MessageBoxA(NULL, toPrint.c_str(), "ERROR", MB_OK | MB_ICONWARNING);
            return 0;
        }

        inline char* get_real(char* address, int offset, int instructionSize, bool isRelative = true) // Address must be an instruction, not a pointer! And offset = the offset to the bytes you want to retrieve.
        {
#ifdef _WIN64
            isRelative = true;
#endif
            char* instruction = address + offset;
            if (!isRelative)
            {
                return *(char**)(instruction);
            }

            int relativeAddress = *(int*)(instruction);
            char* realAddress = address + instructionSize + relativeAddress;
            return realAddress;
        }

        namespace present {
            typedef HRESULT(__stdcall* hooked)(IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
            hooked orig;
            HRESULT __stdcall hook(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);

            void initialize_hook() {
                char* ptr = get_real((char*)find_pattern("gameoverlayrenderer64", "\xFF\x15????\x8B\xF8\xEB\x1E", "Present"), 0x2, 6, false);

                orig = *(hooked*)(ptr);

                *(hooked**)(ptr) = (hooked*)hook;

                
            }

            bool imgui_init = false;

            HRESULT __stdcall hook(IDirect3DDevice9* pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion) {
                //hijack::loop();
                if (imgui_init == false) {
                    HWND window = FindWindowA("Valve001", nullptr);
                    oWndProc = (WNDPROC)SetWindowLongPtrA(window, GWL_WNDPROC, (LONG_PTR)WndProc);
                    if (window == NULL) MessageBoxA(GetActiveWindow(), "cannot find Valve001", "FUCK", MB_OK);
                    D3DXCreateLine(pDevice, &hacks::esp::line);
                    IMGUI_CHECKVERSION();
                    ImGui::CreateContext();
                    ImGuiIO& io = ImGui::GetIO(); (void)io;
                    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
                    ImGui::StyleColorsDark();
                    ImGui_ImplWin32_Init(window);
                    ImGui_ImplDX9_Init(pDevice);
                    imgui_init = true;
                    menu::apply_style();
                }

                DWORD colorwrite, srgbwrite;
                pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &colorwrite);
                pDevice->GetRenderState(D3DRS_SRGBWRITEENABLE, &srgbwrite);

                pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
                pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

                

                ImGui_ImplDX9_NewFrame();
                ImGui_ImplWin32_NewFrame();
                ImGui::NewFrame();

                menu::menu_think();
               
                hacks::r_aim::aim_think();

                for(int i = 0 ;i < iface::cl_entity_list->GetHighestEntityIndex(); ++i)
                    hacks::esp::do_esp((C_BasePlayer*)iface::cl_entity_list->GetClientEntity(i),i);

                ImGui::EndFrame();
                ImGui::Render();
                ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());


                pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, colorwrite);
                pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, srgbwrite);

                return present::orig(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
            }
        }

        namespace paint_traverse {

            VPanel* last_panel_id;

            typedef void(__thiscall* hooked)(void*, VPanel*, bool, bool);
            hooked orig;
            void __fastcall hook(VPanelWrapper* _this,
#ifndef _WIN64
                void*,
#endif
                VPanel* panel, bool force_repaint, bool allow_force)
            {
                iface::input_sys->EnableInput(!menu::open);
                if (!strcmp(iface::panel_wrapper->GetName(panel), "FocusOverlayPanel"))
                {
                    last_panel_id = panel;
                    iface::panel_wrapper->SetKeyBoardInputEnabled(panel, menu::open);
                    iface::panel_wrapper->SetMouseInputEnabled(panel, menu::open);
                }
                orig(_this, panel, force_repaint, allow_force);
            }

            void initialize_hook() {
                orig = vmt_hook<hooked>((PVOID**)iface::panel_wrapper, (PVOID)hook, 41);
            }

        }
    }
}

/*for (int i = 0; i < iface::cl_entity_list->GetHighestEntityIndex(); ++i) {
    auto entity = (C_BasePlayer*)iface::cl_entity_list->GetClientEntity(i);
    if (entity == nullptr)
        continue;
    if (entity->IsDormant())
        continue;
    if (!entity->IsPlayer() || !entity->IsAlive())
        continue;

    Vector pos;
    auto pos3d = entity->GetAbsOrigin();
    iface::debug_overlay->ScreenPosition(pos3d, pos);


}*/
