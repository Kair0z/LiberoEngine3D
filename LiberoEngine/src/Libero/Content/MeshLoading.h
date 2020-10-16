#pragma once
#include "Loading.h"
#include "Libero/Graphics/Mesh.h"

namespace Libero
{
	namespace Loading
	{
		template<>
		Mesh* LoadContent<Mesh>(const std::string& fName)
		{
			return new Mesh(fName);
		}

		template <>
		void DestroyContent<Mesh>(Mesh* pObj)
		{
			SafeDelete(pObj);
		}
	}
}