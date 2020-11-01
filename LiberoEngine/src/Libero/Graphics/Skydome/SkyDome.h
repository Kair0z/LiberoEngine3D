#pragma once
#include "Libero/Math/LiberoMath.h"

namespace Libero
{
	using namespace Math;
	class SkyDome final
	{
	public:
		SkyDome(const ColorRGB& base = {}, const ColorRGB& apex = {1.f, 1.f, 1.f});
		class Mesh* GetMesh() const;

		DefGetSet(ColorRGB, ApexColor, m_ApexColor);
		DefGetSet(ColorRGB, BaseColor, m_BaseColor);

	private:
		ColorRGB m_ApexColor;
		ColorRGB m_BaseColor;

		class Mesh* m_pMesh = nullptr;
	};
}


