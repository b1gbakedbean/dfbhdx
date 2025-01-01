#pragma once
#include "component.hpp"

namespace dfbhdx::components
{
	enum DispatcherCallbackType
	{
		DispatcherCallbackType_Logic,
		DispatcherCallbackType_Render
	};

	struct DispatcherCallback
	{
		DispatcherCallbackType type;
		std::function<void(int)> function;
	};

	class dispatcher : public component
	{
	public:
		virtual void load();
		virtual void unload();

		static void add_callback(DispatcherCallbackType type, std::function<void(int)> callback);
		static std::vector<DispatcherCallback> get_callbacks();

	private:
		static inline std::vector<DispatcherCallback> _callbacks;
	};
}