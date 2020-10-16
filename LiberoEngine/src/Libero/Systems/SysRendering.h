#pragma once
#include "Libero/ECS/Core/System.h"

namespace Libero
{
	class SysRendering final : public System<SysRendering>
	{
	public:
		void Initialize() override;
		void Render() const override;
	};
}


