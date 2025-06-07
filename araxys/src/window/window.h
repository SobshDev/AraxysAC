#ifndef WINDOW_H
#define WINDOW_H

#include <dwmapi.h>
#include <d3d11.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx11.h>

#include <windows.h>
#include <iostream>
#include <stdexcept>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK windowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, message, wParam, lParam))
		return (0);

	if (message == WM_DESTROY) {
		PostQuitMessage(0);
		return (0);
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

class Window {
private:
	WNDCLASSEXW windowClass = {};
	HWND hwnd = nullptr;

	RECT clientArea{}, windowArea = {};
	POINT diff = {};
	MARGINS margins = {};
	DXGI_SWAP_CHAIN_DESC sd = {};

	const D3D_FEATURE_LEVEL levels[2]{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0
	};

	ID3D11Device* device{ nullptr };
	ID3D11DeviceContext* deviceContext{ nullptr };
	IDXGISwapChain* swapChain{ nullptr };
	ID3D11RenderTargetView* renderTargetView{ nullptr };
	D3D_FEATURE_LEVEL level{};
	ID3D11Texture2D* backBuffer{ nullptr };

	bool running = false;

public:
	Window(HINSTANCE instance, INT cmd_show) {
		windowClass.cbSize = sizeof(WNDCLASSEXW);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = windowProcedure;
		windowClass.hInstance = instance;
		windowClass.lpszClassName = L"External Overlay";

		if (!RegisterClassExW(&windowClass)) {
			MessageBoxW(nullptr, L"Failed to register window class", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		hwnd = CreateWindowExW(
			WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
			windowClass.lpszClassName,
			L"External Overlay",
			WS_POPUP,
			0, 0, 1920, 1080,
			nullptr, nullptr,
			windowClass.hInstance, nullptr
		);

		if (!hwnd) {
			MessageBoxW(nullptr, L"Failed to create window", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), BYTE(255), LWA_ALPHA);
		GetClientRect(hwnd, &clientArea);
		GetWindowRect(hwnd, &windowArea);
		ClientToScreen(hwnd, &diff);
		margins = {
			windowArea.left + (diff.x - windowArea.left),
			windowArea.top + (diff.y - windowArea.top),
			clientArea.right,
			clientArea.bottom
		};
		DwmExtendFrameIntoClientArea(hwnd, &margins);

		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.SampleDesc.Count = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 2;
		sd.OutputWindow = hwnd;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, levels, 2,
			D3D11_SDK_VERSION, &sd, &swapChain, &device, &level, &deviceContext
		);

		if (FAILED(hr)) {
			MessageBoxW(nullptr, L"Failed to create D3D11 device", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		if (FAILED(hr) || !backBuffer) {
			MessageBoxW(nullptr, L"Failed to get back buffer", L"Error", MB_OK | MB_ICONERROR);
			return;
		}

		hr = device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
		if (FAILED(hr)) {
			MessageBoxW(nullptr, L"Failed to create render target view", L"Error", MB_OK | MB_ICONERROR);
			backBuffer->Release();
			return;
		}

		backBuffer->Release();

		ShowWindow(hwnd, cmd_show);
		UpdateWindow(hwnd);

		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX11_Init(device, deviceContext);

		running = true;
	}

	~Window() {
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		if (swapChain)
			swapChain->Release();
		if (deviceContext)
			deviceContext->Release();
		if (device)
			device->Release();
		if (renderTargetView)
			renderTargetView->Release();
		if (hwnd)
			DestroyWindow(hwnd);
		UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);
	}

	int Run() {
		if (!running) {
			return 1;
		}

		while (running) {
			MSG msg;
			while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if (msg.message == WM_QUIT)
					running = false;
			}
			if (!running)
				break;

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();

			ImGui::NewFrame();

			RenderUI();

			ImGui::Render();

			constexpr float color[4] = { 0.f, 0.f, 0.f, 0.f };
			deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
			deviceContext->ClearRenderTargetView(renderTargetView, color);

			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

			swapChain->Present(1, 0);
		}

		return 0;
	}

	virtual void RenderUI() {
	}

	void Stop() {
		running = false;
	}

	bool IsRunning() const {
		return running;
	}
};

#endif // WINDOW_H