#pragma once

#include "imgui-1.88/imgui.h"
#include <fstream>


namespace glob {
	namespace menu {
		namespace bg {
			ImColor main_bg(85, 85, 150, 0);
			ImColor bottom_bg(0, 40, 60, 0);
			ImColor top_bg(0, 40, 60, 0);
			ImColor grid(0, 60, 60, 0);

			std::ofstream out("esp_misc_hp_bar.kcc");
			std::ifstream in("esp_misc_hp_bar.kcc");
			void save() {
				out << main_bg.Value.x << '\n'
					<< main_bg.Value.y << '\n'
					<< main_bg.Value.z << '\n'
					<< main_bg.Value.w << '\n'
					<< bottom_bg.Value.x << '\n'
					<< bottom_bg.Value.y << '\n'
					<< bottom_bg.Value.z << '\n'
					<< bottom_bg.Value.w << '\n'
					<< top_bg.Value.x << '\n'
					<< top_bg.Value.y << '\n'
					<< top_bg.Value.z << '\n'
					<< top_bg.Value.w << '\n'
					<< grid.Value.x << '\n'
					<< grid.Value.y << '\n'
					<< grid.Value.z << '\n'
					<< grid.Value.w << '\n';
			}

			void load() {
				in  >> main_bg.Value.x 
					>> main_bg.Value.y
					>> main_bg.Value.z
					>> main_bg.Value.w
					>> bottom_bg.Value.x
					>> bottom_bg.Value.y
					>> bottom_bg.Value.z
					>> bottom_bg.Value.w
					>> top_bg.Value.x
					>> top_bg.Value.y
					>> top_bg.Value.z
					>> top_bg.Value.w
					>> grid.Value.x
					>> grid.Value.y
					>> grid.Value.z
					>> grid.Value.w;
			}
		}

		void save_cfg() {
			bg::save();
		}

		void load_cfg() {
			bg::load();
		}
	}

	namespace esp {
		namespace BOXESP_STYLE
		{
			int Box2d = 0, Box3d = 1, Corners = 2;
		}

		namespace BOXESP_SUBSTYLE
		{
			int Bordered = 0, Nothing = 1;
		}

		namespace TEXT_STYLE
		{
			int Bordered = 0, Nothing = 1;
		}

		namespace INFO_POSITION
		{
			int Top = 0, Right = 1, Bottom = 2, Left = 3, TopLeft = 4, BottomLeft = 5, BottomRight = 6, TopRight = 7;
		}

		namespace LINE_STYLE  {
			int Bordered = 0, Nothing = 1;
		}

		namespace HEALTHBAR_STYLE  {
			int Bordered = 0, DoubleBordered = 1, Nothing = 2;
		}

		bool dormant = false;

		namespace box {
			int style = BOXESP_STYLE::Corners;
			int substyle = BOXESP_SUBSTYLE::Bordered;

			ImColor inner_color = ImColor(40, 100, 120);
			ImColor outer_color = ImColor(0, 0, 0);

			bool enabled = false;


			std::ofstream out("esp_box.kcc");
			std::ifstream in("esp_box.kcc");
			void save() {
				out << style << '\n'
					<< substyle << '\n'
					<< inner_color.Value.x << '\n'
					<< inner_color.Value.y << '\n'
					<< inner_color.Value.z << '\n'
					<< inner_color.Value.w << '\n'
					<< outer_color.Value.x << '\n'
					<< outer_color.Value.y << '\n'
					<< outer_color.Value.z << '\n'
					<< outer_color.Value.w << '\n'
					<< enabled;
			}

			void load() {
				in >> style
					>> substyle
					>> inner_color.Value.x
					>> inner_color.Value.y
					>> inner_color.Value.z
					>> inner_color.Value.w
					>> outer_color.Value.x
					>> outer_color.Value.y
					>> outer_color.Value.z
					>> outer_color.Value.w
					>> enabled;
			}
		}

		namespace ebox {
			int style = BOXESP_STYLE::Corners;
			int substyle = BOXESP_SUBSTYLE::Bordered;

			ImColor inner_color = ImColor(40, 100, 120);
			ImColor outer_color = ImColor(0, 0, 0);

			bool enabled = false;
			bool dormant = false;
										
			std::ofstream out("esp_box.kcc");
			std::ifstream in("esp_box.kcc");
			void save() {
				out << style << '\n'
					<< substyle << '\n'
					<< inner_color.Value.x << '\n'
					<< inner_color.Value.y << '\n'
					<< inner_color.Value.z << '\n'
					<< inner_color.Value.w << '\n'
					<< outer_color.Value.x << '\n'
					<< outer_color.Value.y << '\n'
					<< outer_color.Value.z << '\n'
					<< outer_color.Value.w << '\n'
					<< enabled;
			}

