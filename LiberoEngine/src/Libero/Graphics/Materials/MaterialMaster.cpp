#include "Liber_pch.h"
#include "MaterialMaster.h"

namespace Libero
{
	const IMaterial* MaterialMaster::GetMaterial(const std::string& name) 
	{
		return m_MaterialMap[name];
	}

	void MaterialMaster::DestroyMaterial(const std::string& name)
	{
		if (m_MaterialMap[name])
			SafeDelete(m_MaterialMap[name]);

		m_MaterialMap.erase(name);
	}

	MaterialMaster::~MaterialMaster()
	{
		for (auto& pair : m_MaterialMap) SafeDelete(pair.second);

		m_MaterialMap.clear();
	}
}

