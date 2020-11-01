#pragma once
#include "Loading.h"
#include "Libero/Graphics/GraphicsMaster.h"
#include "Libero/Graphics/Texture2D.h"
#include "Libero/Misc/LiberoUtils.h"

namespace Libero
{
	namespace Loading
	{
		template<>
		Texture2D* LoadContent<Texture2D>(const std::string& fName)
		{
			return GraphicsLocator::Get()->CreateTexture(fName);
		}

		template <>
		void DestroyContent<Texture2D>(Texture2D* pObj)
		{
			SafeDelete(pObj);
		}
	}
}