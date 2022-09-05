#pragma once
#include "interface.h"
#include "hijack.h"
#include "draw_utils.h"
#include "present.h"

#include "sdk/client/C_BasePlayer.h"
#include <Windows.h>
#include <fstream>
#include <thread>
namespace core {

	std::ofstream log("log.out");
	HMODULE h_mod;
	void khak_detach() {
		/*FreeLibrary(hModule);*/
		//FreeConsole();
	}

	void khak_loop() {
		for (int i = 1; i <= iface::cl_entity_list->GetHighestEntityIndex(); ++i) {
			auto ent = (C_BasePlayer*)(iface::cl_entity_list->GetClientEntity(i));
			log << ent->GetAbsOrigin().x << " " << ent->GetAbsOrigin().y << " " << ent->GetAbsOrigin().z << std::endl;
		}
	
	}

	void khak_init() {
		iface::init_ent_list();
		iface::init_debug_overlay();
		iface::init_input_sys();
		iface::init_panel_wrapper();
		iface::init_engine_client();
		//hijack::execute();
		//draw::initialize();
		hook::paint_traverse::initialize_hook();
		hook::present::initialize_hook();
		
		
	}
}


//for (int i = 0; i < iface::cl_entity_list->GetHighestEntityIndex(); ++i) {
//	auto entity = (C_BasePlayer*)iface::cl_entity_list->GetClientEntity(i);
//	if (entity == nullptr) // https://wiki.facepunch.com/gmod/Enums/TEAM
//		continue;
//	if (entity->IsDormant())
//		continue;
//	if (!entity->IsPlayer() || !entity->IsAlive())
//		continue;

//	Vector pos;
//	auto pos3d = entity->GetAbsOrigin();
//	if(iface::debug_overlay != nullptr)
//		iface::debug_overlay->ScreenPosition(pos3d, pos);
//	//hwrt->DrawRectangle({ pos.x - 5,pos.y - 5,pos.x + 5,pos.y + 5 }, black_brush);
//}
//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)hijack::execute, 0, 0, 0);
		//Detac(h_mod);
		/**/