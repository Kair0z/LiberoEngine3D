#include "Liber_pch.h"
#include "ISystem.h"
#include "../Masters/ComponentMaster.h"

namespace Libero
{
	template<class CompType, typename Op>
	inline void ISystem::ForEachComponent(Op op)
	{
		// Loop over all components:
		ComponentMaster* pCompMaster = ECSLocator::GetComponentMaster();

		for (auto it = pCompMaster->Begin<CompType>(); it != pCompMaster->End<CompType>(); ++it)
		{
			if (!(*it)->IsEnabled()) continue;
			op(*it);
		}
	}

	template<class CompType, typename Op>
	inline void ISystem::ForEachComponent(Op op) const
	{
		ComponentMaster* pCompMaster = ECSLocator::GetComponentMaster();
		
		for (auto it = pCompMaster->Begin<CompType>(); it != pCompMaster->End<CompType>(); ++it)
		{
			if (!(*it)) continue;
			if (!(*it)->IsEnabled()) continue;
			op(*it);
		}
	}
}