#include "app_trening.h"
#include <stdexcept>

std::wstring const app_trening::s_class_name{ L"trening Window" };


// REJESTRACJA
bool app_trening::register_class() 
{
	WNDCLASSEXW desc{};
	if (GetClassInfoExW(m_instance, s_class_name.c_str(), &desc) != 0) return true;
	desc = {.cbSize = sizeof(WNDCLASSEXW),
			.lpfnWndProc = window_proc_static,
			.hInstance = m_instance,
			.hCursor = LoadCursorW(nullptr,L"IDC_ARROW"),
			.lpszClassName = s_class_name.c_str() };
	return RegisterClassExW(&desc) != 0;
}

// TWORZENIE OKNA
HWND app_trening::create_window()
{
	return CreateWindowExW(0, s_class_name.c_str(), L"Nazwa na pasku", WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_instance, this);
}

LRESULT app_trening::window_proc_static(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	app_trening* app = nullptr;
	if (message == WM_NCCREATE)
	{
		auto p = reinterpret_cast<LPCREATESTRUCTW>(lparam);
		app = static_cast<app_trening*>(p->lpCreateParams);
		SetWindowLongPtrW(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(app));
	}
	else
	{
		app = reinterpret_cast<app_trening*>(GetWindowLongPtrW(window, GWLP_USERDATA));
	}

	if (app != nullptr)
	{
		return app->window_proc(window, message, wparam, lparam);
	}

	return DefWindowProcW(window, message, wparam, lparam);
}

// EVENTY OKNA HANDLER
LRESULT app_trening::window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		case WM_CLOSE: // klikniêcie guzika X
			DestroyWindow(window);
			return 0;

		case WM_DESTROY: // okno znika
			if (window == m_main)
				PostQuitMessage(EXIT_SUCCESS);
			return 0;

		//case WM_KEYDOWN:
		//	switch (wparam)
		//	{
		//		case VK_LEFT:
		//			return 0;
		//	}
		//	return 0;
		//case WM_LBUTTONDOWN:

	}
	return DefWindowProcW(window, message, wparam, lparam);
}

// KONSTRUKTOR
app_trening::app_trening(HINSTANCE instance) : m_instance{ instance }, m_main{}
{
	register_class();
	m_main = create_window();
}

// DZIA£ANIE APLIKACJI
int app_trening::run(int show_command)
{
	ShowWindow(m_main, show_command);
	MSG msg{};
	BOOL result = TRUE;
	while ((result = GetMessageW(&msg, nullptr, 0, 0)) != 0)
	{
		if (result == -1) return EXIT_FAILURE;

		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return EXIT_SUCCESS;
}