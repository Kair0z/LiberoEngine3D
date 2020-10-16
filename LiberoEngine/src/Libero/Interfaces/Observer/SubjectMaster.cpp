#include "Liber_pch.h"
#include "SubjectMaster.h"
#include "IObserver.h"

namespace Libero
{
	void SubjectMaster::Notify(eSubject enm, IEvent& e)
	{
		for (IObserver* pObs : m_pSubjectMap[enm])
		{
			pObs->OnEvent(e);
		}
	}

	void SubjectMaster::AddToSubject(IObserver* pObs, eSubject enm)
	{
		if (!pObs) return;

		m_pSubjectMap[enm].push_back(pObs);
	}
}

