#pragma once
#include "component.hpp"

namespace dfbhdx::components
{
	class rendering : public component
	{
	public:
		virtual void load();
		virtual void unload();
	};
}