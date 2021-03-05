#pragma once
#include <Sonic/Event/EventDispatcher.h>
#include "Sonic/Graphics/Color.h"
#include "Input/Mouse.h"
#include "_WIN32Include.h"
#include "WindowInfo.h"
#include "WindowInfoLoader.h"

#ifndef SONIC_EVENT_FN
	#define SONIC_EVENT_FN(e) EventDispatcher::dispatch(e)
#endif

namespace Sonic {

	class Window
	{
	private:
		Window() = delete;
		Window(const Window& other) = delete;
		Window& operator=(const Window& other) = delete;

		static void onResized(int width, int height, bool minimized);
		static void onMouseButtonPressed(MouseButton button);
		static void onMouseButtonReleased(MouseButton button);
		static LRESULT CALLBACK WindowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);

		static void createContext();

	public:
		static bool init(const WindowInfo& info);
		static bool init(const String& infoFilePath, bool overrideBinary = false) { return init(Util::loadWindowInfo(infoFilePath, overrideBinary)); }

		static void saveInfo();
		static void destroy();

		static void pollEvents();

		static void clear();
		static void swapBuffers();

		static void setClearColor(const Color& color);

		static void setTitle(String title);
		static String getTitle();

		static void setWidth(float width);
		static void setHeight(float height);
		static void setSize(float width, float height);
		static float getWidth();
		static float getHeight();

		static void setWindowMode(WindowMode mode);

		static double getTime();
	};

}
