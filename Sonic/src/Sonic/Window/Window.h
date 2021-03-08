#pragma once
#include "Sonic/Graphics/Color.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "WindowInfo.h"


struct HWND__;

namespace Sonic {

	namespace Cursors {

		const String Arrow = "arrow";
		const String Alternate = "alternate";
		const String IBeam = "ibeam";
		const String Move = "move";
		const String Crosshair = "crosshair";
		const String ResizeHorizontal = "resize_horizontal";
		const String ResizeVertical = "resize_vertical";
		const String ResizeDiagonalLeft = "resize_diagonal_left";
		const String ResizeDiagonalRight = "resize_diagonal_right";
		const String Unavailable = "unavailable";
		const String Pen = "pen";
		const String Link = "link";
		const String Help = "help";

	}

	class Window
	{
	private:
		Window() = delete;
		Window(const Window& other) = delete;
		Window& operator=(const Window& other) = delete;

		static bool createWin32Window();
		static void onResized(int width, int height);
		static void onMouseButtonPressed(MouseButton button);
		static void onMouseButtonReleased(MouseButton button);
		static __int64 __stdcall WindowProc(HWND__* handle, unsigned int msg, unsigned __int64 wParam, __int64 lParam);

		static bool createContext();
	public:
		static bool init(const WindowInfo& info);
		static bool init(const String& infoFilePath, bool overrideBinary = false);

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

		static void setMaximized(bool b);
		static void setMinimized(bool b);

		static bool isMinimized();
		static bool isMaximized();

		static float getMonitorWidth();
		static float getMonitorHeight();

		static void setWindowMode(WindowMode mode);
		static WindowMode getWindowMode();

		static double getTime();
	};

}
