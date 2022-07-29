#pragma once

#include "windows.h"

#include <string>
#include <fstream>

#include <D2D1.h>

#include "sdk/client/C_BasePlayer.h"

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>
#include <comdef.h>


#include "imgui-1.88/imgui.h"
#include "imgui-1.88/backends/imgui_impl_dx11.h"

#include "imgui-1.88/backends/imgui_impl_dx9.h"
#include <d3dx9.h>
#include <d3d9.h>

#include "imgui-1.88/backends/imgui_impl_win32.h"
#ifdef _DEBUG
#include <iostream>
#include <fstream>
#endif



namespace core {


	namespace hijack {

		DWORD pid;
		HWND handle;

		IDXGISwapChain* swap_chain;
		ID3D11Device* device;
		ID3D11DeviceContext* device_con;
		ID3D11RenderTargetView* render_target;
		ID3D11Buffer* square_index_buffer;
		ID3D11DepthStencilView* depth_stencil_view;
		ID3D11Texture2D* depth_stencil_buffer;
		ID3D11Buffer* vertex_buffer;
		ID3D11VertexShader* vertex_shader;
		ID3D11PixelShader* pixel_shader;
		ID3D10Blob* vs_buffer;
		ID3D10Blob* ps_buffer;
		ID3D11InputLayout* vertex_layout;
		ID3D11Buffer* object_buffer;
		ID3D11RasterizerState* raster_state;

		ID2D1HwndRenderTarget* hwrt;
		DWORD hr;
		/*MOVE THIS*/
		struct Vertex {
			Vertex() {}
			Vertex(float x, float y, float z, float cr, float cg, float cb, float ca) : pos(x, y, z), color(cr, cg, cb, ca) {}
			XMFLOAT3 pos;
			XMFLOAT4 color;
		};

		D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout);

		XMMATRIX WVP;
		XMMATRIX cube1_world;
		XMMATRIX cube2_world;
		XMMATRIX cam_view;
		XMMATRIX cam_projection;

		XMVECTOR cam_position;
		XMVECTOR cam_target;
		XMVECTOR cam_up;

		XMMATRIX rotation;
		XMMATRIX scale;
		XMMATRIX translation;
		float rot = 0.01f;

		std::size_t screen_width, screen_height;

		/*END*/
		const char* shader = "cbuffer cbPerObject{ float4x4 WVP; };\n"
			"    struct VS_OUTPUT {\n"
			"    float4 Pos : SV_POSITION;\n"
			"    float4 Color : COLOR;\n"
			"};\n"
			"VS_OUTPUT VS(float4 inPos : POSITION, float4 inColor : COLOR) {\n"
			"    VS_OUTPUT output;\n"
			"    output.Pos = mul(inPos, WVP);\n"
			"    output.Color = inColor;\n"
			"    return output;\n"
			"}\n"
			"float4 PS(VS_OUTPUT input) : SV_TARGET{return input.Color;}";

		struct cbPerObject { XMMATRIX  WVP; };

		cbPerObject cb_per_object;
		bool imgui_initalized = false;
		void start_notepad() {
			std::ofstream esp_file("overlay_khak_balex_trollface.txt");

			system("start notepad overlay_khak_balex_trollface.txt");
			Sleep(500);
		}

		std::ofstream log("log.txt");

