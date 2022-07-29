#pragma once
#include "imgui-1.88/imgui.h"
#include "interface.h"
#include "sdk/client/C_BasePlayer.h"
#include "esp.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <deque>
#include <fstream>
namespace hacks {
	namespace aim {

	}

	namespace r_aim {

		bool enable_aim_graph = true;

		std::deque<float> pitch_dq;
		std::deque<float> yaw_dq;

		float pitch_ang[128];
		float yaw_ang[128];
		int n = 0;

		std::ofstream aim_logs("aim_logs.csv");

		void update_angles() {
			auto local_player = (C_BasePlayer*)core::iface::cl_entity_list->GetClientEntity(
				core::iface::engine_client->GetLocalPlayer()
			);

			if (pitch_dq.size() < 128){
				pitch_dq.push_back(local_player->GetAbsAngles().x);
			}
			else {
				pitch_dq.pop_front();
				pitch_dq.push_back(local_player->GetAbsAngles().x);
			}

			if (yaw_dq.size() < 128) {
				yaw_dq.push_back(local_player->GetAbsAngles().y);
			}
			else {
				yaw_dq.pop_front();
				yaw_dq.push_back(local_player->GetAbsAngles().y);
			}
			n = 0;
			for (auto& i : pitch_dq) {
				pitch_ang[n] = i;
				++n;
			}
			n = 0;
			for (auto& i : yaw_dq) {
				yaw_ang[n] = i;
				++n;
			}

			aim_logs << local_player->GetAbsAngles().x << ','
				<< local_player->GetAbsAngles().y << ','
				<< local_player->GetAbsAngles().z << '\n';
		}

		void draw_aim_graph() {
			if (!enable_aim_graph) return;
			ImGui::Begin("[DEBUG] Aim Graph");
			
			update_angles();
			ImGui::PlotLines("Pitch", pitch_ang, IM_ARRAYSIZE(pitch_ang));
			ImGui::PlotLines("Yaw", yaw_ang, IM_ARRAYSIZE(yaw_ang));
			

			ImGui::End();  
		}

		
		float distsqr(float x1, float y1, float x2, float y2) {
			return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
		}
		struct point {
			float x;
			float y;
		} closest;

		void get_closest() {
			using namespace core;

			float min_dist = D3D10_FLOAT32_MAX;
			
			for (int i = 0;i < iface::cl_entity_list->GetHighestEntityIndex(); ++i)
			{
				auto ply = (C_BasePlayer*)iface::cl_entity_list->GetClientEntity(i);

				if (ply == nullptr)
					continue;
				if (ply->IsDormant())
					continue;
				if (!ply->IsPlayer() || !ply->IsAlive())
					continue;

				auto r = esp::box::get_bounds_rect(ply);
				auto cx = r.top.x / 2 + r.bottom.x / 2;
				auto cy = r.top.y + 0.25f * (r.bottom.y - r.top.y);
				auto d = distsqr(menu::scr_w/2, menu::scr_h/2, cx, cy);
			
				if (d < min_dist) {
					closest.x = cx;
					closest.y = cy;
					min_dist = d;
				}
			}
		
		}

		void move_mouse_relative(int x, int y) {
			char dbgtxt[128];
			sprintf_s(dbgtxt, "%d %d", x, y);
			ImGui::GetForegroundDrawList()->AddText({ menu::scr_w / 4,menu::scr_h / 4 }, 0xFFFFFFFF, dbgtxt);

			INPUT input;
			input.type = INPUT_MOUSE;
			input.mi.mouseData = 0;
			input.mi.time = 0;
			input.mi.dx = x;
			input.mi.dy = y;
			input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK;
			SendInput(1, &input, sizeof(input));
		}
		float clk = 0;
		void aim_think(){
			if (core::iface::engine_client->IsInGame() ) {
				//draw_aim_graph();
				get_closest();

				auto x = closest.x - menu::scr_w / 2;
				auto y = closest.y - menu::scr_h / 2;


				if ((GetKeyState(VK_LBUTTON) & 0x80) == 0 && (GetKeyState(VK_RBUTTON) & 0x80) == 0) return;
				/*if ((GetKeyState(VK_W) & 0x80) != 0) return;
				if ((GetKeyState(VK_A) & 0x80) != 0) return;
				if ((GetKeyState(VK_S) & 0x80) != 0) return;
				if ((GetKeyState(VK_D) & 0x80) != 0) return;*/

				if (x * x + y * y < 100 * 100 && x * x + y * y > 64) {
					auto up = sin(atan2(y, x));
					auto right = cos(atan2(y, x));
					auto mod = (x * x + y * y) / (100 * 100);
					move_mouse_relative(
						 clamp(10 * cbrt(mod), 1, 10) * right * 2,
						 clamp(10 * cbrt(mod), 1, 10) * up * 2);
				}
				
			}
		}
	}
}