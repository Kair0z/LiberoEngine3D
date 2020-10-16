#pragma once
#include "Libero/ECS/Core/System.h"

namespace Libero
{
	class SysCameras : public System<SysCameras>
	{
	public:
		void PostUpdate() override;

	private:
		void CalculateViews();
	};
}


