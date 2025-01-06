#pragma once
#include "component.hpp"

namespace dfbhdx::components
{
	class archive : public component
	{
	public:
		virtual void load();
		virtual void unload();
	};
}