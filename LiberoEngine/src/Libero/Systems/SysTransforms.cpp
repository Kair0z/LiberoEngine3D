#include "Liber_pch.h"
#include "SysTransforms.h"
#include "Libero/Components/TransformComponent.h"
#include "Libero/Components/CameraComponent.h"
#include "Libero/Time/Time.h"

namespace Libero
{
	void SysTransforms::PostUpdate()
	{
		ForEachComponent<TransformComponent>([](TransformComponent* pTransform)
			{
				// TODO: update children via deferred pattern
				pTransform->UpdateChildren(XMMatrixIdentity());
			});
	}
}