		void find_notepad() {
			WCHAR title[1024];
			for (HWND hwnd = GetTopWindow(NULL); hwnd != NULL; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT))
			{
				if (!IsWindowVisible(hwnd))
					continue;

				int length = GetWindowTextLength(hwnd) + 1;
				if (length == 1)
					continue;

				GetWindowText(hwnd, title, length);

				if (wcsstr(title, L"overlay_khak_balex_trollface")) {
					handle = hwnd;
					return;
				}

			}

		}

		void modify_notepad() {
			SetMenu(handle, NULL);
			SetWindowLongPtr(handle, GWL_STYLE, WS_VISIBLE);
			SetWindowLongPtr(handle, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW); // WS_EX_NOACTIVATE  and WS_EX_TOOLWINDOW removes it from taskbar
			//SetWindowPos(handle, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW); // DX fails to init if I do that here for some reason

			// Quick and dirty transparency
			SetLayeredWindowAttributes(handle, RGB(0, 0, 0), 0, LWA_COLORKEY);
		}

		void create_d2d1() {

			ID2D1Factory* factory;

			D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

			RECT rc;
			GetClientRect(handle, &rc);

			D2D1_SIZE_U size = D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top
			);

			// Create a Direct2D render target.
			if (factory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(handle, size),
				&hwrt
			) != S_OK) {
				//log << L"WE ARE FUCK\n";
			}

		}

		void init_d3d11() {
			RECT rc;
			GetClientRect(handle, &rc);

			D2D1_SIZE_U size = D2D1::SizeU(
				rc.right/1 - rc.left/1,
				rc.bottom/1 - rc.top/1
			);

			DXGI_MODE_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
			bufferDesc.Width = screen_width;
			bufferDesc.Height = screen_height;
			bufferDesc.RefreshRate.Numerator = 60;
			bufferDesc.RefreshRate.Denominator = 1;
			bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			//bufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
			bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

			//Describe our SwapChain
			DXGI_SWAP_CHAIN_DESC swapChainDesc;
			ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
			swapChainDesc.BufferDesc = bufferDesc;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = 1;
			swapChainDesc.OutputWindow = handle; // hwnd
			swapChainDesc.Windowed = true;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			//Create our SwapChain
			hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, &swap_chain, &device, NULL, &device_con);

			//Create our BackBuffer
			ID3D11Texture2D* BackBuffer;
			hr = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

			//Create our Render Target
			hr = device->CreateRenderTargetView(BackBuffer, NULL, &render_target);
			BackBuffer->Release();

			//Describe our Depth/Stencil Buffer
			D3D11_TEXTURE2D_DESC depthStencilDesc;
			depthStencilDesc.Width = screen_width;
			depthStencilDesc.Height = screen_height;
			depthStencilDesc.MipLevels = 1;
			depthStencilDesc.ArraySize = 1;
			depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
			depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
			depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilDesc.CPUAccessFlags = 0;
			depthStencilDesc.MiscFlags = 0;

			//Create the Depth/Stencil View
			device->CreateTexture2D(&depthStencilDesc, NULL, &depth_stencil_buffer);
			device->CreateDepthStencilView(depth_stencil_buffer, NULL, &depth_stencil_view);

			//Set our Render Target
			device_con->OMSetRenderTargets(1, &render_target, depth_stencil_view);
		}

		void cleanup() {
			//Release the COM Objects we created
			swap_chain->Release();
			device->Release();
			device_con->Release();
			render_target->Release();
			vertex_buffer->Release();
			square_index_buffer->Release();
			vertex_shader->Release();
			pixel_shader->Release();
			vs_buffer->Release();
			ps_buffer->Release();
			vertex_layout->Release();
			depth_stencil_view->Release();
			depth_stencil_buffer->Release();
			object_buffer->Release();
			raster_state->Release();
		}

		void init_scene() {
			RECT rc;
			GetClientRect(handle, &rc);

			D2D1_SIZE_U size = D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top
			);

			hr = D3DX11CompileFromMemory(shader, strlen(shader), 0, 0, 0, "VS", "vs_4_0", 0, 0, 0, &vs_buffer, 0, 0);
			hr = D3DX11CompileFromMemory(shader, strlen(shader), 0, 0, 0, "PS", "ps_4_0", 0, 0, 0, &ps_buffer, 0, 0);

			//Create the Shader Objects
			hr = device->CreateVertexShader(vs_buffer->GetBufferPointer(), vs_buffer->GetBufferSize(), NULL, &vertex_shader);
			hr = device->CreatePixelShader(ps_buffer->GetBufferPointer(), ps_buffer->GetBufferSize(), NULL, &pixel_shader);

			//Set Vertex and Pixel Shaders
			device_con->VSSetShader(vertex_shader, 0, 0);
			device_con->PSSetShader(pixel_shader, 0, 0);

			//Create the vertex buffer
			Vertex v[] = {
				Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
				Vertex(-1.0f, +1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f),
				Vertex(+1.0f, +1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
				Vertex(+1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
				Vertex(-1.0f, -1.0f, +1.0f, 0.0f, 1.0f, 1.0f, 1.0f),
				Vertex(-1.0f, +1.0f, +1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
				Vertex(+1.0f, +1.0f, +1.0f, 1.0f, 0.0f, 1.0f, 1.0f),
				Vertex(+1.0f, -1.0f, +1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
			};

			DWORD indices[] = {
				// front face
				0, 1, 2,
				0, 2, 3,

				// back face
				4, 6, 5,
				4, 7, 6,

				// left face
				4, 5, 1,
				4, 1, 0,

				// right face
				3, 2, 6,
				3, 6, 7,

				// top face
				1, 5, 6,
				1, 6, 2,

				// bottom face
				4, 0, 3,
				4, 3, 7
			};

			D3D11_BUFFER_DESC indexBufferDesc;
			ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
			indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			indexBufferDesc.ByteWidth = sizeof(DWORD) * 12 * 3;
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexBufferDesc.CPUAccessFlags = 0;
			indexBufferDesc.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA iinitData;
			iinitData.pSysMem = indices;
			device->CreateBuffer(&indexBufferDesc, &iinitData, &square_index_buffer);

			device_con->IASetIndexBuffer(square_index_buffer, DXGI_FORMAT_R32_UINT, 0);

			D3D11_BUFFER_DESC vertexBufferDesc;
			ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
			vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			vertexBufferDesc.ByteWidth = sizeof(Vertex) * 8;
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags = 0;
			vertexBufferDesc.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA vertexBufferData;
			ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
			vertexBufferData.pSysMem = v;
			hr = device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertex_buffer);

			//Set the vertex buffer
			UINT stride = sizeof(Vertex);
			UINT offset = 0;
			device_con->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);

			//Create the Input Layout
			hr = device->CreateInputLayout(layout, numElements, vs_buffer->GetBufferPointer(), vs_buffer->GetBufferSize(), &vertex_layout);

			//Set the Input Layout
			device_con->IASetInputLayout(vertex_layout);

			//Set Primitive Topology
			device_con->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			//Create the Viewport
			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = screen_width;
			viewport.Height = screen_height;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;

			//Set the Viewport
			device_con->RSSetViewports(1, &viewport);

			//Create the buffer to send to the cbuffer in effect file
			D3D11_BUFFER_DESC cbbd;
			ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));
			cbbd.Usage = D3D11_USAGE_DEFAULT;
			cbbd.ByteWidth = sizeof(cbPerObject);
			cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbbd.CPUAccessFlags = 0;
			cbbd.MiscFlags = 0;
			hr = device->CreateBuffer(&cbbd, NULL, &object_buffer);
			/*log << hr << std::endl;
			_com_error err(hr);
			LPCTSTR errMsg = err.ErrorMessage();
			log << errMsg << std::endl;*/
			//Camera information
			cam_position = XMVectorSet(0.0f, 3.0f, -8.0f, 0.0f);
			cam_target = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			cam_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

			//Set the View matrix
			cam_view = XMMatrixLookAtLH(cam_position, cam_target, cam_up);

			//Set the Projection matrix
			cam_projection = XMMatrixPerspectiveFovLH(0.4f * 3.14f, (float)screen_width / screen_width, 1.0f, 1000.0f);


			D3D11_RASTERIZER_DESC wfdesc;
			ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
			wfdesc.FillMode = D3D11_FILL_WIREFRAME;
			wfdesc.CullMode = D3D11_CULL_NONE;
			hr = device->CreateRasterizerState(&wfdesc, &raster_state);

			device_con->RSSetState(raster_state);

			cube1_world = XMMatrixIdentity();
		}

		void scene_update() {
			//cube1_world = XMMatrixIdentity();
		}

		void init_imgui() {

			if (imgui_initalized) return;

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::StyleColorsDark();
			ImGui_ImplWin32_Init(handle);
			ImGui_ImplDX11_Init(device,device_con);
			
			imgui_initalized = true;
		}

		void init_imgui_dx9(HANDLE handle, IDirect3DDevice9* device ) {

			if (imgui_initalized) return;

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::StyleColorsDark();
			ImGui_ImplWin32_Init(handle);
			ImGui_ImplDX9_Init(device);

			imgui_initalized = true;
		}

		float bgColor[4] = { (0.0f, 0.0f, 0.0f, 0.0f) };
		void draw_scene() {
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			for (int i = 0; i < iface::cl_entity_list->GetHighestEntityIndex(); ++i) {
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

				ImGui::GetBackgroundDrawList()->AddRect({ pos.x-5,pos.y-5 }, { pos.x+5,pos.y+5 },
					ImGui::ColorConvertFloat4ToU32(
						ImVec4(255 / 255.0, 120 / 255.0, 0 / 255.0, 1)), 1);
			}

		
			ImGui::Render();

			device_con->ClearRenderTargetView(render_target, bgColor);

			
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
			swap_chain->Present(0, 0);
		}

		void loop() {
			scene_update();
			draw_scene();
		}

		void execute() {
			RECT desktop;
			const HWND hDesktop = GetDesktopWindow();
			GetWindowRect(hDesktop, &desktop);
			screen_width = desktop.right;
			screen_height = desktop.bottom;

			start_notepad();
			find_notepad();
			modify_notepad();
			init_d3d11();
			init_scene();
			init_imgui();

			/*Sleep(100);
			SetWindowPos(handle, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);
			Sleep(100);
			while (true) {
				loop();
				Sleep(16);
			}*/

		}
	}

}////Refresh the Depth/Stencil view
			//device_con->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

			////Set the WVP matrix and send it to the constant buffer in effect file
			//WVP = cube1_world * cam_view * cam_projection;
			//cb_per_object.WVP = XMMatrixTranspose(WVP);
			//device_con->UpdateSubresource(object_buffer, 0, NULL, &cb_per_object, 0, 0);
			//device_con->VSSetConstantBuffers(0, 1, &object_buffer);

			////Draw the first cube
			//device_con->DrawIndexed(36, 0, 0);