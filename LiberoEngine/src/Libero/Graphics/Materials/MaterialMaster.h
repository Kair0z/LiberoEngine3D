#pragma once
#include "Libero/Interfaces/ILocator.h"
#include <unordered_map>
#include "Material.h"

namespace Libero
{
	class IMaterial;
	class MaterialMaster final
	{
	public:
		template <class MaterialType, class ...Args>
		MaterialType* CreateMaterial(const std::string& name, Args&&... args)
		{
			DestroyMaterial(name);
			
			MaterialType* pMat = new MaterialType(std::forward<Args>(args)...);
			pMat->Initialize();

			m_MaterialMap[name] = pMat;
			return pMat;
		}

		const IMaterial* GetMaterial(const std::string& name);
		void DestroyMaterial(const std::string& name);

		~MaterialMaster();

	private:
		std::unordered_map<std::string, IMaterial*> m_MaterialMap;
	};

	class MaterialLocator : public ILocator<MaterialMaster>{};
}


