#pragma once
#include <functional>

namespace Sonic {

	template<typename Event>
	using EventListener = std::function<void(const Event&)>;

}