			void load() {
				in >> style
					>> substyle
					>> inner_color.Value.x
					>> inner_color.Value.y
					>> inner_color.Value.z
					>> inner_color.Value.w
					>> outer_color.Value.x
					>> outer_color.Value.y
					>> outer_color.Value.z
					>> outer_color.Value.w
					>> enabled;
			}
		}

		namespace info {
			namespace name {
				ImColor inner_color(5, 152, 206);
				ImColor outer_color(85, 85, 85);

				long int style = TEXT_STYLE::Bordered;
				bool enabled = false;

				long int position = INFO_POSITION::Top;

				std::ofstream out("esp_info_name.kcc");
				std::ifstream in("esp_info_name.kcc");
				void save() {
					out << style << '\n'
						<< inner_color.Value.x << '\n'
						<< inner_color.Value.y << '\n'
						<< inner_color.Value.z << '\n'
						<< inner_color.Value.w << '\n'
						<< outer_color.Value.x << '\n'
						<< outer_color.Value.y << '\n'
						<< outer_color.Value.z << '\n'
						<< outer_color.Value.w << '\n'
						<< enabled
						<< position;
				}

				void load() {
					in >> style
						>> inner_color.Value.x
						>> inner_color.Value.y
						>> inner_color.Value.z
						>> inner_color.Value.w
						>> outer_color.Value.x
						>> outer_color.Value.y
						>> outer_color.Value.z
						>> outer_color.Value.w
						>> enabled
						>> position;
				}

			}

			namespace hp_num {
				ImColor inner_color(5, 152, 206);
				ImColor outer_color(85, 85, 85);

				long int style = TEXT_STYLE::Bordered;
				bool enabled = false;

				long int position = INFO_POSITION::Bottom;

				std::ofstream out("esp_info_hp_num.kcc");
				std::ifstream in("esp_info_hp_num.kcc");
				void save() {
					out << style << '\n'
						<< inner_color.Value.x << '\n'
						<< inner_color.Value.y << '\n'
						<< inner_color.Value.z << '\n'
						<< inner_color.Value.w << '\n'
						<< outer_color.Value.x << '\n'
						<< outer_color.Value.y << '\n'
						<< outer_color.Value.z << '\n'
						<< outer_color.Value.w << '\n'
						<< enabled
						<< position;
				}

				void load() {
					in >> style
						>> inner_color.Value.x
						>> inner_color.Value.y
						>> inner_color.Value.z
						>> inner_color.Value.w
						>> outer_color.Value.x
						>> outer_color.Value.y
						>> outer_color.Value.z
						>> outer_color.Value.w
						>> enabled
						>> position;
				}
			}

			namespace weapon {
				ImColor inner_color(5, 152, 206);
				ImColor outer_color(85, 85, 85);

				long int style = TEXT_STYLE::Bordered;
				bool enabled = false;

				long int position = INFO_POSITION::Bottom;

				std::ofstream out("esp_info_weapon.kcc");
				std::ifstream in("esp_info_weapon.kcc");
				void save() {
					out << style << '\n'
						<< inner_color.Value.x << '\n'
						<< inner_color.Value.y << '\n'
						<< inner_color.Value.z << '\n'
						<< inner_color.Value.w << '\n'
						<< outer_color.Value.x << '\n'
						<< outer_color.Value.y << '\n'
						<< outer_color.Value.z << '\n'
						<< outer_color.Value.w << '\n'
						<< enabled
						<< position;
				}

				void load() {
					in >> style
						>> inner_color.Value.x
						>> inner_color.Value.y
						>> inner_color.Value.z
						>> inner_color.Value.w
						>> outer_color.Value.x
						>> outer_color.Value.y
						>> outer_color.Value.z
						>> outer_color.Value.w
						>> enabled
						>> position;
				}
			}

			namespace distance {
				ImColor inner_color(5, 152, 206);
				ImColor outer_color(85, 85, 85);

				long int style = TEXT_STYLE::Bordered;
				bool enabled = false;

				int decimals = 0;
				long int position = INFO_POSITION::Bottom;

				std::ofstream out("esp_info_distance.kcc");
				std::ifstream in("esp_info_distance.kcc");
				void save() {
					out << style << '\n'
						<< inner_color.Value.x << '\n'
						<< inner_color.Value.y << '\n'
						<< inner_color.Value.z << '\n'
						<< inner_color.Value.w << '\n'
						<< outer_color.Value.x << '\n'
						<< outer_color.Value.y << '\n'
						<< outer_color.Value.z << '\n'
						<< outer_color.Value.w << '\n'
						<< enabled
						<< position
						<< decimals;
				}

