#pragma once

#include "sdk/client/C_BasePlayer.h"
#include "interface.h"
#include "imgui-1.88/imgui.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include "settings.h"
#include <iomanip>
#include <random>
#include <unordered_map>

static void random_string(int l, char* s) {
	if (l > sizeof(s)-1) return;
	int i = 0;
	srand(time(0));
	while ((i++)<l) {
		s[i] = '0' + (rand()%'z' - '0');
	}
	s[i] = 0;
	srand(time(0)+1);
}

namespace hacks {
	namespace esp {
		ID3DXLine* line;
		
		int index = 0;

		struct rect {
			ImVec2 top = ImVec2(D3D10_FLOAT32_MAX, D3D10_FLOAT32_MAX);
			ImVec2 bottom = ImVec2(0, 0);
		};


		void draw_line_bordered(ImVec2 to, ImVec2 from, ImColor inner, ImColor outer) {
			D3DXVECTOR2 lines[2] = {
					D3DXVECTOR2(from.x, from.y),
					D3DXVECTOR2(to.x, to.y)
			};
			D3DXVECTOR2 outline1[2] = {
				D3DXVECTOR2(from.x - 1, from.y - 1),
				D3DXVECTOR2(to.x - 1, to.y - 1)
			};
			D3DXVECTOR2 outline2[2] = {
				D3DXVECTOR2(from.x + 1, from.y + 1),
				D3DXVECTOR2(to.x + 1, to.y + 1)
			};

			line->Begin();
			line->Draw(lines, 2, D3DCOLOR_RGBA((int)(255*inner.Value.x), (int)(255 * inner.Value.y), (int)(255 * inner.Value.z), 255));
			line->Draw(outline1, 2, D3DCOLOR_RGBA((int)(255 * outer.Value.x), (int)(255 * outer.Value.y), (int)(255 * outer.Value.z), 255));
			line->Draw(outline2, 2, D3DCOLOR_RGBA((int)(255 * outer.Value.x), (int)(255 * outer.Value.y), (int)(255 * outer.Value.z), 255));
			line->End();
		}

		void draw_line(ImVec2 to, ImVec2 from, ImColor inner) {
			D3DXVECTOR2 lines[2] = {
					D3DXVECTOR2(from.x, from.y),
					D3DXVECTOR2(to.x, to.y)
			};

			line->Begin();
			line->Draw(lines, 2, D3DCOLOR_RGBA((int)(255 * inner.Value.x), (int)(255 * inner.Value.y), (int)(255 * inner.Value.z), 255));

			line->End();
		}

		void draw_rect(rect r, ImColor inner)
		{
			draw_line({ r.top.x,r.top.y }, { r.bottom.x,r.top.y }, inner);
			draw_line({ r.bottom.x,r.top.y }, { r.bottom.x,r.bottom.y }, inner);
			draw_line({ r.bottom.x,r.bottom.y }, { r.top.x,r.bottom.y }, inner);
			draw_line({ r.top.x,r.bottom.y }, { r.top.x,r.top.y }, inner);
		}

		void draw_rect_bordered(rect t, ImColor inner, ImColor outer) {
			draw_rect(t, inner);
			t.bottom.x -= 1;
			t.bottom.y -= 1;
			t.top.x += 1;
			t.top.y += 1;
			draw_rect(t, outer);
			t.bottom.x += 2;
			t.bottom.y += 2;
			t.top.x -= 2;
			t.top.y -= 2;
			draw_rect(t, outer);
		}

		

		C_BasePlayer* ply = nullptr;
		namespace box {

			rect get_bounds_rect() {
				rect bounds;

				auto obb_min = ply->GetCollideable()->OBBMins();
				auto obb_max = ply->GetCollideable()->OBBMaxs();

				Vector pts[]{
					{obb_max.x, obb_max.y, obb_max.z},
					{obb_max.x, obb_max.y, obb_min.z},
					{obb_max.x, obb_min.y, obb_min.z},
					{obb_max.x, obb_min.y, obb_max.z},
					{obb_min.x, obb_min.y, obb_min.z},
					{obb_min.x, obb_min.y, obb_max.z},
					{obb_min.x, obb_max.y, obb_max.z},
					{obb_min.x, obb_max.y, obb_min.z},
				};

				for (auto& pt : pts) {
					Vector screenpos;
					core::iface::debug_overlay->ScreenPosition(pt + ply->GetAbsOrigin(), screenpos);
					bounds.top.x = min(bounds.top.x, screenpos.x);
					bounds.top.y = min(bounds.top.y, screenpos.y);
					bounds.bottom.x = max(bounds.bottom.x, screenpos.x);
					bounds.bottom.y = max(bounds.bottom.y, screenpos.y);
				}

				return bounds;

			}

