#pragma once
#include "component.hpp"

namespace dfbhdx::components
{
	class misc : public component
	{
	public:
		virtual void load();
		virtual void unload();
	};
}