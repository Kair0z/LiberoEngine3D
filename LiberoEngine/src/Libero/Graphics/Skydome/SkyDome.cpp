#include "Liber_pch.h"
#include "SkyDome.h"

#include "Libero/Content/ContentMaster.h"
#include "Libero/Graphics/Mesh.h"

namespace Libero
{
	SkyDome::SkyDome(const ColorRGB& base, const ColorRGB& apex)
		: m_BaseColor{base}
		, m_ApexColor{apex}
	{
		// Set mesh as default Spheremesh.
		m_pMesh = ContentLocator::Get()->Load<Mesh>("../Resources/Core/Meshes/Sphere.obj");
	}

	Mesh* SkyDome::GetMesh() const
	{
		return m_pMesh;
	}
}

