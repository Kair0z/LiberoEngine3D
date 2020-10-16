#pragma once
#include "Libero/ECS/Core/System.h"

namespace Libero
{
	class SysInput final : public System<SysInput>
	{
	public:
		void OnEvent(IEvent& e) override;
	};
}


