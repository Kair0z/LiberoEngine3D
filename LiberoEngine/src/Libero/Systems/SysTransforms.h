#pragma once
#include "Libero/ECS/Core/System.h"

namespace Libero
{
	class SysTransforms final : public System<SysTransforms>
	{
	public:
		void PostUpdate() override;

	private:
	};
}


