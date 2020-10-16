#pragma once

namespace Libero
{
	template <class Service>
	class ILocator
	{
	public:
		static void Provide(Service* pService)
		{
			if (!pService) return;

			m_pService = pService;
		}

		static Service* Get()
		{
			return m_pService;
		}

	protected:
		static Service* m_pService;
	};

	template<class Service>
	Service* ILocator<Service>::m_pService = nullptr;
}


