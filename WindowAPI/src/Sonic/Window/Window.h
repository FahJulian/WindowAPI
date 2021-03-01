#pragma once
#include "Input/Mouse.h"
#include "_WIN32Include.h"
#include "WindowInfo.h"
#include "WindowInfoLoader.h"

namespace Sonic {

	class Window
	{
	private:
		Window() = delete;
		Window(const Window& other) = delete;
		Window& operator=(const Window& other) = delete;

		static void onMouseButtonPressed(MouseButton button);
		static void onMouseButtonReleased(MouseButton button);
		static LRESULT CALLBACK WindowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		static bool init(const WindowInfo& info);
		static bool init(const String& infoFilePath, bool overrideBinary = false) { return init(Util::loadWindowInfo(infoFilePath, overrideBinary)); }

		static void pollEvents();

		static double getTime();
	};

}
