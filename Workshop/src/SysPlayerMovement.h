#pragma once
#include "Libero/ECS/Core/System.h"
#include "Libero/Interfaces/Events/KeyEvent.h"
#include "Libero/Interfaces/Events/MouseEvent.h"

class SysPlayerMovement final : public Libero::System<SysPlayerMovement>
{
public:
	void Start() override;
	void OnEvent(Libero::IEvent& e) override;
	void Update() override;

private:
	void ProcessKeyDown(WPARAM wParam);
	void ProcessMouseMove(Libero::EventMouseMove& e);
};

