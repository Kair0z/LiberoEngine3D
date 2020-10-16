#pragma once
#include "Libero/Interfaces/ILocator.h"
#include "ILoader.h"

namespace Libero
{
	class ContentMaster final
	{
	public:
		ContentMaster() = default;
		~ContentMaster();

		void AddLoader(ILoader* pLoader);
		
		template <class Content>
		Content* Load(const std::string& fName);

	private:
		std::vector<ILoader*> m_Loaders;
		//std::unordered_map<const type_info&, ILoader*> m_Loaders;
	};

	class ContentLocator final : public ILocator<ContentMaster>{};
}

namespace Libero
{
	inline ContentMaster::~ContentMaster()
	{
		for (ILoader* pLoader : m_Loaders)
			SafeDelete(pLoader);
	}

	inline void ContentMaster::AddLoader(ILoader* pLoader)
	{
		if (!pLoader) return;
		m_Loaders.push_back(pLoader);
	}

	template<class Content>
	inline Content* ContentMaster::Load(const std::string& fName)
	{
		for (ILoader* pLoader : m_Loaders)
		{
			if (typeid(Content) != pLoader->GetType()) continue;

			return static_cast<Loader<Content>*>(pLoader)->GetContent(fName);
		}


		// If such loader doesn't exist yet, create a new one...
		Loader<Content>* pNewLoader = new Loader<Content>();
		if (!pNewLoader) return nullptr;
		AddLoader(pNewLoader);

		return pNewLoader->GetContent(fName);
	}
}


