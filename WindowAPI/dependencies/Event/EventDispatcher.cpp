#include "Sonic/Event/EventDispatcher.h"

using namespace Sonic;


std::vector<std::function<void()>> EventDispatcher::s_ClearFunctions;


void EventDispatcher::clear()
{
	for (auto& function : s_ClearFunctions)
		function();
}
