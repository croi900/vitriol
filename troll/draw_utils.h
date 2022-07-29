#pragma once
#include <D2D1.h>
#include "hijack.h"
namespace core {
	namespace draw {
		ID2D1SolidColorBrush* brush;

		void initialize() {
			hijack::hwrt->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Red, 1.0f),
				&brush
			);
		}

		void set_color(int r, int g, int b, float a) {
			D2D1::ColorF clr(r/255.0, g/255.0, b/255.0, a);
			brush->SetColor(clr);
		}

		void set_color(D2D1::ColorF& clr) {
			brush->SetColor(clr);
		}

		void draw_line(float x1, float y1, float x2, float y2, int r = 255, int g = 120, int b = 0, float a = 1.f, float thickness = 0.5) {
			set_color(r, g, b, a);
			hijack::hwrt->DrawLine({ x1,y1 }, { x2,y2 }, brush, thickness);
		}

		void draw_rect(float x1, float y1, float x2, float y2, int r = 255, int g = 120, int b = 0, float a = 1.f, float thickness = 0.5) {
			set_color(r, g, b, a);
			hijack::hwrt->DrawRectangle({ x1,y1,x2,y2 }, brush, thickness);
		}

		void draw_line(float x1, float y1, float x2, float y2, D2D1::ColorF& clr, float thickness = 0.5) {
			draw_line(x1, y1, x2, y2, clr.r * 255, clr.g * 255, clr.b * 255, clr.a, thickness);
		}

		void draw_rect(float x1, float y1, float x2, float y2, D2D1::ColorF& clr, float thickness = 0.5) {
			draw_rect(x1, y1, x2, y2, clr.r * 255, clr.g * 255, clr.b * 255, clr.a, thickness);
		}

		/*void draw_brect(float x1, float y1, float x2, float y2, D2D1::ColorF& border, D2D1::ColorF& inner, float thickness = 0.25) {
			draw_rect(x1 - 1, y1 - 2, x2 + 1, y2 + 1, border, thickness);
			draw_rect(x1 - 0, y1 - 0, x2 + 0, y2 + 0, inner,  thickness);
			draw_rect(x1 + 1, y1 + 2, x2 - 1, y2 - 1, border, thickness);
		}*/

		void draw_brect(float x1, float y1, float x2, float y2, D2D1::ColorF border, D2D1::ColorF inner, float thickness = 0.25) {
			draw_rect(x1 - 1, y1 - 2, x2 + 1, y2 + 1, border, thickness);
			draw_rect(x1 - 0, y1 - 0, x2 + 0, y2 + 0, inner, thickness);
			draw_rect(x1 + 1, y1 + 2, x2 - 1, y2 - 1, border, thickness);
		}

		void draw_line(Vector& v1, Vector& v2, int r = 255, int g = 120, int b = 0, float a = 1.f, float thickness = 0.5) {
			set_color(r, g, b, a);
			hijack::hwrt->DrawLine({ v1.x,v1.y }, { v2.x,v2.y }, brush, thickness);
		}

		void draw_rect(Vector& v1, Vector& v2, int r = 255, int g = 120, int b = 0, float a = 1.f, float thickness = 0.5) {
			set_color(r, g, b, a);
			hijack::hwrt->DrawLine({ v1.x,v1.y }, { v2.x,v2.y }, brush, thickness);
		}

		void draw_line(Vector& v1, Vector& v2, D2D1::ColorF& clr, float thickness = 0.5) {
			draw_line(v1, v2, clr.r * 255, clr.g * 255, clr.b * 255, clr.a, thickness);
		}

		void draw_rect(Vector& v1, Vector& v2, D2D1::ColorF& clr, float thickness = 0.5) {
			draw_rect(v1, v2, clr.r * 255, clr.g * 255, clr.b * 255, clr.a, thickness);
		}

		/*void draw_brect(Vector& v1, Vector& v2, D2D1::ColorF& border, D2D1::ColorF& inner, float thickness = 0.25) {
			draw_brect(v1.x, v1.y, v2.x, v2.y, border, inner, thickness);
		}*/

		void draw_brect(Vector v1, Vector v2, D2D1::ColorF border, D2D1::ColorF inner, float thickness = 1) {
			draw_brect(v1.x, v1.y, v2.x, v2.y, border, inner, thickness);
		}

	}
}