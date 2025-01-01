#include "component_loader.hpp"

namespace dfbhdx
{
	void component_loader::load_components()
	{
		for (const auto& component : _components)
		{
			component->load();
		}

		SPDLOG_DEBUG("Loaded {} component(s)", _components.size());
	}

	void component_loader::unload_components()
	{
		for (const auto& component : _components)
		{
			component->unload();
		}

		SPDLOG_DEBUG("Unloaded {} component(s)", _components.size());
	}
}