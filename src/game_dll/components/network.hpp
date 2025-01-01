#pragma once
#include "component.hpp"

namespace dfbhdx::components
{
	class network : public component
	{
	public:
		virtual void load();
		virtual void unload();
	};
}