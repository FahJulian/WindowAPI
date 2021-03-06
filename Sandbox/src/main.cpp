#include <iostream>
#include <Sonic/Event/EventDispatcher.h>
#include "Sonic/Util/StringUtils.h"
#include "Sonic/Event/Events/KeyEvents.h"
#include "Sonic/Event/Events/MouseEvents.h"
#include "Sonic/Event/Events/WindowEvents.h"
#include "Sonic/Window/Window.h"
#include "Sonic/Window/WindowInfoLoader.h"
#include "Sonic/Window/Input/Keyboard.h"

using namespace Sonic;


bool s_Running;


void onMouseButtonPressed(const MouseButtonPressedEvent& e)
{
	if (e.button == MouseButtons::Left)
		std::cout << "Mouse button " << (int)e.button << " pressed at (" << e.x << ", " << e.y << ")" << std::endl;
}

void onMouseButtonReleased(const MouseButtonReleasedEvent& e)
{
	std::cout << "Mouse button " << (int)e.button << " released at (" << e.x << ", " << e.y << ")" << std::endl;
}

void onKeyPressed(const KeyPressedEvent& e)
{
	std::cout << "Key " << (int)e.key << " pressed (char: " << e.character << ")" << std::endl;
}

void onKeyReleased(const KeyReleasedEvent& e)
{
	static int i;

	std::cout << "Key " << (int)e.key << " released" << std::endl;

	switch (e.key)
	{
	case Keys::F1:
		Window::setSize(0, 0);
		break;
	case Keys::F2:
		Window::setWindowMode(WindowMode::Windowed);
		break;
	case Keys::F3:
		Window::setWindowMode(WindowMode::WindowedBorderless);
		break;
	case Keys::F4:
		Window::setWindowMode(WindowMode::WindowedFullscreen);
		break;
	case Keys::F5:
		Window::setWindowMode(WindowMode::Fullscreen);
		break;
	case Keys::F6:
		Window::setTitle(Util::toString(i++));
		break;
	case Keys::F7:
		Window::setWidth(Window::getWidth() + 20);
		break;
	case Keys::F8:
		Window::setWidth(Window::getWidth() - 20);
		break;
	case Keys::F9:
		Window::setHeight(Window::getHeight() + 20);
		break;
	case Keys::F10:
		Window::setHeight(Window::getHeight() - 20);
		break;
	}
}

void onWindowResized(const WindowResizedEvent& e)
{
	std::cout << "Window resized to (" << e.width << ", " << e.height << ")" << std::endl;
}

void onWindowClosed(const WindowClosedEvent& e)
{
	std::cout << "Window closed" << std::endl;
	s_Running = false;
}

void onMouseMoved(const MouseMovedEvent& e)
{
	if (Keyboard::isKeyPressed(Keys::Space))
		std::cout << "Spacebar is pressed" << std::endl;

	std::cout << "Mouse moved from (" << e.beforeX << ", " << e.beforeY << ") ";
	std::cout << "by (" << e.deltaX << ", " << e.deltaY << ") " << "to (" << e.x << ", " << e.y << ")" << std::endl;
}

void onMouseScrolled(const MouseScrolledEvent& e)
{
	std::cout << "Mouse scolled by " << e.scrollY << std::endl;
}

void onMouseDragged(const MouseDraggedEvent& e)
{
	std::cout << "Mouse dragged " << e.button << std::endl;
}

void onWindowGainedFocus(const WindowGainedFocusEvent& e)
{
	std::cout << "Window gained focus" << std::endl;
}

void onWindowLostFocus(const WindowLostFocusEvent& e)
{
	std::cout << "Window lost focus" << std::endl;
}


int main()
{
	Window::init("C:/dev/WindowAPI/Sandbox/res/app/sandboxapp.sonicwindow.json", true);

	EventDispatcher::addListener<MouseButtonPressedEvent>(onMouseButtonPressed);
	EventDispatcher::addListener<MouseButtonReleasedEvent>(onMouseButtonReleased);
	EventDispatcher::addListener<KeyPressedEvent>(onKeyPressed);
	EventDispatcher::addListener<KeyReleasedEvent>(onKeyReleased);
	EventDispatcher::addListener<MouseMovedEvent>(onMouseMoved);
	EventDispatcher::addListener<MouseScrolledEvent>(onMouseScrolled);
	EventDispatcher::addListener<WindowResizedEvent>(onWindowResized);
	EventDispatcher::addListener<WindowClosedEvent>(onWindowClosed);
	EventDispatcher::addListener<MouseDraggedEvent>(onMouseDragged);
	EventDispatcher::addListener<WindowGainedFocusEvent>(onWindowGainedFocus);
	EventDispatcher::addListener<WindowLostFocusEvent>(onWindowLostFocus);

	Window::setClearColor(Colors::Cyan);

	s_Running = true;
	while (s_Running)
	{
		Window::clear();

		Window::swapBuffers();

		Window::pollEvents();
	}

	Window::saveInfo();
	Window::destroy();
}
