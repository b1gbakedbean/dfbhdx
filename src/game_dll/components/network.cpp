#include "network.hpp"

namespace dfbhdx::components
{
	void network::load()
	{
		// Allows faster transmission of network data
		//utils::memory::set<uint8_t>(0x431959, 0xEB);
	}

	void network::unload()
	{

	}
}