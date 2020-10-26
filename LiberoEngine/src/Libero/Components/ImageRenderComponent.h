#pragma once
#include "Libero/ECS/Core/Component.h"

using namespace DirectX;
namespace Libero
{

	class ImageRenderComponent final :
		public Component<ImageRenderComponent>
	{
		struct ImageVertex
		{
			XMFLOAT4 TransformData;
			XMFLOAT4 TransformData2;
		};

	public:
		ImageRenderComponent() = default;

		DefGetSet(ImageVertex, Data, m_Data);

	private:
		ImageVertex m_Data;

		
		
	};
}


