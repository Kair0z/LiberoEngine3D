#pragma once
#include "Loading.h"

namespace Libero
{
	class ILoader
	{
	public:
		virtual ~ILoader() = default;
		virtual const type_info& GetType() const = 0;
	};

	template <class Content>
	class Loader : public ILoader
	{
	public:
		~Loader();
		virtual Content* GetContent(const std::string& fName);
		virtual const type_info& GetType() const override final;
		virtual Content* LoadContent(const std::string& fName);

	protected:
		virtual void Destroy(Content* pObj);
		std::unordered_map<std::string, Content*> m_ContentMap;
	};

#pragma region Impl
	template<class Content>
	inline Loader<Content>::~Loader()
	{
		for (auto& pair : m_ContentMap)
			Destroy(pair.second);
	}

	template<class Content>
	inline const type_info& Loader<Content>::GetType() const
	{
		return typeid(Content);
	}

	template<class Content>
	inline Content* Loader<Content>::LoadContent(const std::string& fName)
	{
		return Loading::LoadContent<Content>(fName);
	}

	template<class Content>
	inline void Loader<Content>::Destroy(Content* pObj)
	{
		Loading::DestroyContent<Content>(pObj);
	}

	template<class Content>
	inline Content* Loader<Content>::GetContent(const std::string& fName)
	{
		// If the content doesn't yet exists load & return it...
		if (!m_ContentMap[fName]) m_ContentMap[fName] = LoadContent(fName);

		return m_ContentMap[fName];
	}
#pragma endregion
}


