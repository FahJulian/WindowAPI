#pragma once
#include <Sonic/Event/EventDispatcher.h>
#include "Sonic/Graphics/Color.h"
#include "Input/Mouse.h"
#include "WindowInfo.h"
#include "WindowInfoLoader.h"

#ifndef SONIC_EVENT_FN
	#define SONIC_EVENT_FN(e) EventDispatcher::dispatch(e)
#endif

struct HWND__;

namespace Sonic {

	namespace StandardCursors {

		const String Arrow = "Arrow";
		const String Alternate = "Alternate";
		const String IBeam = "IBeam";
		const String Move = "Move";
		const String Crosshair = "Crosshair";
		const String ResizeHorizontal = "ResizeHorizontal";
		const String ResizeVertical = "ResizeVertical";
		const String ResizeDiagonalLeft = "ResizeDiagonalLeft";
		const String ResizeDiagonalRight = "ResizeDiagonalRight";
		const String Unavailable = "Unavailable";
		const String Pen = "Pen";
		const String Link = "Link";
		const String Help = "Help";

	}

	class Window
	{
	private:
		Window() = delete;
		Window(const Window& other) = delete;
		Window& operator=(const Window& other) = delete;

		static void onResized(int width, int height, bool minimized);
		static void onMouseButtonPressed(MouseButton button);
		static void onMouseButtonReleased(MouseButton button);
		static __int64 __stdcall WindowProc(HWND__* handle, unsigned int msg, unsigned __int64 wParam, __int64 lParam);

		static void createContext();
	public:
		static Window* get();

		static bool init(const WindowInfo& info);
		static bool init(const String& infoFilePath, bool overrideBinary = false) { return init(Util::loadWindowInfo(infoFilePath, overrideBinary)); }

		static void saveInfo();
		static void destroy();

		static void pollEvents();

		static void clear();
		static void swapBuffers();

		static void setClearColor(const Color& color);

		static void setCursor(const String& cursorName);

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