				void load() {
					in >> style
						>> inner_color.Value.x
						>> inner_color.Value.y
						>> inner_color.Value.z
						>> inner_color.Value.w
						>> outer_color.Value.x
						>> outer_color.Value.y
						>> outer_color.Value.z
						>> outer_color.Value.w
						>> enabled
						>> position
						>> decimals;
				}
			}

			namespace rank {
				ImColor inner_color(5, 152, 206);
				ImColor outer_color(85, 85, 85);

				long int style = TEXT_STYLE::Bordered;
				bool enabled = false;
				long int position = INFO_POSITION::TopRight;

				std::ofstream out("esp_info_rank.kcc");
				std::ifstream in("esp_info_rank.kcc");
				void save() {
					out << style << '\n'
						<< inner_color.Value.x << '\n'
						<< inner_color.Value.y << '\n'
						<< inner_color.Value.z << '\n'
						<< inner_color.Value.w << '\n'
						<< outer_color.Value.x << '\n'
						<< outer_color.Value.y << '\n'
						<< outer_color.Value.z << '\n'
						<< outer_color.Value.w << '\n'
						<< enabled
						<< position;
				}

				void load() {
					in >> style
						>> inner_color.Value.x
						>> inner_color.Value.y
						>> inner_color.Value.z
						>> inner_color.Value.w
						>> outer_color.Value.x
						>> outer_color.Value.y
						>> outer_color.Value.z
						>> outer_color.Value.w
						>> enabled
						>> position;
				}
			}

			namespace hack_ranks { //such as [NIGERIAN] - represents if player has the same cheat loaded and [STEAM FRIEND]
				ImColor inner_color(5, 152, 206);
				ImColor outer_color(85, 85, 85);

				long int style = TEXT_STYLE::Bordered;
				bool enabled = false;
				long int position = INFO_POSITION::Bottom;

				std::ofstream out("esp_info_hack_ranks.kcc");
				std::ifstream in("esp_info_hack_ranks.kcc");
				void save() {
					out << style << '\n'
						<< inner_color.Value.x << '\n'
						<< inner_color.Value.y << '\n'
						<< inner_color.Value.z << '\n'
						<< inner_color.Value.w << '\n'
						<< outer_color.Value.x << '\n'
						<< outer_color.Value.y << '\n'
						<< outer_color.Value.z << '\n'
						<< outer_color.Value.w << '\n'
						<< enabled
						<< position;
				}

				void load() {
					in >> style
						>> inner_color.Value.x
						>> inner_color.Value.y
						>> inner_color.Value.z
						>> inner_color.Value.w
						>> outer_color.Value.x
						>> outer_color.Value.y
						>> outer_color.Value.z
						>> outer_color.Value.w
						>> enabled
						>> position;
				}
			}
		}

		namespace misc {
			namespace trace {
				ImColor color(5, 152, 206);
				long int style = LINE_STYLE::Bordered;

				std::ofstream out("esp_misc_trace.kcc");
				std::ifstream in("esp_misc_trace.kcc");
				void save() {
					out << style << '\n'
						<< color.Value.x << '\n'
						<< color.Value.y << '\n'
						<< color.Value.z << '\n'
						<< color.Value.w << '\n';
				}

				void load() {
					in  >> style
						>> color.Value.x
						>> color.Value.y
						>> color.Value.z
						>> color.Value.w;
				}
			}

			namespace hp_bar {
				ImColor color(0, 255, 0);
				long int style = HEALTHBAR_STYLE::DoubleBordered;

				std::ofstream out("esp_misc_hp_bar.kcc");
				std::ifstream in("esp_misc_hp_bar.kcc");
				void save() {
					out << style << '\n'
						<< color.Value.x << '\n'
						<< color.Value.y << '\n'
						<< color.Value.z << '\n'
						<< color.Value.w << '\n';
				}

				void load() {
					in >> style
						>> color.Value.x
						>> color.Value.y
						>> color.Value.z
						>> color.Value.w;
				}
			}
		}

		void save_cfg() {
			box::save();
			info::name::save();
			info::hp_num::save();
			info::weapon::save();
			info::distance::save();
			info::rank::save();
			info::hack_ranks::save();
			misc::trace::save();
			misc::hp_bar::save();
		}

		void load_cfg() {
			box::load();
			info::name::load();
			info::hp_num::load();
			info::weapon::load();
			info::distance::load();
			info::rank::load();
			info::hack_ranks::load();
			misc::trace::load();
			misc::hp_bar::load();
		}
	}

	namespace aimbot {
		bool enabled = true;
		float speed = 1.f;
		unsigned int n_pivots = 3;
		float bezier_intensity = 0.2f;
	}

	namespace other {

	}
}