			rect get_bounds_rect(C_BasePlayer* ply) {
				rect bounds;

				auto obb_min = ply->GetCollideable()->OBBMins();
				auto obb_max = ply->GetCollideable()->OBBMaxs();

				Vector pts[]{
					{obb_max.x, obb_max.y, obb_max.z},
					{obb_max.x, obb_max.y, obb_min.z},
					{obb_max.x, obb_min.y, obb_min.z},
					{obb_max.x, obb_min.y, obb_max.z},
					{obb_min.x, obb_min.y, obb_min.z},
					{obb_min.x, obb_min.y, obb_max.z},
					{obb_min.x, obb_max.y, obb_max.z},
					{obb_min.x, obb_max.y, obb_min.z},
				};

				for (auto& pt : pts) {
					Vector screenpos;
					core::iface::debug_overlay->ScreenPosition(pt + ply->GetAbsOrigin(), screenpos);
					bounds.top.x = min(bounds.top.x, screenpos.x);
					bounds.top.y = min(bounds.top.y, screenpos.y);
					bounds.bottom.x = max(bounds.bottom.x, screenpos.x);
					bounds.bottom.y = max(bounds.bottom.y, screenpos.y);
				}

				return bounds;

			}

			void draw_box1() {
				auto bounds = get_bounds_rect();
				if (glob::esp::box::substyle == glob::esp::BOXESP_SUBSTYLE::Nothing) {
					ImGui::GetForegroundDrawList()->AddRect(bounds.top, bounds.bottom, glob::esp::box::inner_color);
				}
				else if (glob::esp::box::substyle == glob::esp::BOXESP_SUBSTYLE::Bordered) {
					draw_rect_bordered(bounds, glob::esp::box::inner_color, glob::esp::box::outer_color);
				}
				
			}

			void draw_box2() {
				auto b = get_bounds_rect();
				auto len = (b.bottom.x - b.top.x)/2.f*0.66f;
				if (glob::esp::box::substyle == glob::esp::BOXESP_SUBSTYLE::Bordered) {
					{
						draw_line_bordered({ b.top.x - 1,b.top.y }, { b.top.x + len, b.top.y }, glob::esp::box::inner_color, glob::esp::box::outer_color);
						draw_line_bordered({ b.top.x,b.top.y }, { b.top.x, b.top.y + len }, glob::esp::box::inner_color, glob::esp::box::outer_color);

						draw_line_bordered({ b.bottom.x + 1,b.top.y }, { b.bottom.x - len,b.top.y }, glob::esp::box::inner_color, glob::esp::box::outer_color);
						draw_line_bordered({ b.bottom.x,b.top.y }, { b.bottom.x,b.top.y + len }, glob::esp::box::inner_color, glob::esp::box::outer_color);

						draw_line_bordered({ b.bottom.x + 1,b.bottom.y }, { b.bottom.x - len,b.bottom.y }, glob::esp::box::inner_color, glob::esp::box::outer_color);
						draw_line_bordered({ b.bottom.x,b.bottom.y }, { b.bottom.x,b.bottom.y - len }, glob::esp::box::inner_color, glob::esp::box::outer_color);

						draw_line_bordered({ b.top.x - 1,b.bottom.y }, { b.top.x + len,b.bottom.y }, glob::esp::box::inner_color, glob::esp::box::outer_color);
						draw_line_bordered({ b.top.x,b.bottom.y }, { b.top.x,b.bottom.y - len }, glob::esp::box::inner_color, glob::esp::box::outer_color);
					}
				}
				else if (glob::esp::box::substyle == glob::esp::BOXESP_SUBSTYLE::Nothing) {
					{
						draw_line({ b.top.x - 1,b.top.y }, { b.top.x + len, b.top.y }, glob::esp::box::inner_color);
						draw_line({ b.top.x,b.top.y }, { b.top.x, b.top.y + len }, glob::esp::box::inner_color);

						draw_line({ b.bottom.x + 1,b.top.y }, { b.bottom.x - len,b.top.y }, glob::esp::box::inner_color);
						draw_line({ b.bottom.x,b.top.y }, { b.bottom.x,b.top.y + len }, glob::esp::box::inner_color);

						draw_line({ b.bottom.x + 1,b.bottom.y }, { b.bottom.x - len,b.bottom.y }, glob::esp::box::inner_color);
						draw_line({ b.bottom.x,b.bottom.y }, { b.bottom.x,b.bottom.y - len }, glob::esp::box::inner_color);

						draw_line({ b.top.x - 1,b.bottom.y }, { b.top.x + len,b.bottom.y }, glob::esp::box::inner_color);
						draw_line({ b.top.x,b.bottom.y }, { b.top.x,b.bottom.y - len }, glob::esp::box::inner_color);
					}
				}
				

			}

