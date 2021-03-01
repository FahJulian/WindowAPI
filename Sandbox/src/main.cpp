#include "Sonic/Window/Window.h"
#include "Sonic/Window/WindowInfoLoader.h"

using namespace Sonic;


bool s_Running;

int main()
{
	Window::init("C:/dev/WindowAPI/Sandbox/res/app/sandboxapp.sonicwindow.json", true);

	s_Running = true;
	while (s_Running)
	{
		Window::pollEvents();
	}
}
