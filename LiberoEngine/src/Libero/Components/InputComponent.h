#pragma once
#include "Libero/ECS/Core/Component.h"

namespace Libero
{
	class InputComponent final: public Component<InputComponent>
	{
	public:
		void Bind(WPARAM wParam, const std::string& name);
		void HandleEvent(IEvent& e);

	private:

	};
}