			void draw_box() {
				if (!glob::esp::box::enabled) return;
				if (glob::esp::box::style == glob::esp::BOXESP_STYLE::Box2d) {
					draw_box1();
				}
				if (glob::esp::box::style == glob::esp::BOXESP_STYLE::Corners) {
					draw_box2();
				}
				if (glob::esp::box::style == glob::esp::BOXESP_STYLE::Box3d) {
					//draw_box1();
				}
			}
		}

		namespace info {
			std::vector<std::string> positions[8];
			int styles[8][32];
			ImColor inner_color[8][32];
			ImColor outer_color[8][32];

			void get_information_and_store() {
				using namespace glob::esp::info;
				for (int i = 0; i < 8; ++i)
					positions[i].clear();

				player_info_t plyinf;
				core::iface::engine_client->GetPlayerInfo(index, &plyinf);

				if (name::enabled) {
					std::string info_name;
					std::stringstream iname_ss(info_name);
					iname_ss << plyinf.name;

					positions[name::position].push_back(iname_ss.str());
					styles[name::position][positions[name::position].size() - 1] = name::style;
					inner_color[name::position][positions[name::position].size() - 1] = name::inner_color;
					outer_color[name::position][positions[name::position].size() - 1] = name::outer_color;
				}
				
				if (hp_num::enabled) {
					std::string info_hp_num;
					std::stringstream ihp_num_ss(info_hp_num);
					ihp_num_ss << ply->GetHealth();

					positions[hp_num::position].push_back(ihp_num_ss.str());
					styles[hp_num::position][positions[hp_num::position].size() - 1] = hp_num::style;
					inner_color[hp_num::position][positions[hp_num::position].size() - 1] = hp_num::inner_color;
					outer_color[hp_num::position][positions[hp_num::position].size() - 1] = hp_num::outer_color;
				}

				if (weapon::enabled) {
					std::string info_weapon;
					std::stringstream iweapon_ss(info_weapon);
					iweapon_ss << ply->GetActiveWeapon()->GetName();

					positions[weapon::position].push_back(iweapon_ss.str());
					styles[weapon::position][positions[weapon::position].size() - 1] = weapon::style;
					inner_color[weapon::position][positions[weapon::position].size() - 1] = weapon::inner_color;
					outer_color[weapon::position][positions[weapon::position].size() - 1] = weapon::outer_color;
				}

				if (distance::enabled) {
					std::string info_distance;
					std::stringstream idistance_ss(info_distance);
					auto v1 = ply->GetAbsOrigin();
					auto local_player = (C_BasePlayer*)core::iface::cl_entity_list->GetClientEntity(core::iface::engine_client->GetLocalPlayer());
					auto v2 = local_player->GetAbsOrigin();

					idistance_ss << std::fixed  << std::setprecision(distance::decimals) << v1.DistTo(v2);

					positions[distance::position].push_back(idistance_ss.str());
					styles[distance::position][positions[distance::position].size() - 1] = distance::style;
					inner_color[distance::position][positions[distance::position].size() - 1] = distance::inner_color;
					outer_color[distance::position][positions[distance::position].size() - 1] = distance::outer_color;
				}
				//TO ADD FROM DOWN HERE USING LUA I GUESS
				if (rank::enabled) {
					std::string info_rank;
					std::stringstream irank_ss(info_rank);
					irank_ss << "Team: " << ply->GetTeam();

					positions[rank::position].push_back(irank_ss.str());
					styles[rank::position][positions[rank::position].size() - 1] = rank::style;
					inner_color[rank::position][positions[rank::position].size() - 1] = rank::inner_color;
					outer_color[rank::position][positions[rank::position].size() - 1] = rank::outer_color;
				}

				if (hack_ranks::enabled) {
					std::string info_hack_ranks;
					std::stringstream ihack_ranks_ss(info_hack_ranks);
					ihack_ranks_ss << "[NOT_IMPLEMENTED]";

					positions[hack_ranks::position].push_back(ihack_ranks_ss.str());
					styles[hack_ranks::position][positions[hack_ranks::position].size() - 1] = hack_ranks::style;
					inner_color[hack_ranks::position][positions[hack_ranks::position].size() - 1] = hack_ranks::inner_color;
					outer_color[hack_ranks::position][positions[hack_ranks::position].size() - 1] = hack_ranks::outer_color;
				}
				
			}

