#include "SysPlayerMovement.h"
#include "Libero/Components/CameraComponent.h"
#include "Libero/Components/TransformComponent.h"
#include "Libero/Logging/Logger.h"
#include "Libero/Interfaces/Events/EventDispatcher.h"
#include "Libero/Time/Time.h"

using namespace Libero;

void SysPlayerMovement::OnEvent(IEvent& e)
{
	EventCatch dispatch(e);
	dispatch.Catch<EventKeyDown>([this](EventKeyDown& e) 
		{
			ProcessKeyDown(e.GetParam());
		});

	dispatch.Catch<EventMouseMove>([this](EventMouseMove& e)
		{
			ProcessMouseMove(e);
		});
}

void SysPlayerMovement::Update()
{
	ForEachComponent<TransformComponent>([](TransformComponent* pTransform)
		{
			IEntity* pOwner = pTransform->GetOwner();
			if (pOwner->GetComponent<CameraComponent>()) return;

			float dt = (float)TimeLocator::GetDeltaTime();
			float speed = 0.5f;
			pTransform->Rotate({ 0.f, dt *speed, 0.f });
		});
}

void SysPlayerMovement::ProcessKeyDown(WPARAM wParam)
{
	Vector3f movement{};
	float scale{ 400.f };
	double dt = TimeLocator::GetDeltaTime();
	scale *= (float)dt;
	switch (wParam)
	{
	case VK_LEFT: movement.x = -scale; break;
	case VK_RIGHT: movement.x = scale; break;
	case VK_UP: movement.z = scale; break;
	case VK_DOWN: movement.z = -scale; break;
	}

	ForEachComponent<CameraComponent>([&movement](CameraComponent* pCam)
		{
			pCam->GetOwner()->GetComponent<TransformComponent>()->Translate({ movement.x, 0.f, 0.f }, TransformComponent::eSpace::Local);
		});
}

void SysPlayerMovement::ProcessMouseMove(EventMouseMove& e)
{
	double dt = TimeLocator::GetDeltaTime();
	float amount = (float)dt;
	ForEachComponent<CameraComponent>([&e, &amount](CameraComponent* pCam)
		{
			TransformComponent* pTransform = pCam->GetOwner()->GetComponent <TransformComponent>();
			if (e.IsLBDown() && e.IsRBDown())
			{
				float plus = 40.f;
				pTransform->Translate({ e.GetDelta().x * amount * plus, -e.GetDelta().y * amount * plus, 0.f }, TransformComponent::eSpace::Local);
				return;
			}

			if (e.IsRBDown())
			{
				pTransform->Rotate({ e.GetDelta().y * amount, e.GetDelta().x * amount, 0.f });
				return;
			}

			if (e.IsLBDown())
			{
				pTransform->Translate({0.f, 0.f, -e.GetDelta().y * amount * 40.f}, TransformComponent::eSpace::Local);
				pTransform->Rotate({ 0.f, e.GetDelta().x * amount, 0.f });
			}
		});
}
