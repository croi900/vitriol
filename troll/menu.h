#pragma once

#include "settings.h"
#include "hook.h"
#include "interface.h"
#include "imgui-1.88/imgui.h"
#include "imgui-1.88/backends/imgui_impl_dx9.h"
#include "imgui-1.88/backends/imgui_impl_win32.h"



namespace menu {
	bool open = false; 
	bool flag = false;
	bool show_demo_window = true;
	float scr_w = GetSystemMetrics(SM_CXSCREEN);
	float scr_h = GetSystemMetrics(SM_CYSCREEN);

	void apply_style() {
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.14f, 0.16f, 0.11f, 0.52f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.27f, 0.30f, 0.23f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.34f, 0.26f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.28f, 0.32f, 0.24f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.30f, 0.22f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.23f, 0.27f, 0.21f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
		colors[ImGuiCol_Button] = ImVec4(0.29f, 0.34f, 0.26f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
		colors[ImGuiCol_Header] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.42f, 0.31f, 0.6f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
		colors[ImGuiCol_Separator] = ImVec4(0.14f, 0.16f, 0.11f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.54f, 0.57f, 0.51f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.19f, 0.23f, 0.18f, 0.00f); // grip invis
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.54f, 0.57f, 0.51f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.54f, 0.57f, 0.51f, 0.78f);
		colors[ImGuiCol_TabActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.78f, 0.28f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.73f, 0.67f, 0.24f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		ImGuiStyle& style = ImGui::GetStyle();
		style.FrameBorderSize = 1.0f;
		style.WindowRounding = 0.0f;
		style.ChildRounding = 0.0f;
		style.FrameRounding = 0.0f;
		style.PopupRounding = 0.0f;
		style.ScrollbarRounding = 0.0f;
		style.GrabRounding = 0.0f;
		style.TabRounding = 0.0f;
	}

	namespace esp {
		namespace box {
			const char* styles[]{
				"Box2d","Box3d","Corners"
			};
			const char* cur_style = "Corners";

			const char* sub_styles[]{
				"Bordered","Simple"
			};
			const char* cur_sub_styles = "Bordered";

			bool open = false;

			void draw_menu() {
				if (!open) return;
				ImGui::Begin("Player ESP");

				ImGui::Checkbox("Enabled", &glob::esp::box::enabled);

				if (ImGui::BeginCombo("combo_esp_box_style", cur_style)) // The second parameter is the label previewed before opening the combo.
				{
					for (int n = 0; n < IM_ARRAYSIZE(styles); n++)
					{
						bool is_selected = (cur_style == styles[n]); // You can store your selection however you want, outside or inside your objects
						if (ImGui::Selectable(styles[n], is_selected))
							cur_style = styles[n];
							if (is_selected)
								ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
							if (cur_style == styles[n]) {
								glob::esp::box::style = n;
							}
					}
					ImGui::EndCombo();
				}
				if (ImGui::BeginCombo("combo_esp_box_substyle", cur_sub_styles)) // The second parameter is the label previewed before opening the combo.
				{
					for (int n = 0; n < IM_ARRAYSIZE(sub_styles); n++)
					{
						bool is_selected = (cur_sub_styles == sub_styles[n]); // You can store your selection however you want, outside or inside your objects
						if (ImGui::Selectable(sub_styles[n], is_selected))
							cur_sub_styles = sub_styles[n];
						if (is_selected)
							ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
						if (cur_sub_styles == sub_styles[n]) {
							glob::esp::box::substyle = n;
						}
					}
					ImGui::EndCombo();
				}

				ImGui::ColorEdit3("Inner color(Main)", (float*)&glob::esp::box::inner_color, ImGuiColorEditFlags_InputRGB);
				ImGui::ColorEdit3("Outer color(Borders)", (float*)&glob::esp::box::outer_color, ImGuiColorEditFlags_InputRGB);
				ImGui::End();

			}
		}

		namespace info {

			bool open = false;

			namespace cname {
				const char* styles[]{
					"Borders", "No Borders"
				};
				const char* cur_style = "Borders";
				const char* pos[]{
					"Top", "Right", "Bottom", "Left", "TopLeft", "BottomLeft","BottomRight","TopRight"
				};
				const char* cur_pos = "Bottom";

				void draw_category() {
					using namespace glob::esp::info;
					if (!open) return;

					

					if (ImGui::BeginTabItem("Name")) {
						ImGui::Checkbox("Enabled", &name::enabled);
						ImGui::ColorEdit3("Inner color(Main)", (float*)&name::inner_color, ImGuiColorEditFlags_InputRGB);
						ImGui::ColorEdit3("Outer color(Borders)", (float*)&name::outer_color, ImGuiColorEditFlags_InputRGB);

						if (ImGui::BeginCombo("Border Style", cur_style)) // The second parameter is the label previewed before opening the combo.
						{
							for (int n = 0; n < IM_ARRAYSIZE(styles); n++)
							{
								bool is_selected = (cur_style == styles[n]); // You can store your selection however you want, outside or inside your objects
								if (ImGui::Selectable(styles[n], is_selected))
									cur_style = styles[n];
								if (is_selected)
									ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
								if (cur_style == styles[n]) {
									name::style = n;
								}
							}
							ImGui::EndCombo();
						}

						if (ImGui::BeginCombo("Position", cur_pos)) // The second parameter is the label previewed before opening the combo.
						{
							for (int n = 0; n < IM_ARRAYSIZE(pos); n++)
							{
								bool is_selected = (cur_pos == pos[n]); // You can store your selection however you want, outside or inside your objects
								if (ImGui::Selectable(pos[n], is_selected))
									cur_pos = pos[n];
								if (is_selected)
									ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
								if (cur_pos == pos[n]) {
									name::position = n;
								}
							}
							ImGui::EndCombo();
						}
						ImGui::EndTabItem();
					}
				}
			}
			namespace chp_num {
				const char* styles[]{
					"Borders", "No Borders"
				};
				const char* cur_style = "Borders";
				const char* pos[]{
					"Top", "Right", "Bottom", "Left", "TopLeft", "BottomLeft","BottomRight","TopRight"
				};
				const char* cur_pos = "Bottom";

				void draw_category() {
					using namespace glob::esp::info;
					if (!open) return;



					if (ImGui::BeginTabItem("Health")) {
						ImGui::Checkbox("Enabled", &hp_num::enabled);
						ImGui::ColorEdit3("Inner color(Main)", (float*)&hp_num::inner_color, ImGuiColorEditFlags_InputRGB);
						ImGui::ColorEdit3("Outer color(Borders)", (float*)&hp_num::outer_color, ImGuiColorEditFlags_InputRGB);

						if (ImGui::BeginCombo("Border Style", cur_style)) // The second parameter is the label previewed before opening the combo.
						{
							for (int n = 0; n < IM_ARRAYSIZE(styles); n++)
							{
								bool is_selected = (cur_style == styles[n]); // You can store your selection however you want, outside or inside your objects
								if (ImGui::Selectable(styles[n], is_selected))
									cur_style = styles[n];
								if (is_selected)
									ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
								if (cur_style == styles[n]) {
									hp_num::style = n;
								}
							}
							ImGui::EndCombo();
						}

						if (ImGui::BeginCombo("Position", cur_pos)) // The second parameter is the label previewed before opening the combo.
						{
							for (int n = 0; n < IM_ARRAYSIZE(pos); n++)
							{
								bool is_selected = (cur_pos == pos[n]); // You can store your selection however you want, outside or inside your objects
								if (ImGui::Selectable(pos[n], is_selected))
									cur_pos = pos[n];
								if (is_selected)
									ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
								if (cur_pos == pos[n]) {
									hp_num::position = n;
								}
							}
							ImGui::EndCombo();
						}
						ImGui::EndTabItem();
					}
				}
			}
			namespace cweapon {
				const char* styles[]{
					"Borders", "No Borders"
				};
				const char* cur_style = "Borders";
				const char* pos[]{
					"Top", "Right", "Bottom", "Left", "TopLeft", "BottomLeft","BottomRight","TopRight"
				};
				const char* cur_pos = "Bottom";

				void draw_category() {
					using namespace glob::esp::info;
					if (!open) return;



					if (ImGui::BeginTabItem("Weapon")) {
						ImGui::Checkbox("Enabled", &weapon::enabled);
						ImGui::ColorEdit3("Inner color(Main)", (float*)&weapon::inner_color, ImGuiColorEditFlags_InputRGB);
						ImGui::ColorEdit3("Outer color(Borders)", (float*)&weapon::outer_color, ImGuiColorEditFlags_InputRGB);

						if (ImGui::BeginCombo("Border Style", cur_style)) // The second parameter is the label previewed before opening the combo.
						{
							for (int n = 0; n < IM_ARRAYSIZE(styles); n++)
							{
								bool is_selected = (cur_style == styles[n]); // You can store your selection however you want, outside or inside your objects
								if (ImGui::Selectable(styles[n], is_selected))
									cur_style = styles[n];
								if (is_selected)
									ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
								if (cur_style == styles[n]) {
									weapon::style = n;
								}
							}
							ImGui::EndCombo();
						}

						if (ImGui::BeginCombo("Position", cur_pos)) // The second parameter is the label previewed before opening the combo.
						{
							for (int n = 0; n < IM_ARRAYSIZE(pos); n++)
							{
								bool is_selected = (cur_pos == pos[n]); // You can store your selection however you want, outside or inside your objects
								if (ImGui::Selectable(pos[n], is_selected))
									cur_pos = pos[n];
								if (is_selected)
									ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
								if (cur_pos == pos[n]) {
									weapon::position = n;
								}
							}
							ImGui::EndCombo();
						}
						ImGui::EndTabItem();
					}
				}
			}
			namespace cdistance {
				const char* styles[]{
					"Borders", "No Borders"
				};
				const char* cur_style = "Borders";
				const char* pos[]{
					"Top", "Right", "Bottom", "Left", "TopLeft", "BottomLeft","BottomRight","TopRight"
				};
				const char* cur_pos = "Bottom";

				void draw_category() {
					using namespace glob::esp::info;
					if (!open) return;



					if (ImGui::BeginTabItem("Distance")) {
						ImGui::Checkbox("Enabled", &distance::enabled);
						ImGui::ColorEdit3("Inner color(Main)", (float*)&distance::inner_color, ImGuiColorEditFlags_InputRGB);
						ImGui::ColorEdit3("Outer color(Borders)", (float*)&distance::outer_color, ImGuiColorEditFlags_InputRGB);

						if (ImGui::BeginCombo("Border Style", cur_style)) // The second parameter is the label previewed before opening the combo.
						{
							for (int n = 0; n < IM_ARRAYSIZE(styles); n++)
							{
								bool is_selected = (cur_style == styles[n]); // You can store your selection however you want, outside or inside your objects
								if (ImGui::Selectable(styles[n], is_selected))
									cur_style = styles[n];
								if (is_selected)
									ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
								if (cur_style == styles[n]) {
									distance::style = n;
								}
							}
							ImGui::EndCombo();
						}

						if (ImGui::BeginCombo("Position", cur_pos)) // The second parameter is the label previewed before opening the combo.
						{
							for (int n = 0; n < IM_ARRAYSIZE(pos); n++)
							{
								bool is_selected = (cur_pos == pos[n]); // You can store your selection however you want, outside or inside your objects
								if (ImGui::Selectable(pos[n], is_selected))
									cur_pos = pos[n];
								if (is_selected)
									ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
								if (cur_pos == pos[n]) {
									distance::position = n;
								}
							}
							ImGui::EndCombo();
						}

						ImGui::SliderInt("Decimals", &distance::decimals, 0, 16);
						ImGui::EndTabItem();
					}
				}
			}
			namespace crank {
				const char* styles[]{
					"Borders", "No Borders"
				};
				const char* cur_style = "Borders";
				const char* pos[]{
					"Top", "Right", "Bottom", "Left", "TopLeft", "BottomLeft","BottomRight","TopRight"
				};
				const char* cur_pos = "Bottom";

				void draw_category() {
					using namespace glob::esp::info;
					if (!open) return;



					if (ImGui::BeginTabItem("Rank")) {
						ImGui::Checkbox("Enabled", &rank::enabled);
						ImGui::ColorEdit3("Inner color(Main)", (float*)&rank::inner_color, ImGuiColorEditFlags_InputRGB);
						ImGui::ColorEdit3("Outer color(Borders)", (float*)&rank::outer_color, ImGuiColorEditFlags_InputRGB);

						if (ImGui::BeginCombo("Border Style", cur_style)) // The second parameter is the label previewed before opening the combo.
						{
							for (int n = 0; n < IM_ARRAYSIZE(styles); n++)
							{
								bool is_selected = (cur_style == styles[n]); // You can store your selection however you want, outside or inside your objects
								if (ImGui::Selectable(styles[n], is_selected))
									cur_style = styles[n];
								if (is_selected)
									ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
								if (cur_style == styles[n]) {
									rank::style = n;
								}
							}
							ImGui::EndCombo();
						}

						if (ImGui::BeginCombo("Position", cur_pos)) // The second parameter is the label previewed before opening the combo.
						{
							for (int n = 0; n < IM_ARRAYSIZE(pos); n++)
							{
								bool is_selected = (cur_pos == pos[n]); // You can store your selection however you want, outside or inside your objects
								if (ImGui::Selectable(pos[n], is_selected))
									cur_pos = pos[n];
								if (is_selected)
									ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
								if (cur_pos == pos[n]) {
									rank::position = n;
								}
							}
							ImGui::EndCombo();
						}

						ImGui::EndTabItem();
					}
				}
			}

			void draw_menu() {
				if (!open) return;
				ImGui::Begin("Player Info");
				if(ImGui::BeginTabBar("player_info_tab")) {
					
					cname::draw_category();
					chp_num::draw_category();
					cdistance::draw_category();
					cweapon::draw_category();
					crank::draw_category();

					ImGui::EndTabBar();
				}
				
				ImGui::End();
			}
		}
	}

	void get_menu_state() {
		if (GetAsyncKeyState(VK_INSERT) && !flag){
			flag = true;
			open = !open;
			
		}
		else if (!GetAsyncKeyState(VK_INSERT) && flag) {
			flag = false;
		}
	}


	void draw_background() {


		ImGui::GetBackgroundDrawList()->AddRectFilled({ 0.f,0.f }, { scr_w,scr_h * 0.06f }, glob::menu::bg::top_bg);
		ImGui::GetBackgroundDrawList()->AddRect({ 0.f,0.f }, { scr_w - 0.f,scr_h * 0.06f - 0.f }, glob::menu::bg::grid,1.f);
		ImGui::GetBackgroundDrawList()->AddRect({ 0.f,4.f }, { scr_w - 0.f,scr_h * 0.06f - 4.f }, glob::menu::bg::grid, 1.f);

		ImGui::GetBackgroundDrawList()->AddRectFilled({ 0.f, scr_h * 0.94f }, { scr_w,scr_h * 0.06f + scr_h * 0.94f }, glob::menu::bg::bottom_bg);
		ImGui::GetBackgroundDrawList()->AddRect({ 0.f,0.f + scr_h * 0.94f }, { scr_w - 0.f,scr_h * 0.06f - 0 + scr_h * 0.94f }, glob::menu::bg::grid, 1.f);
		ImGui::GetBackgroundDrawList()->AddRect({ 0.f,4.f + scr_h * 0.94f }, { scr_w - 0.f,scr_h * 0.06f - 4 + scr_h * 0.94f }, glob::menu::bg::grid, 1.f);

		
	}

	void top_bg_frame() {
		ImGui::Begin("top_bg_frame", 0,
			ImGuiWindowFlags_NoBackground 
			| ImGuiWindowFlags_NoCollapse 
			| ImGuiWindowFlags_NoResize 
			| ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoTitleBar);
		ImGui::SetWindowPos("top_bg_frame", { 0,0 });
		ImGui::SetWindowSize("top_bg_frame", { scr_w,scr_h*0.06f});
		
		if (ImGui::Button("Player ESP")) {
			esp::box::open = !esp::box::open;
		}		  

		ImGui::SameLine();	   

		if (ImGui::Button("Player Info")) {
			esp::info::open = !esp::info::open;
		}

		ImGui::End();
	}

	void menu_think() {
		get_menu_state();
		ImGui::GetIO().MouseDrawCursor = open;
		
		if (!open) return;

		draw_background();
		top_bg_frame();
		esp::box::draw_menu();
		esp::info::draw_menu();
		
	}
}