			void draw_text_outlined(const char* text, ImVec2 pos, ImColor inner, ImColor outer)
			{
				ImGui::GetForegroundDrawList()->AddText({ pos.x + 2,pos.y }, outer, text);
				ImGui::GetForegroundDrawList()->AddText({ pos.x - 2,pos.y }, outer, text);
				ImGui::GetForegroundDrawList()->AddText({ pos.x,pos.y + 2 }, outer, text);
				ImGui::GetForegroundDrawList()->AddText({ pos.x,pos.y - 2 }, outer, text);
				ImGui::GetForegroundDrawList()->AddText(pos, inner, text);
			}

			void draw_info_wnd(rect r,int position) {
				if (positions[position].empty())	return;
				float max_width = -1;
				float max_heigth = positions[position].size() * ImGui::CalcTextSize(positions[position][0].c_str()).y;

				for (auto inf : position[positions]) {
					max_width = max(max_width, ImGui::CalcTextSize(inf.c_str()).x);
				}

				int i = 0;

				ImVec2 wndpos(0,0);
				if (position == glob::esp::INFO_POSITION::Bottom) {
					wndpos = { (r.bottom.x + r.top.x) / 2 - max_width / 2, r.bottom.y };
				}
				if (position == glob::esp::INFO_POSITION::Top) {
					wndpos = { (r.bottom.x + r.top.x) / 2 - max_width / 2, r.top.y - max_heigth };
				}
				if (position == glob::esp::INFO_POSITION::Left) {
					wndpos = { r.top.x - max_width - 8, (r.bottom.y + r.top.y) / 2 - max_heigth/2 };
				}
				if (position == glob::esp::INFO_POSITION::Right) {
					wndpos = { r.bottom.x, (r.bottom.y + r.top.y) / 2 - max_heigth / 2 };
				}
														
				if (position == glob::esp::INFO_POSITION::TopLeft) {
					wndpos = { r.top.x - max_width , r.top.y - max_heigth };
				}
				if (position == glob::esp::INFO_POSITION::TopRight) {
					wndpos = { r.bottom.x , r.top.y - max_heigth };
				}
				if (position == glob::esp::INFO_POSITION::BottomLeft) {
					wndpos = { r.top.x - max_width, r.bottom.y };
				}
				if (position == glob::esp::INFO_POSITION::BottomRight) {
					wndpos = { r.bottom.x, r.bottom.y };
				}

				for (auto inf : positions[position]) {
					auto text = ImGui::CalcTextSize(inf.c_str());
					
					
					if (styles[position][i] == glob::esp::TEXT_STYLE::Bordered) {
						draw_text_outlined(inf.c_str(),
							{ 4 + wndpos.x + (max_width - text.x) / 2,4 + wndpos.y + (4 + text.y) * i },
							inner_color[position][i], outer_color[position][i]);
					}
					if (styles[position][i] == glob::esp::TEXT_STYLE::Nothing) {
						ImGui::GetForegroundDrawList()->AddText(
							{ 4 + wndpos.x + (max_width - text.x) / 2,4 + wndpos.y + (4 + text.y) * i },
							inner_color[position][i], inf.c_str());
					}
						
					i++;
				}

			}

			void draw_info() {
				get_information_and_store();
				auto r = box::get_bounds_rect();
				for(int i = 0; i < 8; ++i)
					info::draw_info_wnd(r, i);

			}
		}

		void do_esp_internal(C_BasePlayer* p) {
			box::draw_box();
			info::draw_info();
		}

		void do_esp(C_BasePlayer* p, int idx) {
			
			if (p == nullptr)
				return;
			if (p->IsDormant())
				return;
			if (!p->IsPlayer() || !p->IsAlive())
				return;
			esp::ply = p;
			esp::index = idx;
			do_esp_internal(p);
		}

		
	}
}