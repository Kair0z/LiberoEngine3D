#pragma once
#include <string>

#pragma warning(push)
#pragma warning (disable: 4505)

namespace Libero
{
	namespace Loading
	{
		template <class Content>
		static Content* LoadContent(const std::string& fName);

		template <class Content>
		static void DestroyContent(Content* pObj);
	}
}

#include "MeshLoading.h"
#include "TextureLoading.h"

#pragma warning(pop)