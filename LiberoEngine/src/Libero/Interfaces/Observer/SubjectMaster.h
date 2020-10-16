#pragma once
#include "Libero/Interfaces/ILocator.h"

namespace Libero
{
	enum class eSubject
	{
		Window,
		Input,
		Engine
	};

	class IEvent;
	class IObserver;
	class SubjectMaster final
	{
	public:
		void Notify(eSubject enm, IEvent& e);
		void AddToSubject(IObserver* pObs, eSubject enm);

	private:
		std::unordered_map<eSubject, std::vector<IObserver*>> m_pSubjectMap;
	};

	class SubjectLocator : public ILocator<SubjectMaster>{};
}




